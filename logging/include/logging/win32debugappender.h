#ifndef LOGGING_WIN32DEBUG_APPENDER_HEADER_
#define LOGGING_WIN32DEBUG_APPENDER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#if defined (LOGGING_HAVE_OUTPUTDEBUGSTRING) 

#include <logging/appender.h>


namespace logging {

	/**
	 * Prints log events using OutputDebugString().
	 */
	class LOGGING_EXPORT Win32DebugAppender
		: public Appender
	{
	public:
		// Ctors
		Win32DebugAppender();
		Win32DebugAppender(const logging::helpers::Properties& properties);

		// Dtor
		virtual ~Win32DebugAppender();

		// Methods
		virtual void close();

	protected:
		virtual void append(const logging::spi::InternalLoggingEvent& event);

	private:
		// Disallow copying of instances of this class
		Win32DebugAppender(const Win32DebugAppender&);
		Win32DebugAppender& operator=(const Win32DebugAppender&);
	};

} // end namespace logging

#endif // LOGGING_HAVE_OUTPUTDEBUGSTRING
#endif // LOGGING_WIN32DEBUG_APPENDER_HEADER_
