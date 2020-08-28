#include "..\include\logging\logging.h"

int main()
{
	logging::Initializer initializer;

	auto logger = logging::create(LOGGING_TEXT("../output/demo2.txt"));

	for (size_t j = 0; j < 10; j++)
	{
		logger.write(LOGGING_TEXT("This is the write file message..."));
	}
}

