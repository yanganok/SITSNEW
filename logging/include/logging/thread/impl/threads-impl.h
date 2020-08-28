#ifndef LOGGING_IMPL_THREADS_IMPL_HEADER_
#define LOGGING_IMPL_THREADS_IMPL_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#if defined (_WIN32)
#include <logging/config/windowsh-inc.h>
#endif
#include <logging/tstring.h>
#include <logging/helpers/pointer.h>
#include <logging/thread/threads.h>

#if ! defined (INSIDE_LOGGING)
#  error "This header must not be be used outside logging' implementation files."
#endif


namespace logging {
	namespace thread {
		namespace impl {


#if defined (LOGGING_USE_PTHREADS)

			typedef pthread_t os_handle_type;
			typedef pthread_t os_id_type;


			inline
				pthread_t
				getCurrentThreadId()
			{
				return pthread_self();
			}


#elif defined (LOGGING_USE_WIN32_THREADS)

			typedef HANDLE os_handle_type;
			typedef DWORD os_id_type;


			inline
				DWORD
				getCurrentThreadId()
			{
				return GetCurrentThreadId();
			}


#elif defined (LOGGING_SINGLE_THREADED)

			typedef void * os_handle_type;
			typedef int os_id_type;


			inline
				int
				getCurrentThreadId()
			{
				return 1;
			}


#endif


		}
	}
} // namespace logging { namespace thread { namespace impl {


#endif // LOGGING_IMPL_THREADS_IMPL_HEADER_
