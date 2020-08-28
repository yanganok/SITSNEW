#include <logging/thread/impl/tls.h>


namespace logging {
	namespace thread {
		namespace impl {


#if defined (LOGGING_SINGLE_THREADED)

			//! This is intentionally allocated using freestore and leaked. The
			//! amount is small (so far only 1 length vector). This is to avoid
			//! initialization order fiasco.
			std::vector<tls_value_type> * tls_single_threaded_values;

#endif


		}
	}
} // namespace logging { namespace thread { namespace impl {
