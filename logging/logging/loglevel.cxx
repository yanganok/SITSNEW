#include <logging/loglevel.h>
#include <logging/helpers/loglog.h>
#include <logging/helpers/stringhelper.h>
#include <logging/internal/internal.h>
#include <algorithm>


namespace logging
{


	namespace
	{

		static tstring const ALL_STRING(LOGGING_TEXT("ALL"));
		static tstring const TRACE_STRING(LOGGING_TEXT("TRACE"));
		static tstring const DEBUG_STRING(LOGGING_TEXT("DEBUG"));
		static tstring const INFO_STRING(LOGGING_TEXT("INFO"));
		static tstring const WARN_STRING(LOGGING_TEXT("WARN"));
		static tstring const ERROR_STRING(LOGGING_TEXT("ERROR"));
		static tstring const FATAL_STRING(LOGGING_TEXT("FATAL"));
		static tstring const OFF_STRING(LOGGING_TEXT("OFF"));
		static tstring const NOTSET_STRING(LOGGING_TEXT("NOTSET"));
		static tstring const UNKNOWN_STRING(LOGGING_TEXT("UNKNOWN"));


		static
			tstring const &
			defaultLogLevelToStringMethod(LogLevel ll)
		{
			switch (ll) {
			case OFF_LOG_LEVEL:     return OFF_STRING;
			case FATAL_LOG_LEVEL:   return FATAL_STRING;
			case ERROR_LOG_LEVEL:   return ERROR_STRING;
			case WARN_LOG_LEVEL:    return WARN_STRING;
			case INFO_LOG_LEVEL:    return INFO_STRING;
			case DEBUG_LOG_LEVEL:   return DEBUG_STRING;
			case TRACE_LOG_LEVEL:   return TRACE_STRING;
				//case ALL_LOG_LEVEL:     return ALL_STRING;
			case NOT_SET_LOG_LEVEL: return NOTSET_STRING;
			};

			return internal::empty_str;
		}


		static
			LogLevel
			defaultStringToLogLevelMethod(const tstring& s)
		{
			// Since C++11, accessing str[0] is always safe as it returns '\0' for
			// empty string.

			switch (s[0])
			{
#define DEF_LLMATCH(_chr, _logLevel)                 \
        case LOGGING_TEXT (_chr):                  \
            if (s == _logLevel ## _STRING)           \
                return _logLevel ## _LOG_LEVEL;      \
            else                                     \
                break;

				DEF_LLMATCH('O', OFF);
				DEF_LLMATCH('F', FATAL);
				DEF_LLMATCH('E', ERROR);
				DEF_LLMATCH('W', WARN);
				DEF_LLMATCH('I', INFO);
				DEF_LLMATCH('D', DEBUG);
				DEF_LLMATCH('T', TRACE);
				DEF_LLMATCH('A', ALL);

#undef DEF_LLMATCH
			}

			return NOT_SET_LOG_LEVEL;
		}

	} // namespace



	//////////////////////////////////////////////////////////////////////////////
	// LogLevelManager ctors and dtor
	//////////////////////////////////////////////////////////////////////////////

	LogLevelManager::LogLevelManager()
	{
		pushToStringMethod(defaultLogLevelToStringMethod);

		pushFromStringMethod(defaultStringToLogLevelMethod);
	}


	LogLevelManager::~LogLevelManager()
	{ }



	//////////////////////////////////////////////////////////////////////////////
	// LogLevelManager public methods
	//////////////////////////////////////////////////////////////////////////////

	tstring const &
		LogLevelManager::toString(LogLevel ll) const
	{
		for (LogLevelToStringMethodRec const & rec : toStringMethods)
		{
			tstring const & ret = rec.func(ll);
			if (!ret.empty())
				return ret;
		}

		return UNKNOWN_STRING;
	}


	LogLevel
		LogLevelManager::fromString(const tstring& arg) const
	{
		tstring const s = helpers::toUpper(arg);

		for (auto func : fromStringMethods)
		{
			LogLevel ret = func(s);
			if (ret != NOT_SET_LOG_LEVEL)
				return ret;
		}

		helpers::getLogLog().error(
			LOGGING_TEXT("Unrecognized log level: ")
			+ arg);

		return NOT_SET_LOG_LEVEL;
	}


	void
		LogLevelManager::pushToStringMethod(LogLevelToStringMethod newToString)
	{
		toStringMethods.emplace(toStringMethods.begin(), newToString);
	}


	void
		LogLevelManager::pushFromStringMethod(StringToLogLevelMethod newFromString)
	{
		fromStringMethods.push_back(newFromString);
	}


	//
	//
	//

	LogLevelManager::LogLevelToStringMethodRec::LogLevelToStringMethodRec()
	{ }


	LogLevelManager::LogLevelToStringMethodRec::LogLevelToStringMethodRec(
		LogLevelToStringMethod f)
		: func{ f }
	{ }


} // namespace logging
