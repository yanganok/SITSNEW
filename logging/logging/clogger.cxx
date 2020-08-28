#include <logging/logger.h>
#include <logging/clogger.h>
#include <logging/appender.h>
#include <logging/hierarchylocker.h>
#include <logging/hierarchy.h>
#include <logging/helpers/loglog.h>
#include <logging/spi/loggerimpl.h>
#include <logging/configurator.h>
#include <logging/streams.h>
#include <logging/helpers/snprintf.h>
#include <logging/initializer.h>
#include <logging/callbackappender.h>
#include <logging/internal/internal.h>
#include <logging/internal/customloglevelmanager.h>

#include <cerrno>
#include <cstdio>
#include <cstdarg>
#include <cstring>

#include <sstream>
#include <map>

using namespace logging;
using namespace logging::helpers;


LOGGING_EXPORT void *
LOGGING_initialize(void)
{
	try
	{
		return new Initializer();
	}
	catch (std::exception const &)
	{
		return 0;
	}
}


LOGGING_EXPORT int
LOGGING_deinitialize(void * initializer_)
{
	if (!initializer_)
		return EINVAL;

	try
	{
		Initializer * initializer = static_cast<Initializer *>(initializer_);
		delete initializer;
	}
	catch (std::exception const &)
	{
		return -1;
	}

	return 0;
}


LOGGING_EXPORT int
LOGGING_file_configure(const LOGGING_char_t *pathname)
{
	if (!pathname)
		return EINVAL;

	try
	{
		PropertyConfigurator::doConfigure(pathname);
	}
	catch (std::exception const &)
	{
		return -1;
	}

	return 0;
}

LOGGING_EXPORT int
LOGGING_file_reconfigure(const LOGGING_char_t *pathname)
{
	if (!pathname)
		return EINVAL;

	try
	{
		// lock the DefaultHierarchy
		HierarchyLocker theLock(Logger::getDefaultHierarchy());

		// reconfigure the DefaultHierarchy
		theLock.resetConfiguration();
		PropertyConfigurator::doConfigure(pathname);
	}
	catch (std::exception const &)
	{
		return -1;
	}

	return 0;
}

LOGGING_EXPORT int
LOGGING_str_configure(const LOGGING_char_t *config)
{
	if (!config)
		return EINVAL;

	try
	{
		tstring s(config);
		tistringstream iss(s);
		PropertyConfigurator pc(iss);
		pc.configure();
	}
	catch (std::exception const &)
	{
		return -1;
	}

	return 0;
}

LOGGING_EXPORT int
LOGGING_str_reconfigure(const LOGGING_char_t *config)
{
	if (!config)
		return EINVAL;

	try
	{
		tstring s(config);
		tistringstream iss(s);
		HierarchyLocker theLock(Logger::getDefaultHierarchy());

		// reconfigure the DefaultHierarchy
		theLock.resetConfiguration();
		PropertyConfigurator pc(iss);
		pc.configure();
	}
	catch (std::exception const &)
	{
		return -1;
	}

	return 0;
}

LOGGING_EXPORT int
LOGGING_basic_configure(void)
{
	try
	{
		BasicConfigurator::doConfigure();
	}
	catch (std::exception const &)
	{
		return -1;
	}

	return 0;
}

LOGGING_EXPORT int
LOGGING_basic_reconfigure(int logToStdErr)
{
	try
	{
		HierarchyLocker theLock(Logger::getDefaultHierarchy());

		// reconfigure the DefaultHierarchy
		theLock.resetConfiguration();
		BasicConfigurator::doConfigure(Logger::getDefaultHierarchy(), logToStdErr);
	}
	catch (std::exception const &)
	{
		return -1;
	}

	return 0;
}

LOGGING_EXPORT void
LOGGING_shutdown(void)
{
	Logger::shutdown();
}


LOGGING_EXPORT int
LOGGING_add_callback_appender(const LOGGING_char_t * logger_name,
	LOGGING_log_event_callback_t callback, void * cookie)
{
	try
	{
		Logger logger = logger_name
			? Logger::getInstance(logger_name)
			: Logger::getRoot();
		SharedAppenderPtr appender(new CallbackAppender(callback, cookie));
		logger.addAppender(appender);
	}
	catch (std::exception const &)
	{
		return -1;
	}

	return 0;
}


