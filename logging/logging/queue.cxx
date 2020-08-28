#include <logging/config.hxx>
#ifndef LOGGING_SINGLE_THREADED

#include <logging/helpers/queue.h>
#include <logging/helpers/loglog.h>
#include <logging/thread/syncprims-pub-impl.h>
#include <stdexcept>
#include <algorithm>
#include <iterator>


namespace logging {
	namespace thread {


		Queue::Queue(unsigned len)
			: mutex()
			, ev_consumer(false)
			, sem(len, len)
			, flags(DRAIN)
		{ }


		Queue::~Queue()
		{ }


		Queue::flags_type
			Queue::put_event(spi::InternalLoggingEvent const & ev)
		{
			flags_type ret_flags = ERROR_BIT;
			try
			{
				ev.gatherThreadSpecificData();

				SemaphoreGuard semguard(sem);
				MutexGuard mguard(mutex);

				ret_flags |= flags;

				if (flags & EXIT)
				{
					ret_flags &= ~(ERROR_BIT | ERROR_AFTER);
					return ret_flags;
				}
				else
				{
					queue.push_back(ev);
					ret_flags |= ERROR_AFTER;
					semguard.detach();
					flags |= QUEUE;
					ret_flags |= flags;
					mguard.unlock();
					mguard.detach();
					ev_consumer.signal();
				}
			}
			catch (std::runtime_error const & e)
			{
				logging::helpers::getLogLog().error(
					LOGGING_TEXT("put_event() exception: ")
					+ LOGGING_C_STR_TO_TSTRING(e.what()));
				return ret_flags;
			}

			ret_flags &= ~(ERROR_BIT | ERROR_AFTER);
			return ret_flags;
		}


		Queue::flags_type
			Queue::signal_exit(bool drain)
		{
			flags_type ret_flags = 0;

			try
			{
				MutexGuard mguard(mutex);

				ret_flags |= flags;

				if (!(flags & EXIT))
				{
					if (drain)
						flags |= DRAIN;
					else
						flags &= ~DRAIN;
					flags |= EXIT;
					ret_flags = flags;
					mguard.unlock();
					mguard.detach();
					ev_consumer.signal();
				}
			}
			catch (std::runtime_error const & e)
			{
				logging::helpers::getLogLog().error(
					LOGGING_TEXT("signal_exit() exception: ")
					+ LOGGING_C_STR_TO_TSTRING(e.what()));
				ret_flags |= ERROR_BIT;
				return ret_flags;
			}

			return ret_flags;
		}


		Queue::flags_type
			Queue::get_events(queue_storage_type * buf)
		{
			flags_type ret_flags = 0;

			try
			{
				while (true)
				{
					MutexGuard mguard(mutex);

					ret_flags = flags;

					if (((QUEUE & flags) && !(EXIT & flags))
						|| ((EXIT | DRAIN | QUEUE) & flags) == (EXIT | DRAIN | QUEUE))
					{
						assert(!queue.empty());

						std::size_t const count = queue.size();
						queue.swap(*buf);
						queue.clear();
						flags &= ~QUEUE;
						for (std::size_t i = 0; i != count; ++i)
							sem.unlock();

						ret_flags = flags | EVENT;
						break;
					}
					else if (((EXIT | QUEUE) & flags) == (EXIT | QUEUE))
					{
						assert(!queue.empty());
						queue.clear();
						flags &= ~QUEUE;
						ev_consumer.reset();
						sem.unlock();
						ret_flags = flags;
						break;
					}
					else if (EXIT & flags)
						break;
					else
					{
						ev_consumer.reset();
						mguard.unlock();
						mguard.detach();
						ev_consumer.wait();
					}
				}
			}
			catch (std::runtime_error const & e)
			{
				logging::helpers::getLogLog().error(
					LOGGING_TEXT("get_events() exception: ")
					+ LOGGING_C_STR_TO_TSTRING(e.what()));
				ret_flags |= ERROR_BIT;
			}

			return ret_flags;
		}


	}
} // namespace logging { namespace thread {


#endif // LOGGING_SINGLE_THREADED
