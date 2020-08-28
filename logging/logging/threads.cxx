#include <logging/config.hxx>

#include <exception>
#include <ostream>
#include <cerrno>

#ifdef LOGGING_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef LOGGING_HAVE_SYS_SYSCALL_H
#include <sys/syscall.h>
#endif

#ifdef LOGGING_HAVE_ERRNO_H
#include <errno.h>
#endif

#ifdef LOGGING_HAVE_UNISTD_H
#include <unistd.h>
#endif

#if defined(LOGGING_USE_PTHREADS)
#  include <pthread.h>
#  include <sched.h>
#  include <signal.h>
#elif defined (LOGGING_USE_WIN32_THREADS)
#  include <process.h>
#endif
#include <logging/config/windowsh-inc.h>
#include <logging/thread/syncprims-pub-impl.h>
#include <logging/tstring.h>
#include <logging/internal/cygwin-win32.h>
#include <logging/streams.h>

#include <logging/thread/threads.h>

#ifndef LOGGING_SINGLE_THREADED

#include <logging/thread/impl/threads-impl.h>
#include <logging/thread/impl/tls.h>
#include <logging/ndc.h>
#include <logging/helpers/loglog.h>
#include <logging/helpers/stringhelper.h>
#include <logging/helpers/timehelper.h>
#include <logging/internal/internal.h>

#endif // LOGGING_SINGLE_THREADED


namespace logging {
	namespace thread {

		LOGGING_EXPORT
			void
			blockAllSignals()
		{
#if defined (LOGGING_USE_PTHREADS)
			// Block all signals.
			sigset_t signal_set;
			sigfillset(&signal_set);
			pthread_sigmask(SIG_BLOCK, &signal_set, nullptr);
#endif
		}


		LOGGING_EXPORT
			void
			yield()
		{
#if defined(LOGGING_USE_PTHREADS)
			sched_yield();
#elif defined(_WIN32)
			if (!SwitchToThread())
				Sleep(0);
#endif
		}

#if defined(LOGGING_SINGLE_THREADED)
		static logging::tstring thread_name
			LOGGING_INIT_PRIORITY(LOGGING_INIT_PRIORITY_BASE - 1)
			(LOGGING_TEXT("single"));
		static logging::tstring thread_name2
			LOGGING_INIT_PRIORITY(LOGGING_INIT_PRIORITY_BASE - 1)
			(thread_name);
#endif

		LOGGING_EXPORT
			logging::tstring const &
			getCurrentThreadName()
		{
#if ! defined (LOGGING_SINGLE_THREADED)
			logging::tstring & name = logging::internal::get_thread_name_str();
			if (LOGGING_UNLIKELY(name.empty()))
			{
				logging::tostringstream tmp;
				tmp << impl::getCurrentThreadId();
				name = tmp.str();
			}
#else
			logging::tstring & name = thread_name;
			if (LOGGING_UNLIKELY(name.empty()))
			{
				name = LOGGING_TEXT("single");
			}
#endif

			return name;
		}


		namespace
		{


			static
				bool
				get_current_thread_name_alt(logging::tostream * s)
			{
				logging::tostream & os = *s;

#if defined (LOGGING_USE_PTHREADS) && defined (__linux__) \
    && defined (LOGGING_HAVE_GETTID)
				pid_t tid = syscall(SYS_gettid);
				os << tid;

#elif defined (__CYGWIN__)
				unsigned long tid = cygwin::get_current_win32_thread_id();
				os << tid;

#else
				os << getCurrentThreadName();

#endif

				return true;
			}


		} // namespace


		LOGGING_EXPORT
			logging::tstring const &
			getCurrentThreadName2()
		{
#if ! defined (LOGGING_SINGLE_THREADED)
			logging::tstring & name = logging::internal::get_thread_name2_str();
			if (LOGGING_UNLIKELY(name.empty()))
			{
				logging::tostringstream tmp;
				get_current_thread_name_alt(&tmp);
				name = tmp.str();
			}

#else
			logging::tstring & name = thread_name2;
			if (LOGGING_UNLIKELY(name.empty()))
			{
				name = getCurrentThreadName();
			}

#endif

			return name;
		}

		LOGGING_EXPORT void setCurrentThreadName(const logging::tstring & name)
		{
#if ! defined (LOGGING_SINGLE_THREADED)
			logging::internal::get_thread_name_str() = name;
#else
			thread_name = name;
#endif
		}

		LOGGING_EXPORT void setCurrentThreadName2(const logging::tstring & name)
		{
#if ! defined (LOGGING_SINGLE_THREADED)
			logging::internal::get_thread_name2_str() = name;
#else
			thread_name2 = name;
#endif
		}


		//
		//
		//

		struct SignalsBlocker::SignalsBlockerImpl
		{
#if defined (LOGGING_USE_PTHREADS)
			sigset_t signal_set;
#endif
		};


		SignalsBlocker::SignalsBlocker()
			: impl(new SignalsBlocker::SignalsBlockerImpl)
		{
#if defined (LOGGING_USE_PTHREADS)
			sigset_t block_all_set;
			sigfillset(&block_all_set);
			(void)pthread_sigmask(SIG_BLOCK, &block_all_set, &impl->signal_set);
#endif
		}


		SignalsBlocker::~SignalsBlocker()
		{
#if defined (LOGGING_USE_PTHREADS)
			(void)pthread_sigmask(SIG_SETMASK, &impl->signal_set, nullptr);
#endif
		}


#ifndef LOGGING_SINGLE_THREADED

		//
		//
		//

		AbstractThread::AbstractThread()
			: flags(0)
		{ }


		bool
			AbstractThread::isRunning() const
		{
			return (flags & fRUNNING) != 0;
		}


		void
			AbstractThread::start()
		{
			try
			{
				flags |= fRUNNING;
				thread.reset(
					new std::thread([this](AbstractThreadPtr const & thread_ptr) {
					(void)thread_ptr;
					blockAllSignals();
					helpers::LogLog & loglog = helpers::getLogLog();
					try
					{
						this->run();
					}
					catch (std::exception const & e)
					{
						tstring err(LOGGING_TEXT("threadStartFunc()")
							LOGGING_TEXT("- run() terminated with an exception: "));
						err += LOGGING_C_STR_TO_TSTRING(e.what());
						loglog.warn(err);
					}
					catch (...)
					{
						loglog.warn(LOGGING_TEXT("threadStartFunc()")
							LOGGING_TEXT("- run() terminated with an exception."));
					}
					this->flags &= ~fRUNNING;
					threadCleanup();
				}, AbstractThreadPtr(this)));
			}
			catch (...)
			{
				flags &= ~fRUNNING;
				throw;
			}
		}


		void
			AbstractThread::join() const
		{
			if (!thread
				|| (flags & fJOINED) == fJOINED)
				throw std::logic_error("this thread is not running");

			thread->join();
			flags |= +fJOINED;
		}


		AbstractThread::~AbstractThread()
		{
			if ((flags & fJOINED) == 0)
				thread->detach();
		}

#endif // LOGGING_SINGLE_THREADED


	}
} // namespace logging { namespace thread {
