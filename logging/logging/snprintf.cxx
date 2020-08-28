#include <logging/helpers/snprintf.h>
#include <logging/helpers/loglog.h>
#include <logging/internal/internal.h>
#include <cstdarg>
#include <cstdio>
#if defined (UNICODE)
#include <cwchar>
#endif
#if defined (LOGGING_HAVE_STDARG_H)
#  include <stdarg.h>
#endif
#if defined (LOGGING_HAVE_WCHAR_H)
#  include <wchar.h>
#endif
#if defined (LOGGING_HAVE_STDIO_H)
#  include <stdio.h>
#endif

#if defined (LOGGING_WITH_UNIT_TESTS)
#include <logging/catch.hpp>
#endif


namespace logging {
	namespace helpers {


		std::size_t const START_BUF_SIZE = 512;

#if defined (_WIN32)
		char const NULL_FILE[] = "NUL";
#else
		char const NULL_FILE[] = "/dev/null";
#endif


		namespace
		{


#if defined (LOGGING_USE_POOR_MANS_SNPRINTF)

			static inline int vftprintf(std::FILE * file, tchar const * fmt,
				std::va_list args) LOGGING_FORMAT_ATTRIBUTE(__printf__, 2, 0);

			static inline
				int
				vftprintf(std::FILE * file, tchar const * fmt, std::va_list args)
			{
#if defined (UNICODE)
#  if defined (LOGGING_HAVE_VFWPRINTF_S)
				return vfwprintf_s(file, fmt, args);
#  else
				return std::vfwprintf(file, fmt, args);
#  endif
#else
#  if defined (LOGGING_HAVE_VFPRINTF_S)
				return vfprintf_s(file, fmt, args);
#  else
				return std::vfprintf(file, fmt, args);
#  endif
#endif
			}


			static inline int vstprintf(tchar * dest, std::size_t dest_size,
				tchar const * fmt, std::va_list args)
				LOGGING_FORMAT_ATTRIBUTE(__printf__, 3, 0);

			static inline
				int
				vstprintf(tchar * dest, std::size_t dest_size, tchar const * fmt,
					std::va_list args)
			{
				int ret;
#if defined (UNICODE)
#  if defined (LOGGING_HAVE_VSWPRINTF_S)
				ret = vswprintf_s(dest, dest_size, fmt, args);
#  else
				ret = std::vswprintf(dest, dest_size, fmt, args);
#  endif
#else
#  if defined (LOGGING_HAVE_VSPRINTF_S)
				ret = vsprintf_s(dest, dest_size, fmt, args);
#  else
				ret = std::vsprintf(dest, fmt, args);
#  endif
#endif

				if (ret >= 0)
					assert(static_cast<std::size_t>(ret) <= dest_size);

				return ret;
			}

#else /* ?defined (LOGGING_USE_POOR_MANS_SNPRINTF) */

			static inline int vsntprintf(tchar * dest, std::size_t dest_size,
				tchar const * fmt, std::va_list args)
				LOGGING_FORMAT_ATTRIBUTE(__printf__, 3, 0);

			static inline
				int
				vsntprintf(tchar * dest, std::size_t dest_size, tchar const * fmt,
					std::va_list args)
			{
				int ret;

#if defined (UNICODE)
#  if defined (LOGGING_HAVE__VSWPRINTF_P)
				ret = _vswprintf_p(dest, dest_size, fmt, args);
#  elif defined (LOGGING_HAVE__VSNWPRINTF_S) && defined (_TRUNCATE)
				ret = _vsnwprintf_s(dest, dest_size, _TRUNCATE, fmt, args);
#  elif defined (LOGGING_HAVE_VSNWPRINTF)
				ret = vsnwprintf(dest, dest_size, fmt, args);
#  elif defined (LOGGING_HAVE__VSNWPRINTF)
				ret = _vsnwprintf(dest, dest_size, fmt, args);
#  else
				using namespace std;
				ret = vswprintf(dest, dest_size, fmt, args);
#  endif
#else
#  if defined (LOGGING_HAVE__VSPRINTF_P)
				ret = _vsprintf_p(dest, dest_size, fmt, args);
#  elif defined (LOGGING_HAVE_VSNPRINTF_S) && defined (_TRUNCATE)
				ret = vsnprintf_s(dest, dest_size, _TRUNCATE, fmt, args);
#  elif defined (LOGGING_HAVE__VSNPRINTF_S) && defined (_TRUNCATE)
				ret = _vsnprintf_s(dest, dest_size, _TRUNCATE, fmt, args);
#  elif defined (LOGGING_HAVE_VSNPRINTF)
				ret = vsnprintf(dest, dest_size, fmt, args);
#  elif defined (LOGGING_HAVE__VSNPRINTF)
				ret = _vsnprintf(dest, dest_size, fmt, args);
#  else
#    error "None of vsnprintf_s, _vsnprintf_s, vsnprintf or _vsnprintf is available."
#  endif
#endif

				return ret;
			}
#endif


		}


