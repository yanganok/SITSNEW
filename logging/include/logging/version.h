#if ! defined (LOGGING_VERSION_H)
#define LOGGING_VERSION_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#define LOGGING_MAKE_VERSION(major, minor, point) \
    (major * 1000 * 1000u + minor * 1000u + point)

#define LOGGING_MAKE_VERSION_STR(major, minor, point) \
    #major "." #minor "." #point

//! This is logging version number as unsigned integer.  This must
//! be kept on a single line. It is used by Autotool and CMake build
//! systems to parse version number.
#define LOGGING_VERSION LOGGING_MAKE_VERSION(2, 0, 5)

//! This is logging version number as a string.
#define LOGGING_VERSION_STR LOGGING_MAKE_VERSION_STR(2, 0, 5)


namespace logging
{

	extern LOGGING_EXPORT unsigned const version;
	extern LOGGING_EXPORT char const versionStr[];

}

#endif
