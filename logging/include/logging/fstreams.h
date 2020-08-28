#ifndef LOGGING_FSTREAMS_HEADER_
#define LOGGING_FSTREAMS_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/tchar.h>
#include <iosfwd>


namespace logging
{


	typedef std::basic_ofstream<tchar> tofstream;
	typedef std::basic_ifstream<tchar> tifstream;

	//! \def LOGGING_FSTREAM_PREFERED_FILE_NAME(X)
	//! \brief Expands into expression that picks the right type for
	//! std::fstream file name parameter.
#if defined (LOGGING_FSTREAM_ACCEPTS_WCHAR_T) && defined (UNICODE)
#  define LOGGING_FSTREAM_PREFERED_FILE_NAME(X) (X)
#else
#  define LOGGING_FSTREAM_PREFERED_FILE_NAME(X) (LOGGING_TSTRING_TO_STRING(X))
#endif


}

#endif // LOGGING_FSTREAMS_HEADER_
