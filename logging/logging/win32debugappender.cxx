#include <logging/config.hxx>
#if defined (LOGGING_HAVE_OUTPUTDEBUGSTRING)

#include <logging/config/windowsh-inc.h>
#include <logging/win32debugappender.h>
#include <logging/internal/internal.h>
#include <logging/internal/cygwin-win32.h>
#include <logging/thread/syncprims-pub-impl.h>


namespace logging
{


	///////////////////////////////////////////////////////////////////////////////
	// Win32DebugAppender ctors and dtor
	///////////////////////////////////////////////////////////////////////////////

	Win32DebugAppender::Win32DebugAppender()
	{
	}


	Win32DebugAppender::Win32DebugAppender(
		const helpers::Properties& properties)
		: Appender(properties)
	{
	}



	Win32DebugAppender::~Win32DebugAppender()
	{
		destructorImpl();
	}



	///////////////////////////////////////////////////////////////////////////////
	// Win32DebugAppender public methods
	///////////////////////////////////////////////////////////////////////////////

	void
		Win32DebugAppender::close()
	{
		closed = true;
	}



	///////////////////////////////////////////////////////////////////////////////
	// Win32DebugAppender protected methods
	///////////////////////////////////////////////////////////////////////////////

	// This method does not need to be locked since it is called by
	// doAppend() which performs the locking
	void
		Win32DebugAppender::append(const spi::InternalLoggingEvent& event)
	{
#if defined (__CYGWIN__)
		cygwin::output_debug_stringW(
			helpers::towstring(formatEvent(event)).c_str());
#else
		const tchar * s = formatEvent(event).c_str();
		::OutputDebugString(s);
#endif
	}


} // namespace logging


#endif // LOGGING_HAVE_OUTPUTDEBUGSTRING
