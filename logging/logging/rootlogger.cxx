#include <logging/spi/rootlogger.h>
#include <logging/helpers/loglog.h>
#include <logging/thread/syncprims-pub-impl.h>


namespace logging {
	namespace spi {


		//////////////////////////////////////////////////////////////////////////////
		// RootLogger Constructor
		//////////////////////////////////////////////////////////////////////////////

		RootLogger::RootLogger(Hierarchy& h, LogLevel loglevel)
			: LoggerImpl(LOGGING_TEXT("root"), h)
		{
			setLogLevel(loglevel);
		}



		//////////////////////////////////////////////////////////////////////////////
		// Logger Methods
		//////////////////////////////////////////////////////////////////////////////

		LogLevel
			RootLogger::getChainedLogLevel() const
		{
			return ll;
		}


		void
			RootLogger::setLogLevel(LogLevel loglevel)
		{
			if (loglevel == NOT_SET_LOG_LEVEL) {
				helpers::getLogLog().error(
					LOGGING_TEXT("You have tried to set NOT_SET_LOG_LEVEL to root."));
			}
			else {
				LoggerImpl::setLogLevel(loglevel);
			}
		}


	}
} // namespace logging { namespace spi {
