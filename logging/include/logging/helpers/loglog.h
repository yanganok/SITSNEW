#ifndef LOGGING_HELPERS_LOGLOG
#define LOGGING_HELPERS_LOGLOG

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/tstring.h>
#include <logging/streams.h>
#include <logging/thread/syncprims.h>


namespace logging {
	namespace helpers {

		/**
		 * This class used to output log statements from within the logging package.
		 *
		 * logging components cannot make logging logging calls. However, it is
		 * sometimes useful for the user to learn about what logging is
		 * doing. You can enable logging internal logging by defining the
		 * <b>logging.configDebug</b> variable.
		 *
		 * All logging internal debug calls go to <code>cout</code>
		 * where as internal error messages are sent to
		 * <code>cerr</code>. All internal messages are prepended with
		 * the string "log4clus: ".
		 */
		class LOGGING_EXPORT LogLog
		{
		public:
			//! Return type of getLogLog().
			typedef LogLog * Ptr;

			/**
			 * Returns a reference to the <code>LogLog</code> singleton.
			 */
			static Ptr getLogLog();


			/**
			 * Allows to enable/disable logging internal logging.
			 */
			void setInternalDebugging(bool enabled);

			/**
			 * In quite mode no LogLog generates strictly no output, not even
			 * for errors.
			 *
			 * @param quietMode A true for not
			 */
			void setQuietMode(bool quietMode);

			/**
			 * This method is used to output logging internal debug
			 * statements. Output goes to <code>std::cout</code>.
			 */
			void debug(const logging::tstring& msg) const;
			void debug(tchar const * msg) const;

			/**
			 * This method is used to output logging internal error
			 * statements. There is no way to disable error
			 * statements.  Output goes to
			 * <code>std::cerr</code>. Optionally, this method can
			 * throw std::runtime_error exception too.
			 */
			void error(const logging::tstring& msg, bool throw_flag = false) const;
			void error(tchar const * msg, bool throw_flag = false) const;

			/**
			 * This method is used to output logging internal warning
			 * statements. There is no way to disable warning statements.
			 * Output goes to <code>std::cerr</code>.
			 */
			void warn(const logging::tstring& msg) const;
			void warn(tchar const * msg) const;

			// Public ctor and dtor to be used only by internal::DefaultContext.
			LogLog();
			virtual ~LogLog();

		private:
			enum TriState
			{
				TriUndef = -1,
				TriFalse,
				TriTrue
			};

			template <typename StringType>
			LOGGING_PRIVATE
				void logging_worker(tostream & os,
					bool (LogLog:: * cond) () const, tchar const *,
					StringType const &, bool throw_flag = false) const;

			LOGGING_PRIVATE static void set_tristate_from_env(TriState *,
				tchar const * envvar);

			LOGGING_PRIVATE bool get_quiet_mode() const;
			LOGGING_PRIVATE bool get_not_quiet_mode() const;
			LOGGING_PRIVATE bool get_debug_mode() const;

			// Data
			mutable TriState debugEnabled;
			mutable TriState quietMode;
			thread::Mutex mutex;

			LOGGING_PRIVATE LogLog(const LogLog&);
			LOGGING_PRIVATE LogLog & operator = (LogLog const &);
		};

		LOGGING_EXPORT LogLog & getLogLog();

	} // end namespace helpers
} // end namespace logging


#endif // LOGGING_HELPERS_LOGLOG

