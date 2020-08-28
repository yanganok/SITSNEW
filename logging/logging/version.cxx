#include <logging/version.h>


namespace logging
{

#if ! defined (LOGGING_VERSION_STR_SUFFIX)
#define LOGGING_VERSION_STR_SUFFIX ""
#endif

	unsigned const version = LOGGING_VERSION;
	char const versionStr[] = LOGGING_VERSION_STR LOGGING_VERSION_STR_SUFFIX;

}
