#ifndef LOGGING_ASYNCAPPENDER_H
#define LOGGING_ASYNCAPPENDER_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#ifndef LOGGING_SINGLE_THREADED

#include <logging/helpers/queue.h>
#include <logging/appender.h>
#include <logging/thread/threads.h>
#include <logging/helpers/appenderattachableimpl.h>


namespace logging
{


	/**
	   This `Appender` is a wrapper to which other appenders can be attached. The
	   attached appendres are then appended to from a separate thread which reads
	   events appended to this appender from a queue.

	   <h3>Properties</h3>
	   <dl>

	   <dt><tt>QueueLimit</tt></dt>
	   <dd>Events queue size limit. Default is 100.</dd>
	   </dt>

	   <dt><tt>Appender</tt></dt>
	   <dd>`Appender` and its properties to use as sink for logged events.</dd>
	   </dt>

	   </dl>

	   \sa helpers::AppenderAttachableImpl
	 */
	class LOGGING_EXPORT AsyncAppender
		: public Appender
		, public helpers::AppenderAttachableImpl
	{
	public:
		AsyncAppender(SharedAppenderPtr const & app, unsigned max_len);
		AsyncAppender(helpers::Properties const &);
		virtual ~AsyncAppender();

		virtual void close();

	protected:
		virtual void append(spi::InternalLoggingEvent const &);

		void init_queue_thread(unsigned);

		thread::AbstractThreadPtr queue_thread;
		thread::QueuePtr queue;

	private:
		AsyncAppender(AsyncAppender const &);
		AsyncAppender & operator = (AsyncAppender const &);
	};


	typedef helpers::SharedObjectPtr<AsyncAppender> AsyncAppenderPtr;


} // namespace logging


#endif // LOGGING_SINGLE_THREADED

#endif // LOGGING_ASYNCAPPENDER_H
