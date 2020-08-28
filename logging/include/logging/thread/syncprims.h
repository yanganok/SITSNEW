#ifndef LOGGING_THREAD_SYNCPRIMS_H
#define LOGGING_THREAD_SYNCPRIMS_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <mutex>
#include <condition_variable>


namespace logging {
	namespace thread {


		template <typename SyncPrim>
		class SyncGuard
		{
		public:
			SyncGuard();
			SyncGuard(SyncPrim const &);
			~SyncGuard();
			SyncGuard(SyncGuard const &) = delete;
			SyncGuard & operator = (SyncGuard const &) = delete;


			void lock();
			void unlock();
			void attach(SyncPrim const &);
			void attach_and_lock(SyncPrim const &);
			void detach();

		private:
			SyncPrim const * sp;
		};


		class LOGGING_EXPORT Mutex
		{
		public:
			Mutex();
			~Mutex();
			Mutex(Mutex const &) = delete;
			Mutex & operator = (Mutex const &) = delete;

			void lock() const;
			void unlock() const;

		private:
			LOGGING_THREADED(mutable std::recursive_mutex mtx;)
		};


		typedef SyncGuard<Mutex> MutexGuard;


		class LOGGING_EXPORT Semaphore
		{
		public:
			Semaphore(unsigned max, unsigned initial);
			~Semaphore();
			Semaphore(Semaphore const &) = delete;
			Semaphore & operator = (Semaphore const &) = delete;

			void lock() const;
			void unlock() const;

		private:
#if ! defined (LOGGING_SINGLE_THREADED)
			mutable std::mutex mtx;
			mutable std::condition_variable cv;
			mutable unsigned maximum;
			mutable unsigned val;
#endif
		};


		typedef SyncGuard<Semaphore> SemaphoreGuard;


		class LOGGING_EXPORT ManualResetEvent
		{
		public:
			explicit ManualResetEvent(bool = false);
			~ManualResetEvent();
			ManualResetEvent(ManualResetEvent const &) = delete;
			ManualResetEvent & operator = (ManualResetEvent const &) = delete;

			void signal() const;
			void wait() const;
			bool timed_wait(unsigned long msec) const;
			void reset() const;

		private:
#if ! defined (LOGGING_SINGLE_THREADED)
			mutable std::mutex mtx;
			mutable std::condition_variable cv;
			mutable bool signaled;
			mutable unsigned sigcount;
#endif
		};


		class SharedMutexImplBase
		{
		protected:
			~SharedMutexImplBase();
		};


		template <typename SyncPrim, void (SyncPrim:: * lock_func) () const,
			void (SyncPrim:: * unlock_func) () const>
			class SyncGuardFunc
		{
		public:
			SyncGuardFunc(SyncPrim const &);
			~SyncGuardFunc();

			void lock();
			void unlock();
			void attach(SyncPrim const &);
			void detach();

		private:
			SyncPrim const * sp;

			SyncGuardFunc(SyncGuardFunc const &);
			SyncGuardFunc & operator = (SyncGuardFunc const &);
		};


		class LOGGING_EXPORT SharedMutex
		{
		public:
			SharedMutex();
			~SharedMutex();

			void rdlock() const;
			void rdunlock() const;

			void wrlock() const;
			void wrunlock() const;

		private:
			SharedMutexImplBase * sm;

			SharedMutex(SharedMutex const &);
			SharedMutex & operator = (SharedMutex const &);
		};


		typedef SyncGuardFunc<SharedMutex, &SharedMutex::rdlock,
			&SharedMutex::rdunlock> SharedMutexReaderGuard;


		typedef SyncGuardFunc<SharedMutex, &SharedMutex::wrlock,
			&SharedMutex::wrunlock> SharedMutexWriterGuard;


		//
		//
		//

		template <typename SyncPrim>
		inline
			SyncGuard<SyncPrim>::SyncGuard()
			: sp(0)
		{ }


		template <typename SyncPrim>
		inline
			SyncGuard<SyncPrim>::SyncGuard(SyncPrim const & m)
			: sp(&m)
		{
			sp->lock();
		}


		template <typename SyncPrim>
		inline
			SyncGuard<SyncPrim>::~SyncGuard()
		{
			if (sp)
				sp->unlock();
		}


		template <typename SyncPrim>
		inline
			void
			SyncGuard<SyncPrim>::lock()
		{
			sp->lock();
		}


		template <typename SyncPrim>
		inline
			void
			SyncGuard<SyncPrim>::unlock()
		{
			sp->unlock();
		}


		template <typename SyncPrim>
		inline
			void
			SyncGuard<SyncPrim>::attach(SyncPrim const & m)
		{
			sp = &m;
		}


		template <typename SyncPrim>
		inline
			void
			SyncGuard<SyncPrim>::attach_and_lock(SyncPrim const & m)
		{
			attach(m);
			try
			{
				lock();
			}
			catch (...)
			{
				detach();
				throw;
			}
		}


		template <typename SyncPrim>
		inline
			void
			SyncGuard<SyncPrim>::detach()
		{
			sp = 0;
		}


		//
		//
		//

		template <typename SyncPrim, void (SyncPrim:: * lock_func) () const,
			void (SyncPrim:: * unlock_func) () const>
			inline
			SyncGuardFunc<SyncPrim, lock_func, unlock_func>::SyncGuardFunc(SyncPrim const & m)
			: sp(&m)
		{
			(sp->*lock_func) ();
		}


		template <typename SyncPrim, void (SyncPrim:: * lock_func) () const,
			void (SyncPrim:: * unlock_func) () const>
			inline
			SyncGuardFunc<SyncPrim, lock_func, unlock_func>::~SyncGuardFunc()
		{
			if (sp)
				(sp->*unlock_func) ();
		}


		template <typename SyncPrim, void (SyncPrim:: * lock_func) () const,
			void (SyncPrim:: * unlock_func) () const>
			inline
			void
			SyncGuardFunc<SyncPrim, lock_func, unlock_func>::lock()
		{
			(sp->*lock_func) ();
		}


		template <typename SyncPrim, void (SyncPrim:: * lock_func) () const,
			void (SyncPrim:: * unlock_func) () const>
			inline
			void
			SyncGuardFunc<SyncPrim, lock_func, unlock_func>::unlock()
		{
			(sp->*unlock_func) ();
		}


		template <typename SyncPrim, void (SyncPrim:: * lock_func) () const,
			void (SyncPrim:: * unlock_func) () const>
			inline
			void
			SyncGuardFunc<SyncPrim, lock_func, unlock_func>::attach(SyncPrim const & m)
		{
			sp = &m;
		}


		template <typename SyncPrim, void (SyncPrim:: * lock_func) () const,
			void (SyncPrim:: * unlock_func) () const>
			inline
			void
			SyncGuardFunc<SyncPrim, lock_func, unlock_func>::detach()
		{
			sp = 0;
		}


	}
} // namespace logging { namespace thread {


#endif // LOGGING_THREAD_SYNCPRIMS_H
