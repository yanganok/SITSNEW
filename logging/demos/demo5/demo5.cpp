#include <logging/logging.h>

using namespace logging;

int main()
{
	logging::Initializer initializer;

	SharedAppenderPtr appender(new  ConsoleAppender());
	appender->setName(LOGGING_TEXT("appender"));

	Layout * layout = new TTCCLayout;

	appender->setLayout(std::unique_ptr<Layout>(layout));

	auto logger = Logger::getInstance(LOGGING_TEXT("logger"));

	logger.setLogLevel(logging::INFO_LOG_LEVEL);

	logger.addAppender(appender);

	for (size_t i = 0; i < 10; i++)
	{
		LOGGING_TRACE(logger, "Entering loop #" << i << " This is the trace log message...");
		LOGGING_DEBUG(logger, "Entering loop #" << i << " This is the debug log message...");
		LOGGING_INFO(logger, "Entering loop #" << i << " This is the info log message...");
		LOGGING_WARN(logger, "Entering loop #" << i << " This is the warn log message...");
		LOGGING_ERROR(logger, "Entering loop #" << i << " This is the error log message...");
		LOGGING_FATAL(logger, "Entering loop #" << i << " This is the fatal log message...");
	}
}

