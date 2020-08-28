#ifndef LOGGING_CALLBACK_APPENDER_HEADER_
#define LOGGING_CALLBACK_APPENDER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/appender.h>
#include <logging/clogger.h>


namespace logging {

	/**
	* Send log events to a C function callback.
	*/
	class LOGGING_EXPORT CallbackAppender
		: public Appender {
	public:
		CallbackAppender();
		CallbackAppender(LOGGING_log_event_callback_t callback, void * cookie);
		CallbackAppender(const logging::helpers::Properties&);

		virtual ~CallbackAppender();
		virtual void close();

		void setCookie(void *);
		void setCallback(LOGGING_log_event_callback_t);

	protected:
		virtual void append(const logging::spi::InternalLoggingEvent& event);

	private:
		LOGGING_log_event_callback_t callback;
		void * cookie;

		// Disallow copying of instances of this class
		CallbackAppender(const CallbackAppender&) = delete;
		CallbackAppender& operator=(const CallbackAppender&) = delete;
	};

} // end namespace logging

#endif // LOGGING_CALLBACK_APPENDER_HEADER_
