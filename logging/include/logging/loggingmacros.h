#ifndef LOGGING_LOGGING_MACROS_HEADER_
#define LOGGING_LOGGING_MACROS_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/streams.h>
#include <logging/logger.h>
#include <logging/helpers/snprintf.h>
#include <logging/tracelogger.h>
#include <sstream>
#include <utility>


#if defined(_MSC_VER)
#define LOGGING_SUPPRESS_DOWHILE_WARNING()  \
    __pragma (warning (push))                 \
    __pragma (warning (disable:4127))

#define LOGGING_RESTORE_DOWHILE_WARNING()   \
    __pragma (warning (pop))

#else
#define LOGGING_SUPPRESS_DOWHILE_WARNING() /* empty */
#define LOGGING_RESTORE_DOWHILE_WARNING() /* empty */

#endif

#define LOGGING_DOWHILE_NOTHING()                 \
    LOGGING_SUPPRESS_DOWHILE_WARNING()            \
    do { } while (0)                                \
    LOGGING_RESTORE_DOWHILE_WARNING()

#if defined(LOGGING_DISABLE_FATAL) && !defined(LOGGING_DISABLE_ERROR)
#define LOGGING_DISABLE_ERROR
#endif
#if defined(LOGGING_DISABLE_ERROR) && !defined(LOGGING_DISABLE_WARN)
#define LOGGING_DISABLE_WARN
#endif
#if defined(LOGGING_DISABLE_WARN) && !defined(LOGGING_DISABLE_INFO)
#define LOGGING_DISABLE_INFO
#endif
#if defined(LOGGING_DISABLE_INFO) && !defined(LOGGING_DISABLE_DEBUG)
#define LOGGING_DISABLE_DEBUG
#endif
#if defined(LOGGING_DISABLE_DEBUG) && !defined(LOGGING_DISABLE_TRACE)
#define LOGGING_DISABLE_TRACE
#endif


namespace logging
{

	namespace detail
	{


		inline
			Logger
			macros_get_logger(Logger const & logger)
		{
			return logger;
		}


		inline
			Logger const &
			macros_get_logger(Logger & logger)
		{
			return logger;
		}


		inline
			Logger
			macros_get_logger(Logger && logger)
		{
			return std::move(logger);
		}

		inline
			Logger
			macros_get_logger(tstring const & logger)
		{
			return Logger::getInstance(logger);
		}


		inline
			Logger
			macros_get_logger(tchar const * logger)
		{
			return Logger::getInstance(logger);
		}


		LOGGING_EXPORT void clear_tostringstream(tostringstream &);


		LOGGING_EXPORT logging::tostringstream & get_macro_body_oss();
		LOGGING_EXPORT logging::helpers::snprintf_buf & get_macro_body_snprintf_buf();
		LOGGING_EXPORT void macro_forced_log(logging::Logger const &,
			logging::LogLevel, logging::tstring const &, char const *, int,
			char const *);
		LOGGING_EXPORT void macro_forced_log(logging::Logger const &,
			logging::LogLevel, logging::tchar const *, char const *, int,
			char const *);



	} // namespace detail

} // namespace logging


#undef LOGGING_MACRO_FUNCTION
#define LOGGING_MACRO_FUNCTION() nullptr
#if ! defined (LOGGING_DISABLE_FUNCTION_MACRO)
#  if defined (LOGGING_HAVE_FUNCSIG_MACRO)
#    undef LOGGING_MACRO_FUNCTION
#    define LOGGING_MACRO_FUNCTION() __FUNCSIG__
#  elif defined (LOGGING_HAVE_PRETTY_FUNCTION_MACRO)
#    undef LOGGING_MACRO_FUNCTION
#    define LOGGING_MACRO_FUNCTION() __PRETTY_FUNCTION__
#  elif defined (LOGGING_HAVE_FUNCTION_MACRO)
#    undef LOGGING_MACRO_FUNCTION
#    define LOGGING_MACRO_FUNCTION() __FUNCTION__
#  elif defined (LOGGING_HAVE_FUNC_SYMBOL)
#    undef LOGGING_MACRO_FUNCTION
#    define LOGGING_MACRO_FUNCTION() __func__
#  endif
#endif

#undef LOGGING_MACRO_FILE
#define LOGGING_MACRO_FILE() nullptr
#if ! defined (LOGGING_DISABLE_FILE_MACRO)
#  undef LOGGING_MACRO_FILE
#  define LOGGING_MACRO_FILE() __FILE__
#endif


