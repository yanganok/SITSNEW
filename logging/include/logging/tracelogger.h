#ifndef LOGGING_TRACELOGGER_H
#define LOGGING_TRACELOGGER_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/logger.h>


namespace logging
{


	/**
	 * This class is used to produce "Trace" logging.  When an instance of
	 * this class is created, it will log a <code>"ENTER: " + msg</code>
	 * log message if TRACE_LOG_LEVEL is enabled for <code>logger</code>.
	 * When an instance of this class is destroyed, it will log a
	 * <code>"ENTER: " + msg</code> log message if TRACE_LOG_LEVEL is enabled
	 * for <code>logger</code>.
	 * <p>
	 * @see LOGGING_TRACE
	 */
	class TraceLogger
	{
	public:
		TraceLogger(Logger l, logging::tstring _msg,
			const char* _file = LOGGING_CALLER_FILE(),
			int _line = LOGGING_CALLER_LINE(),
			char const * _function = LOGGING_CALLER_FUNCTION())
			: logger(std::move(l)), msg(std::move(_msg)), file(_file),
			function(_function), line(_line)
		{
			if (logger.isEnabledFor(TRACE_LOG_LEVEL))
				logger.forcedLog(TRACE_LOG_LEVEL, LOGGING_TEXT("ENTER: ") + msg,
					file, line, function);
		}

		~TraceLogger()
		{
			if (logger.isEnabledFor(TRACE_LOG_LEVEL))
				logger.forcedLog(TRACE_LOG_LEVEL, LOGGING_TEXT("EXIT:  ") + msg,
					file, line, function);
		}

	private:
		TraceLogger(TraceLogger const &);
		TraceLogger & operator = (TraceLogger const &);

		Logger logger;
		logging::tstring msg;
		const char* file;
		const char* function;
		int line;
	};


} // logging


#endif // LOGGING_TRACELOGGER_H
