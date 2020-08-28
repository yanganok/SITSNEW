#ifndef LOGGING_CONSOLE_APPENDER_HEADER_
#define LOGGING_CONSOLE_APPENDER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/appender.h>

namespace logging {
	/**
	 * ConsoleAppender appends log events to <code>std::cout</code> or
	 * <code>std::cerr</code> using a layout specified by the
	 * user. The default target is <code>std::cout</code>.
	 *
	 * <h3>Properties</h3>
	 * <dl>
	 * <dt><tt>logToStdErr</tt></dt>
	 * <dd>When it is set true, the output stream will be
	 * <code>std::cerr</code> instead of <code>std::cout</code>.</dd>
	 *
	 * <dt><tt>ImmediateFlush</tt></dt>
	 * <dd>When it is set true, output stream will be flushed after
	 * each appended event.</dd>
	 *
	 * </dl>
	 * \sa Appender
	 */
	class LOGGING_EXPORT ConsoleAppender : public Appender {
	public:
		// Ctors

		ConsoleAppender(bool logToStdErr = false, bool immediateFlush = false);

		ConsoleAppender(const logging::helpers::Properties & properties);

		// Dtor
		~ConsoleAppender();

		// Methods
		virtual void close();

		//! This mutex is used by ConsoleAppender and helpers::LogLog
		//! classes to synchronize output to console.
		static logging::thread::Mutex const & getOutputMutex();

	protected:
		virtual void append(const spi::InternalLoggingEvent& event);

		// Data
		bool logToStdErr;
		/**
		 * Immediate flush means that the underlying output stream
		 * will be flushed at the end of each append operation.
		 */
		bool immediateFlush;
	};

} // end namespace logging

#endif // LOGGING_CONSOLE_APPENDER_HEADER_