// Make TRACE and DEBUG log level unlikely and INFO, WARN, ERROR and FATAL log level likely.
#define LOGGING_MACRO_TRACE_LOG_LEVEL(pred) \
    LOGGING_UNLIKELY (pred)
#define LOGGING_MACRO_DEBUG_LOG_LEVEL(pred) \
    LOGGING_UNLIKELY (pred)
#define LOGGING_MACRO_INFO_LOG_LEVEL(pred) \
    LOGGING_LIKELY (pred)
#define LOGGING_MACRO_WARN_LOG_LEVEL(pred) \
    LOGGING_LIKELY (pred)
#define LOGGING_MACRO_ERROR_LOG_LEVEL(pred) \
    LOGGING_LIKELY (pred)
#define LOGGING_MACRO_FATAL_LOG_LEVEL(pred) \
    LOGGING_LIKELY (pred)


//! Dispatch to LOGGING_MACRO_LOGLEVEL_* depending on log level.
#define LOGGING_MACRO_LOGLEVEL_PRED(pred, logLevel)    \
    LOGGING_MACRO_ ## logLevel (pred)


// Either use temporary instances of ostringstream
// and snprintf_buf, or use thread-local instances.
#if defined (LOGGING_MACRO_DISABLE_TLS)
#  define LOGGING_MACRO_INSTANTIATE_OSTRINGSTREAM(var)    \
    logging::tostringstream var

#  define LOGGING_MACRO_INSTANTIATE_SNPRINTF_BUF(var)     \
    logging::helpers::snprintf_buf var

#else
#  define LOGGING_MACRO_INSTANTIATE_OSTRINGSTREAM(var)    \
    logging::tostringstream & var                         \
        = logging::detail::get_macro_body_oss ()

#  define LOGGING_MACRO_INSTANTIATE_SNPRINTF_BUF(var)     \
    logging::helpers::snprintf_buf & var                  \
        = logging::detail::get_macro_body_snprintf_buf ()

#endif


#define LOGGING_MACRO_BODY(logger, logEvent, logLevel)                \
    LOGGING_SUPPRESS_DOWHILE_WARNING()                                \
    do {                                                                \
        logging::Logger const & _l                                    \
            = logging::detail::macros_get_logger (logger);            \
        if (LOGGING_MACRO_LOGLEVEL_PRED (                             \
                _l.isEnabledFor (logging::logLevel), logLevel)) {     \
            LOGGING_MACRO_INSTANTIATE_OSTRINGSTREAM (_LOGGING_buf); \
            _LOGGING_buf << logEvent;                                 \
            logging::detail::macro_forced_log (_l,                    \
                logging::logLevel, _LOGGING_buf.str(),              \
                LOGGING_MACRO_FILE (), __LINE__,                      \
                LOGGING_MACRO_FUNCTION ());                           \
        }                                                               \
    } while (0)                                                         \
    LOGGING_RESTORE_DOWHILE_WARNING()


#define LOGGING_MACRO_STR_BODY(logger, logEvent, logLevel)            \
    LOGGING_SUPPRESS_DOWHILE_WARNING()                                \
    do {                                                                \
        logging::Logger const & _l                                    \
            = logging::detail::macros_get_logger (logger);            \
        if (LOGGING_MACRO_LOGLEVEL_PRED (                             \
                _l.isEnabledFor (logging::logLevel), logLevel)) {     \
            logging::detail::macro_forced_log (_l,                    \
                logging::logLevel, logEvent,                          \
                LOGGING_MACRO_FILE (), __LINE__,                      \
                LOGGING_MACRO_FUNCTION ());                           \
        }                                                               \
    } while(0)                                                          \
    LOGGING_RESTORE_DOWHILE_WARNING()

#define LOGGING_MACRO_FMT_BODY(logger, logLevel, ...)                 \
    LOGGING_SUPPRESS_DOWHILE_WARNING()                                \
    do {                                                                \
        logging::Logger const & _l                                    \
            = logging::detail::macros_get_logger (logger);            \
        if (LOGGING_MACRO_LOGLEVEL_PRED (                             \
                _l.isEnabledFor (logging::logLevel), logLevel)) {     \
            LOGGING_MACRO_INSTANTIATE_SNPRINTF_BUF (_snpbuf);         \
            logging::tchar const * _logEvent                          \
                = _snpbuf.print (__VA_ARGS__);                          \
            logging::detail::macro_forced_log (_l,                    \
                logging::logLevel, _logEvent,                         \
                LOGGING_MACRO_FILE (), __LINE__,                      \
                LOGGING_MACRO_FUNCTION ());                           \
        }                                                               \
    } while(0)                                                          \
    LOGGING_RESTORE_DOWHILE_WARNING()

