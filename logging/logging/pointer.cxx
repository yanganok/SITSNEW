#include <logging/streams.h>
#include <logging/helpers/pointer.h>
#include <logging/thread/threads.h>
#include <logging/thread/impl/syncprims-impl.h>
#include <cassert>


namespace logging {
	namespace helpers {


		///////////////////////////////////////////////////////////////////////////////
		// logging::helpers::SharedObject dtor
		///////////////////////////////////////////////////////////////////////////////

		SharedObject::~SharedObject()
		{
			assert(count__ == 0);
		}



		///////////////////////////////////////////////////////////////////////////////
		// logging::helpers::SharedObject public methods
		///////////////////////////////////////////////////////////////////////////////

		void
			SharedObject::addReference() const LOGGING_NOEXCEPT
		{
#if defined (LOGGING_SINGLE_THREADED)
			++count__;

#else
			std::atomic_fetch_add_explicit(&count__, 1u,
				std::memory_order_relaxed);

#endif
		}


		void
			SharedObject::removeReference() const
		{
			assert(count__ > 0);
			bool destroy;

#if defined (LOGGING_SINGLE_THREADED)
			destroy = --count__ == 0;

#else
			destroy = std::atomic_fetch_sub_explicit(&count__, 1u,
				std::memory_order_release) == 1;
			if (LOGGING_UNLIKELY(destroy))
				std::atomic_thread_fence(std::memory_order_acquire);

#endif
			if (LOGGING_UNLIKELY(destroy))
				delete this;
		}


	}
} // namespace logging { namespace helpers
