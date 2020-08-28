#ifndef LOGGING_CONFIG_HXX
#define LOGGING_CONFIG_HXX

#if defined (_WIN32)
#  include <logging/config/win32.h>
#elif (defined(__MWERKS__) && defined(__MACOS__))
#  include <logging/config/macosx.h>
#else
#  include <logging/config/defines.hxx>
#endif

# if ! defined (LOGGING_WORKING_LOCALE) \
  && ! defined (LOGGING_WORKING_C_LOCALE) \
  && ! defined (LOGGING_WITH_ICONV)
# define LOGGING_POOR_MANS_CHCONV
#endif

#ifndef LOGGING_DECLSPEC_EXPORT
#define LOGGING_DECLSPEC_EXPORT /* empty */
#endif

#ifndef LOGGING_DECLSPEC_IMPORT
#define LOGGING_DECLSPEC_IMPORT /* empty */
#endif

#ifndef LOGGING_DECLSPEC_PRIVATE
#define LOGGING_DECLSPEC_PRIVATE /* empty */
#endif

#define LOGGING_PRIVATE LOGGING_DECLSPEC_PRIVATE

#if !defined(_WIN32)
#  define LOGGING_USE_BSD_SOCKETS
#  if !defined(LOGGING_SINGLE_THREADED)
#    define LOGGING_USE_PTHREADS
#  endif
#  if defined (INSIDE_LOGGING)
#    define LOGGING_EXPORT LOGGING_DECLSPEC_EXPORT
#  else
#    define LOGGING_EXPORT LOGGING_DECLSPEC_IMPORT
#  endif // defined (INSIDE_LOGGING)

#endif // !_WIN32

#if defined (LOGGING_INLINES_ARE_EXPORTED) \
    && defined (LOGGING_BUILD_DLL)
#  define LOGGING_INLINE_EXPORT inline
#else
#  define LOGGING_INLINE_EXPORT
#endif

#if defined (UNICODE)
#  if defined (_MSC_VER) && _MSC_VER >= 1400
#    define LOGGING_FSTREAM_ACCEPTS_WCHAR_T
#  endif
#  if defined (_MSC_VER) && _MSC_VER >= 1600
#    define LOGGING_HAVE_CODECVT_UTF8_FACET
#    define LOGGING_HAVE_CODECVT_UTF16_FACET
#  endif
#endif

// C++11 stuff

#if ! defined (__has_feature)
//! __has_feature(X) is Clangs way for testing features.
//! Define it to 0 if it does not exist.
#  define __has_feature(X) 0
#endif

#if __has_feature (cxx_noexcept)                       \
    || (defined (__GNUC__)                             \
        && (__GNUC__ > 4                               \
            || __GNUC__ == 4 && __GNUC_MINOR__ >= 6))  \
    || (defined (_MSC_VER) && _MSC_VER >= 1900)
#  define LOGGING_NOEXCEPT noexcept
#  define LOGGING_NOEXCEPT_FALSE noexcept(false)
#else
#  define LOGGING_NOEXCEPT /* empty */
#  define LOGGING_NOEXCEPT_FALSE /* empty */
#endif

#if ! defined (UNICODE) && defined (__GNUC__) && __GNUC__ >= 3
#  define LOGGING_FORMAT_ATTRIBUTE(archetype, format_index, first_arg_index) \
    __attribute__ ((format (archetype, format_index, first_arg_index)))
#else
#  define LOGGING_FORMAT_ATTRIBUTE(archetype, fmt_index, first_arg_index) \
    /* empty */
#endif

#if defined (__GNUC__) \
    && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)) \
    && ! defined (__INTEL_COMPILER) \
    && ! defined (__CUDACC__)
#  define LOGGING_CALLER_FILE() __builtin_FILE ()
#  define LOGGING_CALLER_LINE() __builtin_LINE ()
#  define LOGGING_CALLER_FUNCTION() __builtin_FUNCTION ()
#else
#  define LOGGING_CALLER_FILE() (nullptr)
#  define LOGGING_CALLER_LINE() (-1)
#  define LOGGING_CALLER_FUNCTION() (nullptr)
#endif

