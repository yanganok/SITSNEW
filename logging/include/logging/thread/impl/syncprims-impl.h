#ifndef LOGGING_THREAD_SYNCPRIMS_IMPL_H
#define LOGGING_THREAD_SYNCPRIMS_IMPL_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#if ! defined (INSIDE_LOGGING)
#  error "This header must not be be used outside logging' implementation files."
#endif

#include <stdexcept>
#include <logging/thread/syncprims.h>
#include <mutex>
#include <thread>
#include <condition_variable>


namespace logging {
	namespace thread {
		namespace impl {


			LOGGING_EXPORT void LOGGING_ATTRIBUTE_NORETURN
				syncprims_throw_exception(char const * const msg,
					char const * const file, int line);


			class SharedMutex
				: public SharedMutexImplBase
			{
			public:
				SharedMutex();
				~SharedMutex();

				void rdlock() const;
				void wrlock() const;
				void rdunlock() const;
				void wrunlock() const;

			private:
				Mutex m1;
				Mutex m2;
				Mutex m3;
				Semaphore w;
				mutable unsigned writer_count;
				Semaphore r;
				mutable unsigned reader_count;

				SharedMutex(SharedMutex const &);
				SharedMutex & operator = (SharedMutex const &);
			};


		}
	}
} // namespace logging { namespace thread { namespace impl {


// Include the appropriate implementations of the classes declared
// above.

#include <logging/thread/impl/syncprims-cxx11.h>

#undef LOGGING_THROW_RTE


#endif // LOGGING_THREAD_SYNCPRIMS_IMPL_H
