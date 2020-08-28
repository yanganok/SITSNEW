#include <logging/logging.h>

using namespace logging;

int main()
{
	logging::Initializer initializer;

	SharedAppenderPtr appender(new  ConsoleAppender());
	appender->setLayout(std::unique_ptr<Layout>(new TTCCLayout));

	auto logger = Logger::getInstance(LOGGING_TEXT("logger"));

	logger.addAppender(SharedAppenderPtr(appender.get()));

	NDC& _ndc = logging::getNDC();

	_ndc.push(LOGGING_TEXT("_ndc"));

	LOGGING_DEBUG(logger, "this is a NDC test");

	_ndc.pop();

	LOGGING_DEBUG(logger, "There should be no NDC...");

	_ndc.remove();



	NDCContextCreator _first_ndc(LOGGING_TEXT("_first_ndc"));

	LOGGING_DEBUG(logger, "this is a NDC test");

	_ndc.pop();

	LOGGING_DEBUG(logger, "There should be no NDC...");


	NDCContextCreator _second_ndc(LOGGING_TEXT("_second_ndc"));

	LOGGING_DEBUG(logger, "this is a NDC test");

	_ndc.remove();

	LOGGING_DEBUG(logger, "There should be no NDC...");
}