/**
 * @def LOGGING_TRACE(logger, logEvent) This macro creates a
 * TraceLogger to log a TRACE_LOG_LEVEL message to <code>logger</code>
 * upon entry and exiting of a method.
 * <code>logEvent</code> will be streamed into an <code>ostream</code>.
 */
#if !defined(LOGGING_DISABLE_TRACE)
#define LOGGING_TRACE_METHOD(logger, logEvent)                        \
    logging::TraceLogger _LOGGING_trace_logger(logger, logEvent,    \
        LOGGING_MACRO_FILE (), __LINE__,                              \
        LOGGING_MACRO_FUNCTION ());
#define LOGGING_TRACE(logger, logEvent)                               \
    LOGGING_MACRO_BODY (logger, logEvent, TRACE_LOG_LEVEL)
#define LOGGING_TRACE_STR(logger, logEvent)                           \
    LOGGING_MACRO_STR_BODY (logger, logEvent, TRACE_LOG_LEVEL)
#define LOGGING_TRACE_FMT(logger, ...)                                \
    LOGGING_MACRO_FMT_BODY (logger, TRACE_LOG_LEVEL, __VA_ARGS__)

#else
#define LOGGING_TRACE_METHOD(logger, logEvent) LOGGING_DOWHILE_NOTHING()
#define LOGGING_TRACE(logger, logEvent) LOGGING_DOWHILE_NOTHING()
#define LOGGING_TRACE_STR(logger, logEvent) LOGGING_DOWHILE_NOTHING()
#define LOGGING_TRACE_FMT(logger, logFmt, ...) LOGGING_DOWHILE_NOTHING()

#endif

 /**
  * @def LOGGING_DEBUG(logger, logEvent)  This macro is used to log a
  * DEBUG_LOG_LEVEL message to <code>logger</code>.
  * <code>logEvent</code> will be streamed into an <code>ostream</code>.
  */
#if !defined(LOGGING_DISABLE_DEBUG)
#define LOGGING_DEBUG(logger, logEvent)                               \
    LOGGING_MACRO_BODY (logger, logEvent, DEBUG_LOG_LEVEL)
#define LOGGING_DEBUG_STR(logger, logEvent)                           \
    LOGGING_MACRO_STR_BODY (logger, logEvent, DEBUG_LOG_LEVEL)
#define LOGGING_DEBUG_FMT(logger, ...)                                \
    LOGGING_MACRO_FMT_BODY (logger, DEBUG_LOG_LEVEL, __VA_ARGS__)

#else
#define LOGGING_DEBUG(logger, logEvent) LOGGING_DOWHILE_NOTHING()
#define LOGGING_DEBUG_STR(logger, logEvent) LOGGING_DOWHILE_NOTHING()
#define LOGGING_DEBUG_FMT(logger, ...) LOGGING_DOWHILE_NOTHING()

#endif

  /**
   * @def LOGGING_INFO(logger, logEvent)  This macro is used to log a
   * INFO_LOG_LEVEL message to <code>logger</code>.
   * <code>logEvent</code> will be streamed into an <code>ostream</code>.
   */
#if !defined(LOGGING_DISABLE_INFO)
#define LOGGING_INFO(logger, logEvent)                                \
    LOGGING_MACRO_BODY (logger, logEvent, INFO_LOG_LEVEL)
#define LOGGING_INFO_STR(logger, logEvent)                            \
    LOGGING_MACRO_STR_BODY (logger, logEvent, INFO_LOG_LEVEL)
#define LOGGING_INFO_FMT(logger, ...)                                 \
    LOGGING_MACRO_FMT_BODY (logger, INFO_LOG_LEVEL, __VA_ARGS__)

#else
#define LOGGING_INFO(logger, logEvent) LOGGING_DOWHILE_NOTHING()
#define LOGGING_INFO_STR(logger, logEvent) LOGGING_DOWHILE_NOTHING()
#define LOGGING_INFO_FMT(logger, ...) LOGGING_DOWHILE_NOTHING()

