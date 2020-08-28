#if ! defined (LOGGING_CONFIG_CYGWIN_WIN32_H)
#define LOGGING_CONFIG_CYGWIN_WIN32_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#if defined (__CYGWIN__)

#if ! defined (INSIDE_LOGGING)
#  error "This header must not be be used outside logging' implementation files."
#endif


namespace logging {
	namespace cygwin {

		unsigned long get_current_win32_thread_id();
		void output_debug_stringW(wchar_t const *);

	}
} // namespace logging { namespace cygwin {


#endif // defined (__CYGWIN__)
#endif // LOGGING_CONFIG_CYGWIN_WIN32_H
