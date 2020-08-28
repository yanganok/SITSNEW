#if defined (__CYGWIN__)

// Work around missing _X86_ symbol with Clang on Cygwin.
#if ! defined (_X86_) && defined (__i386__)
#  define _X86_ 1
#endif

#include <logging/internal/cygwin-win32.h>

// This is intentionally included directly instead of through
// windowsh-inc.h.
#include <winsock2.h>


namespace logging {
	namespace cygwin {

		unsigned long
			get_current_win32_thread_id()
		{
			return GetCurrentThreadId();
		}


		void
			output_debug_stringW(wchar_t const * str)
		{
			OutputDebugStringW(str);
		}

	}
} // namespace logging { namespace cygwin {

#endif // defined (__CYGWIN__)
