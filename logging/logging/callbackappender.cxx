#include <logging/callbackappender.h>
#include <logging/spi/loggingevent.h>
#include <logging/helpers/timehelper.h>
#include <logging/thread/syncprims-pub-impl.h>


namespace logging
{


	CallbackAppender::CallbackAppender()
	{ }


	CallbackAppender::CallbackAppender(LOGGING_log_event_callback_t callback_,
		void * cookie_)
		: callback(callback_)
		, cookie(cookie_)
	{ }


	CallbackAppender::CallbackAppender(const helpers::Properties& properties)
		: Appender(properties)
	{ }


	CallbackAppender::~CallbackAppender()
	{
		destructorImpl();
	}


	void
		CallbackAppender::close()
	{
	}


	void
		CallbackAppender::append(const spi::InternalLoggingEvent& ev)
	{
		if (callback)
		{
			helpers::Time const & t = ev.getTimestamp();
			callback(cookie, ev.getMessage().c_str(),
				ev.getLoggerName().c_str(), ev.getLogLevel(),
				ev.getThread().c_str(), ev.getThread2().c_str(),
				static_cast<unsigned long long>(helpers::to_time_t(t)),
				static_cast<unsigned long>(helpers::microseconds_part(t)),
				ev.getFile().c_str(),
				ev.getFunction().c_str(), ev.getLine());
		}
	}


} // namespace logging
