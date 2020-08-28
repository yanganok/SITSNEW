#ifndef LOGGING_CONFIG_MACOSX_HEADER_
#define LOGGING_CONFIG_MACOSX_HEADER_

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#if (defined(__APPLE__) || (defined(__MWERKS__) && defined(__MACOS__)))

#define LOGGING_HAVE_GETTIMEOFDAY 1
#define socklen_t int

#endif // MACOSX
#endif // LOGGING_CONFIG_MACOSX_HEADER_
