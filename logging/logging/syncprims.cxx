#include <sstream>
#include <stdexcept>
#define LOGGING_ENABLE_SYNCPRIMS_PUB_IMPL
#include <logging/thread/syncprims-pub-impl.h>


namespace logging {
	namespace thread {


		namespace impl
		{


			LOGGING_EXPORT
				void
				syncprims_throw_exception(char const * const msg, char const * const file,
					int line)
			{
				std::ostringstream oss;
				oss << file << ":" << line << ": " << msg;
				throw std::runtime_error(oss.str());
			}


		}


	}
} // namespace logging { namespace thread namespace impl {
