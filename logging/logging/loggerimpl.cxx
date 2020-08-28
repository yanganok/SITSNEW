#include <logging/internal/internal.h>
#include <logging/spi/loggerimpl.h>
#include <logging/appender.h>
#include <logging/hierarchy.h>
#include <logging/helpers/loglog.h>
#include <logging/spi/loggingevent.h>
#include <logging/spi/rootlogger.h>
#include <logging/thread/syncprims-pub-impl.h>


namespace logging {
	namespace spi {

		//////////////////////////////////////////////////////////////////////////////
		// Logger Constructors and Destructor
		//////////////////////////////////////////////////////////////////////////////
		LoggerImpl::LoggerImpl(const logging::tstring& name_, Hierarchy& h)
			: name(name_),
			ll(NOT_SET_LOG_LEVEL),
			parent(nullptr),
			additive(true),
			hierarchy(h)
		{
		}


		LoggerImpl::~LoggerImpl()
		{
		}


		//////////////////////////////////////////////////////////////////////////////
		// Logger Methods
		//////////////////////////////////////////////////////////////////////////////

		void
			LoggerImpl::callAppenders(const InternalLoggingEvent& event)
		{
			int writes = 0;
			for (const LoggerImpl* c = this; c != nullptr; c = c->parent.get()) {
				writes += c->appendLoopOnAppenders(event);
				if (!c->additive) {
					break;
				}
			}

			// No appenders in hierarchy, warn user only once.
			if (!hierarchy.emittedNoAppenderWarning && writes == 0) {
				helpers::getLogLog().error(
					LOGGING_TEXT("No appenders could be found for logger (")
					+ getName()
					+ LOGGING_TEXT(")."));
				helpers::getLogLog().error(
					LOGGING_TEXT("Please initialize the logging system properly."));
				hierarchy.emittedNoAppenderWarning = true;
			}
		}


		void
			LoggerImpl::closeNestedAppenders()
		{
			SharedAppenderPtrList appenders = getAllAppenders();
			for (auto & appenderPtr : appenders)
			{
				Appender & appender = *appenderPtr;
				if (!appender.isClosed())
					appender.close();
			}
		}


		bool
			LoggerImpl::isEnabledFor(LogLevel loglevel) const
		{
			if (hierarchy.disableValue >= loglevel) {
				return false;
			}
			return loglevel >= getChainedLogLevel();
		}


		void
			LoggerImpl::log(LogLevel loglevel,
				const logging::tstring& message,
				const char* file,
				int line,
				const char* function)
		{
			if (isEnabledFor(loglevel)) {
				forcedLog(loglevel, message, file, line, function ? function : "");
			}
		}


		void
			LoggerImpl::log(spi::InternalLoggingEvent const & ev)
		{
			if (isEnabledFor(ev.getLogLevel()))
				forcedLog(ev);
		}


		LogLevel
			LoggerImpl::getChainedLogLevel() const
		{
			for (const LoggerImpl *c = this; c != nullptr; c = c->parent.get()) {
				if (c->ll != NOT_SET_LOG_LEVEL) {
					return c->ll;
				}
			}

			helpers::getLogLog().error(
				LOGGING_TEXT("LoggerImpl::getChainedLogLevel()- No valid LogLevel found"),
				true);
			return NOT_SET_LOG_LEVEL;
		}


		Hierarchy&
			LoggerImpl::getHierarchy() const
		{
			return hierarchy;
		}


		bool
			LoggerImpl::getAdditivity() const
		{
			return additive;
		}


		void
			LoggerImpl::setAdditivity(bool additive_)
		{
			additive = additive_;
		}


		void
			LoggerImpl::forcedLog(LogLevel loglevel,
				const logging::tstring& message,
				const char* file,
				int line,
				const char* function)
		{
			spi::InternalLoggingEvent & ev = internal::get_ptd()->forced_log_ev;
			assert(function);
			ev.setLoggingEvent(this->getName(), loglevel, message, file, line,
				function);
			callAppenders(ev);
		}


		void
			LoggerImpl::forcedLog(spi::InternalLoggingEvent const & ev)
		{
			callAppenders(ev);
		}


	}
} // namespace logging { namespace spi {
