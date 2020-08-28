#ifndef LOGGING_HELPERS_SNPRINTF_H
#define LOGGING_HELPERS_SNPRINTF_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/tchar.h>
#include <cstdarg>
#include <vector>


namespace logging {
	namespace helpers {


		class LOGGING_EXPORT snprintf_buf
		{
		public:
			snprintf_buf();

			tchar const * print(tchar const * fmt, ...)
				LOGGING_FORMAT_ATTRIBUTE(__printf__, 2, 3);

			int print_va_list(tchar const * & str, tchar const * fmt, std::va_list)
				LOGGING_FORMAT_ATTRIBUTE(__printf__, 3, 0);

		private:
			std::vector<tchar> buf;
		};


	}
} // namespace logging { namespace helpers



#endif // LOGGING_HELPERS_SNPRINTF_H
