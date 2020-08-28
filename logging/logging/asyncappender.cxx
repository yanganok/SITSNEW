#include <logging/config.hxx>
#ifndef LOGGING_SINGLE_THREADED

#include <logging/asyncappender.h>
#include <logging/spi/factory.h>
#include <logging/helpers/loglog.h>
#include <logging/helpers/property.h>
#include <logging/thread/syncprims-pub-impl.h>


namespace logging
{


	namespace
	{


		class QueueThread : public thread::AbstractThread
		{
		public:
			QueueThread(AsyncAppenderPtr, thread::QueuePtr);

			void run() override;

		private:
			AsyncAppenderPtr appenders;
			thread::QueuePtr queue;
		};


		QueueThread::QueueThread(AsyncAppenderPtr aai, thread::QueuePtr q) : appenders(std::move(aai)), queue(std::move(q))
		{

		}


		void
			QueueThread::run()
		{
			typedef logging::thread::Queue::queue_storage_type ev_buf_type;
			ev_buf_type ev_buf;

			while (true)
			{
				unsigned qflags = queue->get_events(&ev_buf);

				if (qflags & thread::Queue::EVENT)
				{
					ev_buf_type::const_iterator const ev_buf_end = ev_buf.end();

					for (ev_buf_type::const_iterator it = ev_buf.begin(); it != ev_buf_end; ++it)
						appenders->appendLoopOnAppenders(*it);
				}

				if (((thread::Queue::EXIT | thread::Queue::DRAIN
					| thread::Queue::EVENT) & qflags)
					== (thread::Queue::EXIT | thread::Queue::DRAIN
						| thread::Queue::EVENT))
					continue;
				else if (thread::Queue::EXIT & qflags)
					break;
			}
		}


	} // namespace


	AsyncAppender::AsyncAppender(SharedAppenderPtr const & app,
		unsigned queue_len)
	{
		addAppender(app);
		init_queue_thread(queue_len);
	}


	AsyncAppender::AsyncAppender(helpers::Properties const & props)
		: Appender(props)
	{
		tstring const & appender_name(
			props.getProperty(LOGGING_TEXT("Appender")));
		if (appender_name.empty())
		{
			getErrorHandler()->error(
				LOGGING_TEXT("Unspecified appender for AsyncAppender."));
			return;
		}

		spi::AppenderFactoryRegistry & appender_registry
			= spi::getAppenderFactoryRegistry();
		spi::AppenderFactory * factory = appender_registry.get(appender_name);
		if (!factory)
		{
			helpers::getLogLog().error(
				LOGGING_TEXT("AsyncAppender::AsyncAppender()")
				LOGGING_TEXT(" - Cannot find AppenderFactory: ")
				+ appender_name, true);
		}

		helpers::Properties appender_props = props.getPropertySubset(
			LOGGING_TEXT("Appender."));
		addAppender(factory->createObject(appender_props));

		unsigned queue_len = 100;
		props.getUInt(queue_len, LOGGING_TEXT("QueueLimit"));

		init_queue_thread(queue_len);
	}


	AsyncAppender::~AsyncAppender()
	{
		destructorImpl();
	}


	void
		AsyncAppender::init_queue_thread(unsigned queue_len)
	{
		queue = new thread::Queue(queue_len);
		queue_thread = new QueueThread(AsyncAppenderPtr(this), queue);
		queue_thread->start();
		helpers::getLogLog().debug(LOGGING_TEXT("Queue thread started."));
	}


	void
		AsyncAppender::close()
	{
		if (queue)
		{
			unsigned ret = queue->signal_exit();
			if (ret & (thread::Queue::ERROR_BIT | thread::Queue::ERROR_AFTER))
				getErrorHandler()->error(
					LOGGING_TEXT("Error in AsyncAppender::close"));
		}

		if (queue_thread && queue_thread->isRunning())
			queue_thread->join();

		removeAllAppenders();

		queue_thread = nullptr;
		queue = nullptr;
	}


	void
		AsyncAppender::append(spi::InternalLoggingEvent const & ev)
	{
		if (queue_thread && queue_thread->isRunning())
		{
			unsigned ret = queue->put_event(ev);
			if (ret & (thread::Queue::ERROR_BIT | thread::Queue::ERROR_AFTER))
			{
				getErrorHandler()->error(
					LOGGING_TEXT("Error in AsyncAppender::append,")
					LOGGING_TEXT(" event queue has been lost."));
				// Exit the queue consumer thread without draining
				// the events queue.
				queue->signal_exit(false);
				queue_thread->join();
				queue_thread = nullptr;
				queue = nullptr;
				appendLoopOnAppenders(ev);
			}
		}
		else
		{
			// If the thread has died for any reason, fall back to synchronous
			// operation.
			appendLoopOnAppenders(ev);
		}
	}


} // namespace logging


#endif // #ifndef LOGGING_SINGLE_THREADED
