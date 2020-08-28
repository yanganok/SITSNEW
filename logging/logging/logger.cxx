#include <logging/logger.h>
#include <logging/appender.h>
#include <logging/hierarchy.h>
#include <logging/helpers/loglog.h>
#include <logging/spi/loggerimpl.h>
#include <logging/loggingmacros.h>
#include <utility>


namespace logging
{


	Logger
		DefaultLoggerFactory::makeNewLoggerInstance(const logging::tstring & name,
			Hierarchy& h)
	{
		return Logger(makeNewLoggerImplInstance(name, h));
	}


	spi::LoggerImpl *
		DefaultLoggerFactory::makeNewLoggerImplInstance(const logging::tstring& name,
			Hierarchy& h)
	{
		return new spi::LoggerImpl(name, h);
	}


	//////////////////////////////////////////////////////////////////////////////
	// static Logger Methods
	//////////////////////////////////////////////////////////////////////////////
	//
	Hierarchy &
		Logger::getDefaultHierarchy()
	{
		return logging::getDefaultHierarchy();
	}


	bool
		Logger::exists(const logging::tstring & name)
	{
		return getDefaultHierarchy().exists(name);
	}


	LoggerList
		Logger::getCurrentLoggers()
	{
		return getDefaultHierarchy().getCurrentLoggers();
	}


	Logger
		Logger::getInstance(const logging::tstring& name)
	{
		return getDefaultHierarchy().getInstance(name);
	}


	Logger
		Logger::getInstance(const logging::tstring& name,
			spi::LoggerFactory& factory)
	{
		return getDefaultHierarchy().getInstance(name, factory);
	}


	Logger
		Logger::getRoot()
	{
		return getDefaultHierarchy().getRoot();
	}


	void
		Logger::shutdown()
	{
		getDefaultHierarchy().shutdown();
	}

	void Logger::write(const logging::tstring & msg) const
	{
		auto list = value->getAllAppenders();

		for each (auto appender in list)
		{
			logging::tstring pattern = LOGGING_TEXT("%m%n");

			auto layout = new PatternLayout(pattern);

			appender->setLayout(std::unique_ptr<Layout>(layout));
		}

		LOGGING_INFO(value, msg);

		for each (auto appender in list)
		{
			appender->setLayout();
		}	
	}


	//////////////////////////////////////////////////////////////////////////////
	// Logger ctors and dtor
	//////////////////////////////////////////////////////////////////////////////

	Logger::Logger() LOGGING_NOEXCEPT
	{ }


	Logger::Logger(spi::LoggerImpl * ptr) LOGGING_NOEXCEPT
		: value(ptr)
	{
		if (value)
			value->addReference();
	}


	Logger::Logger(const Logger& rhs) LOGGING_NOEXCEPT
		: spi::AppenderAttachable(rhs)
		, value(rhs.value)
	{
		if (value)
			value->addReference();
	}


	Logger &
		Logger::operator = (const Logger& rhs) LOGGING_NOEXCEPT
	{
		Logger(rhs).swap(*this);
		return *this;
	}


	Logger::Logger(Logger && rhs) LOGGING_NOEXCEPT
		: spi::AppenderAttachable(std::move(rhs))
		, value(rhs.value)
	{
		rhs.value = nullptr;
	}


	Logger &
		Logger::operator = (Logger && rhs) LOGGING_NOEXCEPT
	{
		Logger(std::move(rhs)).swap(*this);
		return *this;
	}


	Logger::~Logger()
	{
		if (value)
			value->removeReference();
	}




	//////////////////////////////////////////////////////////////////////////////
	// Logger Methods
	//////////////////////////////////////////////////////////////////////////////

	void
		Logger::swap(Logger & other) LOGGING_NOEXCEPT
	{
		std::swap(value, other.value);
	}


	Logger
		Logger::getParent() const
	{
		if (value->parent)
			return Logger(value->parent.get());
		else
		{
			helpers::getLogLog().error(
				LOGGING_TEXT("********* This logger has no parent: ")
				+ getName());
			return *this;
		}
	}


	void
		Logger::addAppender(SharedAppenderPtr newAppender)
	{
		value->addAppender(newAppender);
	}


	SharedAppenderPtrList
		Logger::getAllAppenders()
	{
		return value->getAllAppenders();
	}


	SharedAppenderPtr
		Logger::getAppender(const logging::tstring& name)
	{
		return value->getAppender(name);
	}


	void
		Logger::removeAllAppenders()
	{
		value->removeAllAppenders();
	}


	void
		Logger::removeAppender(SharedAppenderPtr appender)
	{
		value->removeAppender(appender);
	}


	void
		Logger::removeAppender(const logging::tstring& name)
	{
		value->removeAppender(name);
	}


	void
		Logger::assertion(bool assertionVal, const logging::tstring& msg) const
	{
		if (!assertionVal)
			log(FATAL_LOG_LEVEL, msg, nullptr, -1);
	}


	void
		Logger::closeNestedAppenders() const
	{
		value->closeNestedAppenders();
	}


	bool
		Logger::isEnabledFor(LogLevel ll) const
	{
		return value->isEnabledFor(ll);
	}


	void
		Logger::log(LogLevel ll, const logging::tstring& message, const char* file, int line, const char* function) const
	{
		value->log(ll, message, file, line, function ? function : "");
	}


	void
		Logger::log(spi::InternalLoggingEvent const & ev) const
	{
		value->log(ev);
	}


	void
		Logger::forcedLog(LogLevel ll, const logging::tstring& message, const char* file, int line, const char* function) const
	{
		value->forcedLog(ll, message, file, line, function ? function : "");
	}


	void
		Logger::forcedLog(spi::InternalLoggingEvent const & ev) const
	{
		value->forcedLog(ev);
	}


	void
		Logger::callAppenders(const spi::InternalLoggingEvent& event) const
	{
		value->callAppenders(event);
	}


	LogLevel
		Logger::getChainedLogLevel() const
	{
		return value->getChainedLogLevel();
	}


	LogLevel
		Logger::getLogLevel() const
	{
		return value->getLogLevel();
	}


	void
		Logger::setLogLevel(LogLevel ll)
	{
		value->setLogLevel(ll);
	}


	Hierarchy &
		Logger::getHierarchy() const
	{
		return value->getHierarchy();
	}


	logging::tstring const &
		Logger::getName() const
	{
		return value->getName();
	}


	bool
		Logger::getAdditivity() const
	{
		return value->getAdditivity();
	}


	void Logger::setAdditivity(bool additive)
	{
		value->setAdditivity(additive);
	}




} // namespace logging
