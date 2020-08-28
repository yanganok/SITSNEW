#ifndef LOGGING_NULL_APPENDER_HEADER_
#define LOGGING_NULL_APPENDER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/appender.h>


namespace logging {

	/**
	 * Appends log events to a file.
	 */
	class LOGGING_EXPORT NullAppender : public Appender {
	public:
		// Ctors
		NullAppender();
		NullAppender(const logging::helpers::Properties&);

		// Dtor
		virtual ~NullAppender();

		// Methods
		virtual void close();

	protected:
		virtual void append(const logging::spi::InternalLoggingEvent& event);

	private:
		// Disallow copying of instances of this class
		NullAppender(const NullAppender&);
		NullAppender& operator=(const NullAppender&);
	};

} // end namespace logging

#endif // LOGGING_NULL_APPENDER_HEADER_

