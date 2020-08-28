#ifndef LOGGING_CLOGGERHEADER_
#define LOGGING_CLOGGERHEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif


#ifdef __cplusplus
extern "C"
{
#endif

	// TODO UNICDE capable

	typedef void * LOGGING_logger_t;
	typedef LOGGING_logger_t logger_t;

	typedef int LOGGING_loglevel_t;
	typedef LOGGING_loglevel_t loglevel_t;

#define L4CP_OFF_LOG_LEVEL 60000
#define L4CP_FATAL_LOG_LEVEL 50000
#define L4CP_ERROR_LOG_LEVEL 40000
#define L4CP_WARN_LOG_LEVEL 30000
#define L4CP_INFO_LOG_LEVEL 20000
#define L4CP_DEBUG_LOG_LEVEL 10000
#define L4CP_TRACE_LOG_LEVEL 0
#define L4CP_ALL_LOG_LEVEL TRACE_LOG_LEVEL
#define L4CP_NOT_SET_LOG_LEVEL -1

#ifdef UNICODE
	typedef wchar_t LOGGING_char_t;
#else
	typedef char LOGGING_char_t;
#endif // UNICODE

#if ! defined (LOGGING_TEXT)
#ifdef UNICODE
#  define LOGGING_TEXT2(STRING) L##STRING
#else
#  define LOGGING_TEXT2(STRING) STRING
#endif // UNICODE
#define LOGGING_TEXT(STRING) LOGGING_TEXT2(STRING)
#endif // LOGGING_TEXT

	LOGGING_EXPORT void * LOGGING_initialize(void);
	LOGGING_EXPORT int LOGGING_deinitialize(void * initializer);

	LOGGING_EXPORT int LOGGING_file_configure(const LOGGING_char_t *pathname);
	LOGGING_EXPORT int LOGGING_file_reconfigure(const LOGGING_char_t *pathname);
	LOGGING_EXPORT int LOGGING_str_configure(const LOGGING_char_t *config);
	LOGGING_EXPORT int LOGGING_str_reconfigure(const LOGGING_char_t *config);
	LOGGING_EXPORT int LOGGING_basic_configure(void);
	LOGGING_EXPORT int LOGGING_basic_reconfigure(int logToStdErr);
	LOGGING_EXPORT void LOGGING_shutdown(void);

	LOGGING_EXPORT int LOGGING_logger_exists(const LOGGING_char_t *name);
	LOGGING_EXPORT int LOGGING_logger_is_enabled_for(
		const LOGGING_char_t *name, LOGGING_loglevel_t ll);

	LOGGING_EXPORT int LOGGING_logger_log(const LOGGING_char_t *name,
		LOGGING_loglevel_t ll, const LOGGING_char_t *msgfmt, ...)
		LOGGING_FORMAT_ATTRIBUTE(__printf__, 3, 4);

	LOGGING_EXPORT int LOGGING_logger_log_str(const LOGGING_char_t *name,
		LOGGING_loglevel_t ll, const LOGGING_char_t *msg);

	LOGGING_EXPORT int LOGGING_logger_force_log(const LOGGING_char_t *name,
		LOGGING_loglevel_t ll, const LOGGING_char_t *msgfmt, ...)
		LOGGING_FORMAT_ATTRIBUTE(__printf__, 3, 4);

	LOGGING_EXPORT int LOGGING_logger_force_log_str(const LOGGING_char_t *name,
		LOGGING_loglevel_t ll, const LOGGING_char_t *msg);

	//! CallbackAppender callback type.
	typedef void(*LOGGING_log_event_callback_t)(void * cookie,
		LOGGING_char_t const * message, LOGGING_char_t const * loggerName,
		LOGGING_loglevel_t ll, LOGGING_char_t const * thread,
		LOGGING_char_t const * thread2,
		unsigned long long timestamp_secs, unsigned long timestamp_usecs,
		LOGGING_char_t const * file, LOGGING_char_t const * function, int line);

	LOGGING_EXPORT int LOGGING_add_callback_appender(
		const LOGGING_char_t * logger, LOGGING_log_event_callback_t callback,
		void * cookie);

	// Custom LogLevel
	LOGGING_EXPORT int LOGGING_add_log_level(unsigned int ll,
		const LOGGING_char_t *ll_name);
	LOGGING_EXPORT int LOGGING_remove_log_level(unsigned int ll,
		const LOGGING_char_t *ll_name);

#ifdef __cplusplus
}
#endif

#endif /*?LOGGING_CLOGGERHEADER_*/