LOGGING_EXPORT int
LOGGING_logger_exists(const LOGGING_char_t *name)
{
	int retval = false;

	try
	{
		retval = Logger::exists(name);
	}
	catch (std::exception const &)
	{
		// Fall through.
	}

	return retval;
}

LOGGING_EXPORT int
LOGGING_logger_is_enabled_for(const LOGGING_char_t *name, loglevel_t ll)
{
	int retval = false;

	try
	{
		Logger logger = name ? Logger::getInstance(name) : Logger::getRoot();
		retval = logger.isEnabledFor(ll);
	}
	catch (std::exception const &)
	{
		// Fall through.
	}

	return retval;
}

LOGGING_EXPORT int
LOGGING_logger_log(const LOGGING_char_t *name, loglevel_t ll,
	const LOGGING_char_t *msgfmt, ...)
{
	int retval = -1;

	try
	{
		Logger logger = name ? Logger::getInstance(name) : Logger::getRoot();

		if (logger.isEnabledFor(ll))
		{
			const tchar * msg = nullptr;
			snprintf_buf buf;
			std::va_list ap;

			do
			{
				va_start(ap, msgfmt);
				retval = buf.print_va_list(msg, msgfmt, ap);
				va_end(ap);
			} while (retval == -1);

			logger.forcedLog(ll, msg, 0, -1);
		}

		retval = 0;
	}
	catch (std::exception const &)
	{
		// Fall through.
	}

	return retval;
}


LOGGING_EXPORT int
LOGGING_logger_log_str(const LOGGING_char_t *name,
	LOGGING_loglevel_t ll, const LOGGING_char_t *msg)
{
	int retval = -1;

	try
	{
		Logger logger = name ? Logger::getInstance(name) : Logger::getRoot();

		if (logger.isEnabledFor(ll))
		{
			logger.forcedLog(ll, msg, 0, -1);
		}

		retval = 0;
	}
	catch (std::exception const &)
	{
		// Fall through.
	}

	return retval;
}


LOGGING_EXPORT int
LOGGING_logger_force_log(const LOGGING_char_t *name, loglevel_t ll,
	const LOGGING_char_t *msgfmt, ...)
{
	int retval = -1;

	try
	{
		Logger logger = name ? Logger::getInstance(name) : Logger::getRoot();
		const tchar * msg = nullptr;
		snprintf_buf buf;
		std::va_list ap;

		do
		{
			va_start(ap, msgfmt);
			retval = buf.print_va_list(msg, msgfmt, ap);
			va_end(ap);
		} while (retval == -1);

		logger.forcedLog(ll, msg, 0, -1);

		retval = 0;
	}
	catch (std::exception const &)
	{
		// Fall through.
	}

	return retval;
}


LOGGING_EXPORT int
LOGGING_logger_force_log_str(const LOGGING_char_t *name, loglevel_t ll,
	const LOGGING_char_t *msg)
{
	int retval = -1;

	try
	{
		Logger logger = name ? Logger::getInstance(name) : Logger::getRoot();
		logger.forcedLog(ll, msg, 0, -1);
		retval = 0;
	}
	catch (std::exception const &)
	{
		// Fall through.
	}

	return retval;
}


namespace logging {

	namespace internal {

		tstring const &
			CustomLogLevelManager::customToStringMethod(LogLevel ll)
		{
			CustomLogLevelManager & customLogLevelManager = getCustomLogLevelManager();
			return customLogLevelManager.customToStringMethodWorker(ll);
		}

		LogLevel
			CustomLogLevelManager::customFromStringMethod(const tstring& nm)
		{
			CustomLogLevelManager & customLogLevelManager = getCustomLogLevelManager();
			return customLogLevelManager.customFromStringMethodWorker(nm);
		}

	} // namespace internal

} // namespace logging


LOGGING_EXPORT int
LOGGING_add_log_level(unsigned int ll, const LOGGING_char_t *ll_name)
{
	if (ll == 0 || !ll_name)
		return EINVAL;

	tstring nm(ll_name);
	if (logging::internal::getCustomLogLevelManager().add(ll, nm) == true)
		return 0;

	return -1;
}

LOGGING_EXPORT int
LOGGING_remove_log_level(unsigned int ll, const LOGGING_char_t *ll_name)
{
	if (ll == 0 || !ll_name)
		return EINVAL;

	tstring nm(ll_name);
	if (logging::internal::getCustomLogLevelManager().remove(ll, nm) == true)
		return 0;

	return -1;
}