#if defined (__GNUC__) && __GNUC__ >= 3
#  define LOGGING_ATTRIBUTE_NORETURN __attribute__ ((__noreturn__))
#  define LOGGING_ATTRIBUTE_PURE __attribute__ ((__pure__))
#  define LOGGING_ATTRIBUTE_DEPRECATED __attribute__ ((__deprecated__))
#  define LOGGING_BUILTIN_EXPECT(exp, c) __builtin_expect ((exp), (c))
#else
#  if ! defined (LOGGING_ATTRIBUTE_NORETURN)
#    define LOGGING_ATTRIBUTE_NORETURN /* empty */
#  endif
#  define LOGGING_ATTRIBUTE_PURE /* empty */
#  define LOGGING_ATTRIBUTE_DEPRECATED /* empty */
#  define LOGGING_BUILTIN_EXPECT(exp, c) (exp)
#endif

#define LOGGING_LIKELY(cond) LOGGING_BUILTIN_EXPECT(!! (cond), 1)
#define LOGGING_UNLIKELY(cond) LOGGING_BUILTIN_EXPECT(!! (cond), 0)

#if defined (_MSC_VER)                                             \
    || (defined (__BORLANDC__) && __BORLANDC__ >= 0x0650)          \
    || (defined (__COMO__) && __COMO_VERSION__ >= 400) /* ??? */   \
    || (defined (__DMC__) && __DMC__ >= 0x700) /* ??? */           \
    || (defined (__clang__) && __clang_major__ >= 3)               \
    || (defined (__GNUC__) && (__GNUC__ >= 4                       \
            || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)))
#  define LOGGING_HAVE_PRAGMA_ONCE
#  pragma once
#endif

#if defined (LOGGING_HAVE_FUNC_ATTRIBUTE_CONSTRUCTOR_PRIORITY)
#  define LOGGING_CONSTRUCTOR_FUNC(prio) \
    __attribute__ ((__constructor__ ((prio))))
#elif defined (LOGGING_HAVE_FUNC_ATTRIBUTE_CONSTRUCTOR)
#  define LOGGING_CONSTRUCTOR_FUNC(prio) \
    __attribute__ ((__constructor__))
#else
#  define LOGGING_CONSTRUCTOR_FUNC(prio) /* empty */
#endif

#if defined (LOGGING_HAVE_VAR_ATTRIBUTE_INIT_PRIORITY)
#  define LOGGING_INIT_PRIORITY(prio) \
    __attribute__ ((__init_priority__ ((prio))))
#else
#  define LOGGING_INIT_PRIORITY(prio) /* empty */
#endif

#define LOGGING_INIT_PRIORITY_BASE (65535 / 2)

#include <logging/helpers/thread-config.h>

#if defined (LOGGING_SINGLE_THREADED)
#define LOGGING_THREADED(x)
#else
#define LOGGING_THREADED(x) x
#endif

#if defined(__cplusplus)
#include <cstddef>

namespace logging
{

	//! Per thread cleanup function. Users should call this function before
	//! a thread ends its execution. It frees resources allocated in thread local
	//! storage. It is important only for multi-threaded static library builds
	//! of logging and user threads. In all other cases the clean up is provided
	//! automatically by other means.
	LOGGING_EXPORT void threadCleanup();

	//! Initializes logging.
	//!
	//! \note using `logging::Initializer` is preferred
	LOGGING_EXPORT void initialize();

	//! Deinitializes logging.
	//!
	//! \note using `logging::Initializer` is preferred
	LOGGING_EXPORT void deinitialize();

	//! Set thread pool size.
	LOGGING_EXPORT void setThreadPoolSize(std::size_t pool_size);

} // namespace logging

#endif

#endif // LOGGING_CONFIG_HXX
