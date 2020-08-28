#ifndef LOGGING_THREAD_SYNCPRIMS_PUB_IMPL_H
#define LOGGING_THREAD_SYNCPRIMS_PUB_IMPL_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <algorithm>

#if (defined (LOGGING_INLINES_ARE_EXPORTED)           \
    && defined (LOGGING_BUILD_DLL))                   \
    || defined (LOGGING_ENABLE_SYNCPRIMS_PUB_IMPL)
#include <logging/thread/syncprims.h>

#if ! defined (LOGGING_SINGLE_THREADED)
#  include <logging/thread/impl/syncprims-impl.h>
#endif

#define LOGGING_THROW_RTE(msg) \
    do { logging::thread::impl::syncprims_throw_exception (msg, __FILE__, \
            __LINE__); } while (0)

namespace logging {
	namespace thread {

		namespace impl
		{

			LOGGING_EXPORT void LOGGING_ATTRIBUTE_NORETURN
				syncprims_throw_exception(char const * const msg,
					char const * const file, int line);

		}

		//
		//
		//

		LOGGING_INLINE_EXPORT
			Mutex::Mutex()
			LOGGING_THREADED(: mtx())
		{ }


		LOGGING_INLINE_EXPORT
			Mutex::~Mutex()
		{ }


		LOGGING_INLINE_EXPORT
			void
			Mutex::lock() const
		{
			LOGGING_THREADED(mtx.lock());
		}


		LOGGING_INLINE_EXPORT
			void
			Mutex::unlock() const
		{
			LOGGING_THREADED(mtx.unlock());
		}


		//
		//
		//

		LOGGING_INLINE_EXPORT
			Semaphore::Semaphore(unsigned LOGGING_THREADED(max_),
				unsigned LOGGING_THREADED(initial))
#if ! defined (LOGGING_SINGLE_THREADED)
			: maximum(max_)
			, val((std::min) (maximum, initial))
#endif
		{ }


		LOGGING_INLINE_EXPORT
			Semaphore::~Semaphore()
		{ }


		LOGGING_INLINE_EXPORT
			void
			Semaphore::unlock() const
		{
#if ! defined (LOGGING_SINGLE_THREADED)
			std::lock_guard<std::mutex> guard(mtx);

			if (val >= maximum)
				LOGGING_THROW_RTE("Semaphore::unlock(): val >= max");

			++val;
			cv.notify_all();
#endif
		}


		LOGGING_INLINE_EXPORT
			void
			Semaphore::lock() const
		{
#if ! defined (LOGGING_SINGLE_THREADED)
			std::unique_lock<std::mutex> guard(mtx);

			if (LOGGING_UNLIKELY(val > maximum))
				LOGGING_THROW_RTE("Semaphore::unlock(): val > max");

			while (val == 0)
				cv.wait(guard);

			--val;

			if (LOGGING_UNLIKELY(val >= maximum))
				LOGGING_THROW_RTE("Semaphore::unlock(): val >= max");
#endif
		}


		//
		//
		//

		LOGGING_INLINE_EXPORT
			ManualResetEvent::ManualResetEvent(bool LOGGING_THREADED(sig))
#if ! defined (LOGGING_SINGLE_THREADED)
			: signaled(sig)
			, sigcount(0)
#endif
		{ }


		LOGGING_INLINE_EXPORT
			ManualResetEvent::~ManualResetEvent()
		{ }


		LOGGING_INLINE_EXPORT
			void
			ManualResetEvent::signal() const
		{
#if ! defined (LOGGING_SINGLE_THREADED)
			std::unique_lock<std::mutex> guard(mtx);

			signaled = true;
			sigcount += 1;
			cv.notify_all();
#endif
		}


		LOGGING_INLINE_EXPORT
			void
			ManualResetEvent::wait() const
		{
#if ! defined (LOGGING_SINGLE_THREADED)
			std::unique_lock<std::mutex> guard(mtx);

			if (!signaled)
			{
				unsigned prev_count = sigcount;
				do
				{
					cv.wait(guard);
				} while (prev_count == sigcount);
			}
#endif
		}


		LOGGING_INLINE_EXPORT
			bool
			ManualResetEvent::timed_wait(unsigned long LOGGING_THREADED(msec)) const
		{
#if defined (LOGGING_SINGLE_THREADED)
			return true;

#else
			std::unique_lock<std::mutex> guard(mtx);

			if (!signaled)
			{
				unsigned prev_count = sigcount;

				std::chrono::steady_clock::time_point const wait_until_time
					= std::chrono::steady_clock::now()
					+ std::chrono::milliseconds(msec);

				do
				{
					int ret = static_cast<int>(
						cv.wait_until(guard, wait_until_time));
					switch (ret)
					{
						case static_cast<int>(std::cv_status::no_timeout) :
							break;

							case static_cast<int>(std::cv_status::timeout) :
								return false;

							default:
								guard.unlock();
								guard.release();
								LOGGING_THROW_RTE("ManualResetEvent::timed_wait");
					}
				} while (prev_count == sigcount);
			}

			return true;
#endif
		}


		LOGGING_INLINE_EXPORT
			void
			ManualResetEvent::reset() const
		{
#if ! defined (LOGGING_SINGLE_THREADED)
			std::lock_guard<std::mutex> guard(mtx);

			signaled = false;
#endif
		}


		//
		//
		//

		LOGGING_INLINE_EXPORT
			SharedMutexImplBase::~SharedMutexImplBase()
		{ }


		//
		//
		//

		LOGGING_INLINE_EXPORT
			SharedMutex::SharedMutex()
			: sm(LOGGING_THREADED(new impl::SharedMutex))
		{ }


		LOGGING_INLINE_EXPORT
			SharedMutex::~SharedMutex()
		{
			LOGGING_THREADED(delete static_cast<impl::SharedMutex *>(sm));
		}


		LOGGING_INLINE_EXPORT
			void
			SharedMutex::rdlock() const
		{
			LOGGING_THREADED(static_cast<impl::SharedMutex *>(sm)->rdlock());
		}


		LOGGING_INLINE_EXPORT
			void
			SharedMutex::wrlock() const
		{
			LOGGING_THREADED(static_cast<impl::SharedMutex *>(sm)->wrlock());
		}


		LOGGING_INLINE_EXPORT
			void
			SharedMutex::rdunlock() const
		{
			LOGGING_THREADED(static_cast<impl::SharedMutex *>(sm)->rdunlock());
		}


		LOGGING_INLINE_EXPORT
			void
			SharedMutex::wrunlock() const
		{
			LOGGING_THREADED(static_cast<impl::SharedMutex *>(sm)->wrunlock());
		}


	}
} // namespace logging { namespace thread {

#endif // LOGGING_ENABLE_SYNCPRIMS_PUB_IMPL

#endif // LOGGING_THREAD_SYNCPRIMS_PUB_IMPL_H
