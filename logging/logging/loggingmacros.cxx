#include <logging/internal/internal.h>
#include <logging/loggingmacros.h>


namespace logging {
	namespace detail {


		//! Helper stream to get the defaults from.
		static tostringstream const macros_oss_defaults;

		// Individual defaults.

		static std::ios_base::fmtflags const default_flags
			= macros_oss_defaults.flags();
		static logging::tchar const default_fill = macros_oss_defaults.fill();
		static std::streamsize const default_precision
			= macros_oss_defaults.precision();
		static std::streamsize const default_width = macros_oss_defaults.width();

		//! Clears string stream using defaults taken from macros_oss_defaults.
		void
			clear_tostringstream(tostringstream & os)
		{
			os.clear();
			os.str(internal::empty_str);
			os.setf(default_flags);
			os.fill(default_fill);
			os.precision(default_precision);
			os.width(default_width);
#if defined (LOGGING_WORKING_LOCALE)
			std::locale glocale = std::locale();
			if (os.getloc() != glocale)
				os.imbue(glocale);
#endif // defined (LOGGING_WORKING_LOCALE)
		}


		logging::tostringstream &
			get_macro_body_oss()
		{
			tostringstream & oss = internal::get_ptd()->macros_oss;
			clear_tostringstream(oss);
			return oss;
		}


		logging::helpers::snprintf_buf &
			get_macro_body_snprintf_buf()
		{
			return internal::get_ptd()->snprintf_buf;
		}


		void
			macro_forced_log(logging::Logger const & logger,
				logging::LogLevel log_level, logging::tchar const * msg,
				char const * filename, int line, char const * func)
		{
			macro_forced_log(logger, log_level,
				internal::get_ptd()->macros_str = msg, filename, line, func);
		}


		void
			macro_forced_log(logging::Logger const & logger,
				logging::LogLevel log_level, logging::tstring const & msg,
				char const * filename, int line, char const * func)
		{
			logging::spi::InternalLoggingEvent & ev = internal::get_ptd()->forced_log_ev;
			ev.setLoggingEvent(logger.getName(), log_level, msg, filename, line, func);
			logger.forcedLog(ev);
		}


	}
} // namespace logging { namespace detail {
