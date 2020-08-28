#ifndef LOGGING_STREAMS_HEADER_
#define LOGGING_STREAMS_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/tchar.h>

#include <iosfwd>


namespace logging
{
	typedef std::basic_ostream<tchar> tostream;
	typedef std::basic_istream<tchar> tistream;
	typedef std::basic_ostringstream<tchar> tostringstream;
	typedef std::basic_istringstream<tchar> tistringstream;
	extern LOGGING_EXPORT tostream & tcout;
	extern LOGGING_EXPORT tostream & tcerr;
}

#if defined (UNICODE) && defined (LOGGING_ENABLE_GLOBAL_C_STRING_STREAM_INSERTER)

LOGGING_EXPORT logging::tostream& operator <<(logging::tostream&, const char* psz);

#endif

#endif // LOGGING_STREAMS_HEADER_

