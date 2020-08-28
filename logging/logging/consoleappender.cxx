#include <logging/layout.h>
#include <logging/consoleappender.h>
#include <logging/streams.h>
#include <logging/helpers/loglog.h>
#include <logging/helpers/stringhelper.h>
#include <logging/helpers/property.h>
#include <logging/spi/loggingevent.h>
#include <logging/thread/syncprims-pub-impl.h>
#include <ostream>


namespace logging
{


	namespace helpers
	{

		extern logging::thread::Mutex const & getConsoleOutputMutex();

	} // namespace helpers


	logging::thread::Mutex const &
		ConsoleAppender::getOutputMutex()
	{
		return helpers::getConsoleOutputMutex();
	}


	//////////////////////////////////////////////////////////////////////////////
	// ConsoleAppender ctors and dtor
	//////////////////////////////////////////////////////////////////////////////

	ConsoleAppender::ConsoleAppender(bool logToStdErr_,
		bool immediateFlush_)
		: logToStdErr(logToStdErr_),
		immediateFlush(immediateFlush_)
	{
	}



	ConsoleAppender::ConsoleAppender(const helpers::Properties & properties)
		: Appender(properties),
		logToStdErr(false),
		immediateFlush(false)
	{
		properties.getBool(logToStdErr, LOGGING_TEXT("logToStdErr"));
		properties.getBool(immediateFlush, LOGGING_TEXT("ImmediateFlush"));
	}



	ConsoleAppender::~ConsoleAppender()
	{
		destructorImpl();
	}



	//////////////////////////////////////////////////////////////////////////////
	// ConsoleAppender public methods
	//////////////////////////////////////////////////////////////////////////////

	void
		ConsoleAppender::close()
	{
		helpers::getLogLog().debug(
			LOGGING_TEXT("Entering ConsoleAppender::close().."));
		closed = true;
	}



	//////////////////////////////////////////////////////////////////////////////
	// ConsoleAppender protected methods
	//////////////////////////////////////////////////////////////////////////////

	void
		ConsoleAppender::append(const spi::InternalLoggingEvent& event)
	{
		thread::MutexGuard guard(getOutputMutex());

		tostream& output = (logToStdErr ? tcerr : tcout);
		layout->formatAndAppend(output, event);
		if (immediateFlush) {
			output.flush();
		}
	}


} // namespace logging
