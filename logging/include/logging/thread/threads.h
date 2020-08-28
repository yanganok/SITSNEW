#ifndef LOGGING_THREADS_HEADER_
#define LOGGING_THREADS_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <memory>
#include <thread>

#include <logging/tstring.h>
#include <logging/helpers/pointer.h>


namespace logging {
	namespace thread {


		LOGGING_EXPORT logging::tstring const & getCurrentThreadName();
		LOGGING_EXPORT logging::tstring const & getCurrentThreadName2();
		LOGGING_EXPORT void setCurrentThreadName(const logging::tstring & name);
		LOGGING_EXPORT void setCurrentThreadName2(const logging::tstring & name);
		LOGGING_EXPORT void yield();
		LOGGING_EXPORT void blockAllSignals();

		/**
		 * This class blocks all POSIX signals when created and unblocks them when
		 * destroyed.
		 */
		class LOGGING_EXPORT SignalsBlocker
		{
		public:
			SignalsBlocker();
			~SignalsBlocker();

		private:
			struct SignalsBlockerImpl;
			std::unique_ptr<SignalsBlockerImpl> impl;
		};


#ifndef LOGGING_SINGLE_THREADED


		/**
		 * There are many cross-platform C++ Threading libraries.  The goal of
		 * this class is not to replace (or match in functionality) those
		 * libraries.  The goal of this class is to provide a simple Threading
		 * class with basic functionality.
		 */
		class LOGGING_EXPORT AbstractThread
			: public virtual logging::helpers::SharedObject
		{
		public:
			AbstractThread();
			// Disallow copying of instances of this class.
			AbstractThread(const AbstractThread&) = delete;
			AbstractThread& operator=(const AbstractThread&) = delete;

			bool isRunning() const;
			virtual void start();
			void join() const;
			virtual void run() = 0;

		protected:
			// Force objects to be constructed on the heap
			virtual ~AbstractThread();

		private:
			enum Flags
			{
				fRUNNING = 1,
				fJOINED = 2
			};

			std::unique_ptr<std::thread> thread;
			mutable std::atomic<int> flags;
		};

		typedef helpers::SharedObjectPtr<AbstractThread> AbstractThreadPtr;


#endif // LOGGING_SINGLE_THREADED


	}
} // namespace logging { namespace thread {


#endif // LOGGING_THREADS_HEADER_