		snprintf_buf::snprintf_buf()
			: buf(START_BUF_SIZE)
		{ }


		tchar const *
			snprintf_buf::print(tchar const * fmt, ...)
		{
			assert(fmt);

			tchar const * str = nullptr;
			int ret = 0;
			std::va_list args;

			do
			{
				va_start(args, fmt);
				ret = print_va_list(str, fmt, args);
				va_end(args);
			} while (ret == -1);

			return str;
		}


		int
			snprintf_buf::print_va_list(tchar const * & str, tchar const * fmt,
				std::va_list args)
		{
			int printed;
			std::size_t const fmt_len = std::char_traits<tchar>::length(fmt);
			std::size_t buf_size = buf.size();
			std::size_t const output_estimate = fmt_len + fmt_len / 2 + 1;
			if (output_estimate > buf_size)
				buf.resize(buf_size = output_estimate);

#if defined (LOGGING_USE_POOR_MANS_SNPRINTF)
			std::FILE * & fnull = internal::get_ptd()->fnull;
			if (!fnull)
			{
				fnull = std::fopen(NULL_FILE, "wb");
				if (!fnull)
					LogLog::getLogLog()->error(
						LOGGING_TEXT("Could not open NULL_FILE."), true);
			}

			std::va_list args_copy;
			va_copy(args_copy, args);
			printed = vftprintf(fnull, fmt, args_copy);
			va_end(args_copy);
			if (printed == -1)
				LogLog::getLogLog()->error(
					LOGGING_TEXT("Error printing into NULL_FILE."), true);

			buf.resize(printed + 1);
			int sprinted = vstprintf(&buf[0], buf.size(), fmt, args);
			if (sprinted == -1 || sprinted >= buf.size())
				LogLog::getLogLog()->error(
					LOGGING_TEXT("Error printing into string."), true);

			assert(printed == sprinted);

			buf[sprinted] = 0;

#else
			printed = vsntprintf(&buf[0], buf_size - 1, fmt, args);
			if (printed == -1)
			{
#if defined (EILSEQ)
				if (errno == EILSEQ)
				{
					LogLog::getLogLog()->error(
						LOGGING_TEXT("Character conversion error when printing"));
					// Return zero to terminate the outer loop in
					// snprintf_buf::print().
					return 0;
				}
#endif

				buf_size *= 2;
				buf.resize(buf_size);
			}
			else if (printed >= static_cast<int>(buf_size - 1))
			{
				buf_size = printed + 2;
				buf.resize(buf_size);
				printed = -1;
			}
			else
				buf[printed] = 0;

#endif

			str = &buf[0];
			return printed;
		}


#if defined (LOGGING_WITH_UNIT_TESTS)
		CATCH_TEST_CASE("snprintf_buf", "[snprintf_buf]")
		{
			snprintf_buf buf;

			CATCH_SECTION("ints")
			{
				tchar const * const result
					= buf.print(LOGGING_TEXT("%d %d %d"), 1, 2, 3);
				std::size_t const len = std::char_traits<tchar>::length(result);
				CATCH_REQUIRE(result);
				CATCH_REQUIRE(
					std::char_traits<tchar>::compare(result, LOGGING_TEXT("1 2 3"),
						len)
					== 0);
			}
		}

#endif


	}
} // namespace logging { namespace helpers
