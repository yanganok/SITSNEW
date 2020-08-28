#include <logging/logging.h>
#include <iomanip>

using namespace std;

using namespace logging;

int main()
{
	logging::Initializer initializer;

	SharedAppenderPtr appender(new ConsoleAppender());

	auto root = Logger::getRoot();

	root.addAppender(appender);

	LOGGING_DEBUG(root, "This is" << " a reall" << "y long message." << std::endl << "Just testing it out" << std::endl << "What do you think?");

	LOGGING_DEBUG(root, "This is a bool: " << true);
	LOGGING_INFO(root, "This is a char: " << 'x');
	LOGGING_INFO(root, "This is a short: " << static_cast<short>(-100));
	LOGGING_INFO(root, "This is a unsigned short: " << static_cast<unsigned short>(100));
	LOGGING_INFO(root, "This is a int: " << 1000);
	LOGGING_INFO(root, "This is a unsigned int: " << 1000u);
	LOGGING_INFO(root, "This is a long(hex): " << std::hex << 100000000l);
	LOGGING_INFO(root, "This is a unsigned long: " << 100000000ul);
	LOGGING_WARN(root, "This is a float: " << 1.2345f);
	LOGGING_ERROR(root, "This is a double: " << setprecision(15) << 1.2345234234);
	LOGGING_FATAL(root, "This is a long double: " << setprecision(15) << 123452342342.25L);
	LOGGING_WARN(root, "The following message is empty:");
	LOGGING_WARN(root, "");
}

