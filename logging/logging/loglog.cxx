#include <logging/streams.h>
#include <logging/helpers/loglog.h>
#include <logging/thread/syncprims-pub-impl.h>
#include <logging/thread/threads.h>
#include <logging/internal/env.h>
#include <logging/consoleappender.h>
#include <ostream>
#include <stdexcept>


namespace logging {
	namespace helpers {

		namespace
		{

			static tchar const PREFIX[] = LOGGING_TEXT("logging: ");
			static tchar const WARN_PREFIX[] = LOGGING_TEXT("logging:WARN ");
			static tchar const ERR_PREFIX[] = LOGGING_TEXT("logging:ERROR ");

		} // namespace


		LogLog *
			LogLog::getLogLog()
		{
			return &helpers::getLogLog();
		}


		LogLog::LogLog()
			: debugEnabled(TriUndef)
			, quietMode(TriUndef)
		{ }


		LogLog::~LogLog()
		{ }


		void
			LogLog::setInternalDebugging(bool enabled)
		{
			thread::MutexGuard guard(mutex);

			debugEnabled = enabled ? TriTrue : TriFalse;
		}


		void
			LogLog::setQuietMode(bool quietModeVal)
		{
			thread::MutexGuard guard(mutex);

			quietMode = quietModeVal ? TriTrue : TriFalse;
		}


		void
			LogLog::debug(const logging::tstring& msg) const
		{
			logging_worker(tcout, &LogLog::get_debug_mode, PREFIX, msg);
		}


		void
			LogLog::debug(tchar const * msg) const
		{
			logging_worker(tcout, &LogLog::get_debug_mode, PREFIX, msg);
		}


		void
			LogLog::warn(const logging::tstring& msg) const
		{
			logging_worker(tcerr, &LogLog::get_not_quiet_mode, WARN_PREFIX, msg);
		}


		void
			LogLog::warn(tchar const * msg) const
		{
			logging_worker(tcerr, &LogLog::get_not_quiet_mode, WARN_PREFIX, msg);
		}


		void
			LogLog::error(const logging::tstring& msg, bool throw_flag) const
		{
			logging_worker(tcerr, &LogLog::get_not_quiet_mode, ERR_PREFIX, msg,
				throw_flag);
		}


		void
			LogLog::error(tchar const * msg, bool throw_flag) const
		{
			logging_worker(tcerr, &LogLog::get_not_quiet_mode, ERR_PREFIX, msg,
				throw_flag);
		}


		bool
			LogLog::get_quiet_mode() const
		{
			if (LOGGING_UNLIKELY(quietMode == TriUndef))
				set_tristate_from_env(&quietMode,
					LOGGING_TEXT("LOGGING_LOGLOG_QUIETMODE"));

			return quietMode == TriTrue;
		}


		bool
			LogLog::get_not_quiet_mode() const
		{
			return !get_quiet_mode();
		}


		bool
			LogLog::get_debug_mode() const
		{
			if (LOGGING_UNLIKELY(debugEnabled == TriUndef))
				set_tristate_from_env(&debugEnabled,
					LOGGING_TEXT("LOGGING_LOGLOG_DEBUGENABLED"));

			return debugEnabled && !get_quiet_mode();
		}


		void
			LogLog::set_tristate_from_env(TriState * result, tchar const * envvar_name)
		{
			tstring envvar_value;
			bool exists = internal::get_env_var(envvar_value, envvar_name);
			bool value = false;
			if (exists && internal::parse_bool(value, envvar_value) && value)
				*result = TriTrue;
			else
				*result = TriFalse;
		}


		template <typename StringType>
		void
			LogLog::logging_worker(tostream & os, bool (LogLog:: * cond) () const,
				tchar const * prefix, StringType const & msg, bool throw_flag) const
		{
			bool output;
			{
				thread::MutexGuard guard(mutex);
				output = (this->*cond) ();
			}

			if (LOGGING_UNLIKELY(output))
			{
				// XXX This is potential recursive lock of
				// ConsoleAppender::outputMutex.
				thread::MutexGuard outputGuard(ConsoleAppender::getOutputMutex());
				os << prefix << msg << std::endl;
			}

			if (LOGGING_UNLIKELY(throw_flag))
				throw std::runtime_error(LOGGING_TSTRING_TO_STRING(msg));
		}


	}
} // namespace logging { namespace helpers {
