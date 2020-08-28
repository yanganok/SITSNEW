#ifndef LOGGING_TCHAR_HEADER_
#define LOGGING_TCHAR_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#if defined (_WIN32)
#include <cstddef>
#endif


#ifdef UNICODE
#  define LOGGING_TEXT2(STRING) L##STRING
#else
#  define LOGGING_TEXT2(STRING) STRING
#endif // UNICODE
#define LOGGING_TEXT(STRING) LOGGING_TEXT2(STRING)


namespace logging
{

#if defined (UNICODE)
	typedef wchar_t tchar;

#else
	typedef char tchar;

#endif

} // namespace logging


#endif // LOGGING_TCHAR_HEADER_
