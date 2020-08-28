#ifndef LOGGING_THREAD_IMPL_TLS_H
#define LOGGING_THREAD_IMPL_TLS_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <new>
#include <cassert>
#include <system_error>

#if ! defined (INSIDE_LOGGING)
#  error "This header must not be be used outside logging' implementation files."
#endif

#ifdef LOGGING_USE_PTHREADS
#  include <pthread.h>

#elif defined (LOGGING_USE_WIN32_THREADS)
#  include <logging/config/windowsh-inc.h>

#elif defined (LOGGING_SINGLE_THREADED)
#  include <vector>

#endif


namespace logging {
	namespace thread {
		namespace impl {


			typedef void * tls_value_type;

#ifdef LOGGING_USE_PTHREADS
			typedef pthread_key_t * tls_key_type;
			typedef void(*tls_init_cleanup_func_type)(void *);

#elif defined (LOGGING_USE_WIN32_THREADS)
			typedef DWORD tls_key_type;
			typedef PFLS_CALLBACK_FUNCTION tls_init_cleanup_func_type;

#elif defined (LOGGING_SINGLE_THREADED)
			typedef std::size_t tls_key_type;
			typedef void(*tls_init_cleanup_func_type)(void *);

#endif


			inline tls_key_type tls_init(tls_init_cleanup_func_type);
			inline tls_value_type tls_get_value(tls_key_type);
			inline void tls_set_value(tls_key_type, tls_value_type);
			inline void tls_cleanup(tls_key_type);


#if defined (LOGGING_USE_PTHREADS)
			tls_key_type
				tls_init(tls_init_cleanup_func_type cleanupfunc)
			{
				pthread_key_t * key = new pthread_key_t;
				int ret = pthread_key_create(key, cleanupfunc);
				if (LOGGING_UNLIKELY(ret != 0))
					throw std::system_error(ret, std::system_category(),
						"pthread_key_create() failed");
				return key;
		}


			tls_value_type
				tls_get_value(tls_key_type key)
			{
				return pthread_getspecific(*key);
			}


			void
				tls_set_value(tls_key_type key, tls_value_type value)
			{
				pthread_setspecific(*key, value);
			}


			void
				tls_cleanup(tls_key_type key)
			{
				pthread_key_delete(*key);
				delete key;
			}


#elif defined (LOGGING_USE_WIN32_THREADS)
			tls_key_type
				tls_init(tls_init_cleanup_func_type cleanupfunc)
			{
				DWORD const slot = FlsAlloc(cleanupfunc);
				if (LOGGING_UNLIKELY(slot == FLS_OUT_OF_INDEXES))
				{
					DWORD const eno = GetLastError();
					throw std::system_error(static_cast<int>(eno),
						std::system_category(), "FlsAlloc() failed");
				}
				return slot;
			}


			tls_value_type tls_get_value(tls_key_type k)
			{
				return FlsGetValue(k);
			}


			void
				tls_set_value(tls_key_type k, tls_value_type value)
			{
				FlsSetValue(k, value);
			}


			void
				tls_cleanup(tls_key_type k)
			{
				FlsFree(k);
			}


#elif defined (LOGGING_SINGLE_THREADED)
			extern std::vector<tls_value_type> * tls_single_threaded_values;


			tls_key_type
				tls_init(tls_init_cleanup_func_type)
			{
				if (!tls_single_threaded_values)
					tls_single_threaded_values = new std::vector<tls_value_type>;
				tls_key_type key = tls_single_threaded_values->size();
				tls_single_threaded_values->resize(key + 1);
				return key;
			}


			tls_value_type
				tls_get_value(tls_key_type k)
			{
				assert(k < tls_single_threaded_values->size());
				return (*tls_single_threaded_values)[k];
			}


			void
				tls_set_value(tls_key_type k, tls_value_type val)
			{
				assert(k < tls_single_threaded_values->size());
				(*tls_single_threaded_values)[k] = val;
			}


			void
				tls_cleanup(tls_key_type k)
			{
				assert(k < tls_single_threaded_values->size());
				(*tls_single_threaded_values)[k] = 0;
			}

#endif


		}
	}
} // namespace logging { namespace thread { namespace impl {

#endif // LOGGING_THREAD_IMPL_TLS_H
