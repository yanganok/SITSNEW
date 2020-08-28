#ifndef LOGGING_HELPERS_POINTERS_HEADER_
#define LOGGING_HELPERS_POINTERS_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/thread/syncprims.h>
#include <algorithm>
#include <cassert>
#if ! defined (LOGGING_SINGLE_THREADED)
#include <atomic>
#endif


namespace logging {
	namespace helpers {

		/******************************************************************************
		 *                       Class SharedObject (from pp. 204-205)                *
		 ******************************************************************************/

		class LOGGING_EXPORT SharedObject
		{
		public:
			void addReference() const LOGGING_NOEXCEPT;
			void removeReference() const;

		protected:
			// Ctor
			SharedObject()
				: access_mutex()
				, count__(0)
			{ }

			SharedObject(const SharedObject&)
				: access_mutex()
				, count__(0)
			{ }

			SharedObject(SharedObject &&)
				: access_mutex()
				, count__(0)
			{ }

			// Dtor
			virtual ~SharedObject();

			// Operators
			SharedObject& operator=(const SharedObject&) LOGGING_NOEXCEPT { return *this; }
			SharedObject& operator=(SharedObject &&) LOGGING_NOEXCEPT { return *this; }

		public:
			thread::Mutex access_mutex;

		private:
#if defined (LOGGING_SINGLE_THREADED)
			typedef unsigned count_type;
#else
			typedef std::atomic<unsigned> count_type;
#endif
			mutable count_type count__;
		};


		/******************************************************************************
		 *           Template Class SharedObjectPtr (from pp. 203, 206)               *
		 ******************************************************************************/
		template<class T>
		class SharedObjectPtr
		{
		public:
			// Ctor
			explicit
				SharedObjectPtr(T* realPtr = 0) LOGGING_NOEXCEPT
				: pointee(realPtr)
			{
				addref();
			}

			SharedObjectPtr(const SharedObjectPtr& rhs) LOGGING_NOEXCEPT
				: pointee(rhs.pointee)
			{
				addref();
			}

			SharedObjectPtr(SharedObjectPtr && rhs) LOGGING_NOEXCEPT
				: pointee(std::move(rhs.pointee))
			{
				rhs.pointee = 0;
			}

			SharedObjectPtr & operator = (SharedObjectPtr && rhs) LOGGING_NOEXCEPT
			{
				rhs.swap(*this);
				return *this;
			}

			// Dtor
			~SharedObjectPtr()
			{
				if (pointee)
					pointee->removeReference();
			}

			// Operators
			bool operator==(const SharedObjectPtr& rhs) const
			{
				return (pointee == rhs.pointee);
			}
			bool operator!=(const SharedObjectPtr& rhs) const
			{
				return (pointee != rhs.pointee);
			}
			bool operator==(const T* rhs) const { return (pointee == rhs); }
			bool operator!=(const T* rhs) const { return (pointee != rhs); }
			T* operator->() const { assert(pointee); return pointee; }
			T& operator*() const { assert(pointee); return *pointee; }

			SharedObjectPtr& operator=(const SharedObjectPtr& rhs)
			{
				return this->operator = (rhs.pointee);
			}

			SharedObjectPtr& operator=(T* rhs)
			{
				SharedObjectPtr<T>(rhs).swap(*this);
				return *this;
			}

			// Methods
			T* get() const { return pointee; }

			void swap(SharedObjectPtr & other) LOGGING_NOEXCEPT
			{
				std::swap(pointee, other.pointee);
			}

			typedef T * (SharedObjectPtr:: * unspec_bool_type) () const;
			operator unspec_bool_type () const
			{
				return pointee ? &SharedObjectPtr::get : 0;
			}

			bool operator ! () const
			{
				return !pointee;
			}

		private:
			// Methods
			void addref() const LOGGING_NOEXCEPT
			{
				if (pointee)
					pointee->addReference();
			}

			// Data
			T* pointee;
		};


		//! Boost `intrusive_ptr` helpers.
		//! @{
		inline
			void
			intrusive_ptr_add_ref(SharedObject const * so)
		{
			so->addReference();
		}

		inline
			void
			intrusive_ptr_release(SharedObject const * so)
		{
			so->removeReference();
		}
		//! @}

	} // end namespace helpers
} // end namespace logging


#endif // LOGGING_HELPERS_POINTERS_HEADER_
