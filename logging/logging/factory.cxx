#include <logging/spi/factory.h>
#include <logging/spi/loggerfactory.h>
#include <logging/helpers/loglog.h>
#include <logging/helpers/thread-config.h>
#include <logging/helpers/property.h>
#include <logging/asyncappender.h>
#include <logging/consoleappender.h>
#include <logging/fileappender.h>
#include <logging/nteventlogappender.h>
#include <logging/nullappender.h>
#include <logging/socketappender.h>
#include <logging/syslogappender.h>
#include <logging/win32debugappender.h>
#include <logging/win32consoleappender.h>
#include <logging/log4judpappender.h>


///////////////////////////////////////////////////////////////////////////////
// LOCAL file class definitions
///////////////////////////////////////////////////////////////////////////////

namespace logging {

	namespace spi {

		BaseFactory::~BaseFactory()
		{ }


		AppenderFactory::AppenderFactory()
		{ }

		AppenderFactory::~AppenderFactory()
		{ }


		LayoutFactory::LayoutFactory()
		{ }

		LayoutFactory::~LayoutFactory()
		{ }


		FilterFactory::FilterFactory()
		{ }

		FilterFactory::~FilterFactory()
		{ }


		LocaleFactory::LocaleFactory()
		{ }

		LocaleFactory::~LocaleFactory()
		{ }


		LoggerFactory::~LoggerFactory()
		{ }


		namespace
		{

			class GlobalLocale
				: public LocalFactoryBase<LocaleFactory>
			{
			public:
				explicit
					GlobalLocale(tchar const * n)
					: LocalFactoryBase<LocaleFactory>(n)
				{ }

				ProductPtr
					createObject(const logging::helpers::Properties &) override
				{
					return std::locale();
				}
			};


			class UserLocale
				: public LocalFactoryBase<LocaleFactory>
			{
			public:
				explicit
					UserLocale(tchar const * n)
					: LocalFactoryBase<LocaleFactory>(n)
				{ }

				ProductPtr
					createObject(const logging::helpers::Properties &) override
				{
					return std::locale("");
				}
			};


			class ClassicLocale
				: public LocalFactoryBase<LocaleFactory>
			{
			public:
				explicit
					ClassicLocale(tchar const * n)
					: LocalFactoryBase<LocaleFactory>(n)
				{ }

				ProductPtr
					createObject(const logging::helpers::Properties &) override
				{
					return std::locale::classic();
				}
			};


		} // namespace




	} // namespace spi


	namespace
	{

		template <typename Factory>
		struct DisableFactoryLocking
		{
			typedef Factory factory_type;

			explicit
				DisableFactoryLocking(factory_type & f)
				: factory(f)
			{
				factory._enableLocking(false);
			}

			~DisableFactoryLocking()
			{
				factory._enableLocking(true);
			}

			factory_type & factory;
		};

	} // namespace


	void initializeFactoryRegistry()
	{
		spi::AppenderFactoryRegistry& reg = spi::getAppenderFactoryRegistry();
		DisableFactoryLocking<spi::AppenderFactoryRegistry> dfl_reg(reg);
		LOGGING_REG_APPENDER(reg, ConsoleAppender);
		LOGGING_REG_APPENDER(reg, NullAppender);
		LOGGING_REG_APPENDER(reg, FileAppender);
		LOGGING_REG_APPENDER(reg, RollingFileAppender);
		LOGGING_REG_APPENDER(reg, DailyRollingFileAppender);
		LOGGING_REG_APPENDER(reg, TimeBasedRollingFileAppender);
		LOGGING_REG_APPENDER(reg, SocketAppender);
#if defined(_WIN32)
#  if defined(LOGGING_HAVE_NT_EVENT_LOG)
		LOGGING_REG_APPENDER(reg, NTEventLogAppender);
#  endif
#  if defined(LOGGING_HAVE_WIN32_CONSOLE)
		LOGGING_REG_APPENDER(reg, Win32ConsoleAppender);
#  endif
		LOGGING_REG_APPENDER(reg, Win32DebugAppender);
#endif
		LOGGING_REG_APPENDER(reg, SysLogAppender);
#ifndef LOGGING_SINGLE_THREADED
		LOGGING_REG_APPENDER(reg, AsyncAppender);
#endif
		LOGGING_REG_APPENDER(reg, Log4jUdpAppender);

		spi::LayoutFactoryRegistry& reg2 = spi::getLayoutFactoryRegistry();
		DisableFactoryLocking<spi::LayoutFactoryRegistry> dfl_reg2(reg2);
		LOGGING_REG_LAYOUT(reg2, SimpleLayout);
		LOGGING_REG_LAYOUT(reg2, TTCCLayout);
		LOGGING_REG_LAYOUT(reg2, PatternLayout);

		spi::FilterFactoryRegistry& reg3 = spi::getFilterFactoryRegistry();
		DisableFactoryLocking<spi::FilterFactoryRegistry> dfl_reg3(reg3);
		LOGGING_REG_FILTER(reg3, DenyAllFilter);
		LOGGING_REG_FILTER(reg3, LogLevelMatchFilter);
		LOGGING_REG_FILTER(reg3, LogLevelRangeFilter);
		LOGGING_REG_FILTER(reg3, StringMatchFilter);
		LOGGING_REG_FILTER(reg3, NDCMatchFilter);
		LOGGING_REG_FILTER(reg3, MDCMatchFilter);

		spi::LocaleFactoryRegistry& reg4 = spi::getLocaleFactoryRegistry();
		DisableFactoryLocking<spi::LocaleFactoryRegistry> dfl_reg4(reg4);
		LOGGING_REG_LOCALE(reg4, LOGGING_TEXT("GLOBAL"), spi::GlobalLocale);
		LOGGING_REG_LOCALE(reg4, LOGGING_TEXT("DEFAULT"), spi::GlobalLocale);
		LOGGING_REG_LOCALE(reg4, LOGGING_TEXT("USER"), spi::UserLocale);
		LOGGING_REG_LOCALE(reg4, LOGGING_TEXT("CLASSIC"), spi::ClassicLocale);
	}


} // namespace logging
