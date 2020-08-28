#ifndef LOGGING_HELPERS_THREAD_CONFIG_HEADER_
#define LOGGING_HELPERS_THREAD_CONFIG_HEADER_

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#if defined (LOGGING_USE_PTHREADS)
#   if defined (__APPLE__)
#     define LOGGING_USE_NAMED_POSIX_SEMAPHORE
#   endif

#elif defined(LOGGING_USE_WIN32_THREADS)
#   define LOGGING_USE_SRW_LOCK
//#   define LOGGING_POOR_MANS_SHAREDMUTEX
#   undef LOGGING_HAVE_TLS_SUPPORT
#   undef LOGGING_THREAD_LOCAL_VAR
#   if defined (_MSC_VER)
// The __declspec(thread) functionality is not compatible with LoadLibrary().
// For more information why see and "Windows and TLS" note in README.
// <http://msdn.microsoft.com/en-us/library/2s9wt68x(v=vs.100).aspx>.
#     define LOGGING_HAVE_TLS_SUPPORT 1
#     define LOGGING_THREAD_LOCAL_VAR __declspec(thread)
#   endif

#elif defined(LOGGING_SINGLE_THREADED)
#   undef LOGGING_HAVE_TLS_SUPPORT
#   undef LOGGING_THREAD_LOCAL_VAR

#else
#   error "You Must define a Threading model"

#endif


#endif // LOGGING_HELPERS_THREAD_CONFIG_HEADER_
