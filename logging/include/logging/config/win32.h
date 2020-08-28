#ifndef LOGGING_CONFIG_WIN32_HEADER_
#define LOGGING_CONFIG_WIN32_HEADER_

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#if defined (__MINGW32__)  || defined (__MINGW64__)
#  include <_mingw.h>
#endif

#ifdef _WIN32

#if (defined (_MSC_VER) && _MSC_VER > 1400) \
    || (defined (__MINGW64_VERSION_MAJOR) && __MINGW64_VERSION_MAJOR >= 3)
#  define LOGGING_HAVE_INTRIN_H
#endif

// Time related functions and headers.
#define LOGGING_HAVE_TIME_H
#define LOGGING_HAVE_SYS_TIMEB_H
#define LOGGING_HAVE_FTIME
#if defined (_MSC_VER) || defined (__BORLANDC__)
#define LOGGING_HAVE_GMTIME_S
#endif

// Use Winsock on Windows.
#define LOGGING_USE_WINSOCK

// Enable Win32DebugAppender
#define LOGGING_HAVE_OUTPUTDEBUGSTRING

// Enable Win32ConsoleAppender.
#define LOGGING_HAVE_WIN32_CONSOLE

#define LOGGING_HAVE_SYS_TYPES_H
#define LOGGING_HAVE_SYS_LOCKING_H
#define LOGGING_HAVE_FCNTL_H
#define LOGGING_HAVE_IO_H
#define LOGGING_HAVE_STDIO_H
#define LOGGING_HAVE_WCHAR_H
#define LOGGING_HAVE_STDARG_H
#define LOGGING_HAVE_STDLIB_H
#define LOGGING_HAVE_ERRNO_H
#define LOGGING_HAVE_SYS_STAT_H
#define LOGGING_HAVE_TIME_H
#define LOGGING_HAVE_STDLIB_H
#define LOGGING_HAVE_DIRECT_H

// MSVC has both and so does MinGW.
#define LOGGING_HAVE_VSNPRINTF
#define LOGGING_HAVE__VSNPRINTF
#define LOGGING_HAVE__VSNWPRINTF

// Limit the use of foo_s() functions to builds using Visual Studio
// 2005 and its run time library. In MinGW land, limit the foo_s()
// functions to MinGw-w64 toolchain and __MSVCRT_VERSION__ >= 0x0900.
#if (defined (_MSC_VER) && _MSC_VER >= 1400)                         \
    || (defined (__MSVCRT_VERSION__) && __MSVCRT_VERSION__ >= 0x0900 \
        && defined (__MINGW64_VERSION_MAJOR) && __MINGW64_VERSION_MAJOR >= 2)
// MS secure versions of vprintf().
#  define LOGGING_HAVE_VSPRINTF_S
#  define LOGGING_HAVE_VSWPRINTF_S

// MS secure versions of vfprintf().
#  define LOGGING_HAVE_VFPRINTF_S
#  define LOGGING_HAVE_VFWPRINTF_S

// MS secure versions of vsnprintf().
#  define LOGGING_HAVE_VSNPRINTF_S
#  define LOGGING_HAVE__VSNPRINTF_S
#  define LOGGING_HAVE__VSNWPRINTF_S

// MS secure version of _tsopen().
#  define LOGGING_HAVE__TSOPEN_S
#endif

#if defined (_MSC_VER) && _MSC_VER >= 1400
// MS printf-like functions supporting positional parameters.
#  define LOGGING_HAVE__VSPRINTF_P
#  define LOGGING_HAVE__VSWPRINTF_P
#endif

#if defined (_MSC_VER)
#  define LOGGING_HAVE_LOCALTIME_S
#endif

#define LOGGING_HAVE__TSOPEN

#define LOGGING_DLLMAIN_HINSTANCE HINSTANCE
#define LOGGING_HAVE_NT_EVENT_LOG

// LOGGING_EXPORTS is used by the CMake build system.  DLL_EXPORT is
// used by the autotools build system.
#if (defined (LOGGING_EXPORTS) \
    || (defined (DLL_EXPORT) && defined (INSIDE_LOGGING)))     \
    && ! defined (LOGGING_STATIC)
#  undef LOGGING_BUILD_DLL
#  define LOGGING_BUILD_DLL
#endif

#if ! defined (LOGGING_BUILD_DLL)
#  undef LOGGING_STATIC
#  define LOGGING_STATIC
#endif

#if defined (LOGGING_STATIC) && defined (LOGGING_BUILD_DLL)
#  error LOGGING_STATIC and LOGGING_BUILD_DLL cannot be defined both.
#endif

#if defined (LOGGING_BUILD_DLL)
#  if defined (INSIDE_LOGGING)
#    define LOGGING_EXPORT __declspec(dllexport)
#  else
#    define LOGGING_EXPORT __declspec(dllimport)
#  endif
#else
#  define LOGGING_EXPORT
#endif

#ifndef LOGGING_SINGLE_THREADED
#  define LOGGING_USE_WIN32_THREADS
#endif

#if defined(_MSC_VER)
  // Warning about: identifier was truncated to '255' characters in the debug information
#  pragma warning( disable : 4786 )
  // Warning about: <type1> needs to have dll-interface to be used by clients of class <type2>
#  pragma warning( disable : 4251 )

#  define LOGGING_INLINES_ARE_EXPORTED

#  if _MSC_VER >= 1400
#    define LOGGING_WORKING_LOCALE
#    define LOGGING_HAVE_FUNCTION_MACRO
#    define LOGGING_HAVE_FUNCSIG_MACRO
#    define LOGGING_ATTRIBUTE_NORETURN __declspec(noreturn)
#  endif
#endif

#if defined (__GNUC__)
#  undef LOGGING_INLINES_ARE_EXPORTED
#  if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)
#    define LOGGING_HAVE_PRETTY_FUNCTION_MACRO
#    define LOGGING_HAVE_FUNC_SYMBOL
#  endif
// This has worked for some versions of MinGW with GCC 4.7+ but it
// appears to be broken again in 4.8.x. Thus, we disable this for GCC
// completely forever.
//
//#  define LOGGING_INLINES_ARE_EXPORTED
#  define LOGGING_HAVE_FUNCTION_MACRO
#  if defined (__MINGW32__)
#    define LOGGING_WORKING_C_LOCALE
#  endif
#endif

#if defined (__BORLANDC__) && __BORLANDC__ >= 0x0650
#  define LOGGING_HAVE_FUNCTION_MACRO
#endif // __BORLANDC__

#if ! defined (LOGGING_DISABLE_DLL_RUNTIME_WARNING)
#  if defined (LOGGING_STATIC) && defined (_MSC_VER) && ! defined (_DLL)
#    pragma message("You are not using DLL C run time library. " \
    "You must call logging::initialize() once before " \
    "you use any other logging API.")
#  endif
#endif

#endif // _WIN32
#endif // LOGGING_CONFIG_WIN32_HEADER_