#endif

   /**
	* @def LOGGING_WARN(logger, logEvent)  This macro is used to log a
	* WARN_LOG_LEVEL message to <code>logger</code>.
	* <code>logEvent</code> will be streamed into an <code>ostream</code>.
	*/
#if !defined(LOGGING_DISABLE_WARN)
#define LOGGING_WARN(logger, logEvent)                                \
    LOGGING_MACRO_BODY (logger, logEvent, WARN_LOG_LEVEL)
#define LOGGING_WARN_STR(logger, logEvent)                            \
    LOGGING_MACRO_STR_BODY (logger, logEvent, WARN_LOG_LEVEL)
#define LOGGING_WARN_FMT(logger, ...)                                 \
    LOGGING_MACRO_FMT_BODY (logger, WARN_LOG_LEVEL, __VA_ARGS__)

#else
#define LOGGING_WARN(logger, logEvent) LOGGING_DOWHILE_NOTHING()
#define LOGGING_WARN_STR(logger, logEvent) LOGGING_DOWHILE_NOTHING()
#define LOGGING_WARN_FMT(logger, ...) LOGGING_DOWHILE_NOTHING()

#endif

	/**
	 * @def LOGGING_ERROR(logger, logEvent)  This macro is used to log a
	 * ERROR_LOG_LEVEL message to <code>logger</code>.
	 * <code>logEvent</code> will be streamed into an <code>ostream</code>.
	 */
#if !defined(LOGGING_DISABLE_ERROR)
#define LOGGING_ERROR(logger, logEvent)                               \
    LOGGING_MACRO_BODY (logger, logEvent, ERROR_LOG_LEVEL)
#define LOGGING_ERROR_STR(logger, logEvent)                           \
    LOGGING_MACRO_STR_BODY (logger, logEvent, ERROR_LOG_LEVEL)
#define LOGGING_ERROR_FMT(logger, ...)                                \
    LOGGING_MACRO_FMT_BODY (logger, ERROR_LOG_LEVEL, __VA_ARGS__)

#else
#define LOGGING_ERROR(logger, logEvent) LOGGING_DOWHILE_NOTHING()
#define LOGGING_ERROR_STR(logger, logEvent) LOGGING_DOWHILE_NOTHING()
#define LOGGING_ERROR_FMT(logger, ...) LOGGING_DOWHILE_NOTHING()

#endif

	 /**
	  * @def LOGGING_FATAL(logger, logEvent)  This macro is used to log a
	  * FATAL_LOG_LEVEL message to <code>logger</code>.
	  * <code>logEvent</code> will be streamed into an <code>ostream</code>.
	  */
#if !defined(LOGGING_DISABLE_FATAL)
#define LOGGING_FATAL(logger, logEvent)                               \
    LOGGING_MACRO_BODY (logger, logEvent, FATAL_LOG_LEVEL)
#define LOGGING_FATAL_STR(logger, logEvent)                           \
    LOGGING_MACRO_STR_BODY (logger, logEvent, FATAL_LOG_LEVEL)
#define LOGGING_FATAL_FMT(logger, ...)                                \
    LOGGING_MACRO_FMT_BODY (logger, FATAL_LOG_LEVEL, __VA_ARGS__)

#else
#define LOGGING_FATAL(logger, logEvent) LOGGING_DOWHILE_NOTHING()
#define LOGGING_FATAL_STR(logger, logEvent) LOGGING_DOWHILE_NOTHING()
#define LOGGING_FATAL_FMT(logger, ...) LOGGING_DOWHILE_NOTHING()

#endif

	  //! Helper macro for LOGGING_ASSERT() macro.
#define LOGGING_ASSERT_STRINGIFY(X) #X

//! If the condition given in second parameter evaluates false, this
//! macro logs it using FATAL log level, including the condition's
//! source text.
#define LOGGING_ASSERT(logger, condition)                             \
    LOGGING_SUPPRESS_DOWHILE_WARNING()                                \
    do {                                                                \
        if (LOGGING_UNLIKELY(! (condition)))                          \
            LOGGING_FATAL_STR ((logger),                              \
                LOGGING_TEXT ("failed condition: ")                   \
                LOGGING_TEXT (LOGGING_ASSERT_STRINGIFY (condition))); \
    } while (0)                                                         \
    LOGGING_RESTORE_DOWHILE_WARNING()


#endif /* LOGGING_LOGGING_MACROS_HEADER_ */
