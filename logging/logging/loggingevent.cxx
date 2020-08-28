#include <logging/spi/loggingevent.h>
#include <logging/internal/internal.h>
#include <algorithm>


namespace logging {
	namespace spi {


		static const int LOGGING_DEFAULT_TYPE = 1;


		///////////////////////////////////////////////////////////////////////////////
		// InternalLoggingEvent ctors and dtor
		///////////////////////////////////////////////////////////////////////////////

		InternalLoggingEvent::InternalLoggingEvent(const logging::tstring& logger,
			LogLevel loglevel, const logging::tstring& message_, const char* filename,
			int line_, const char * function_)
			: message(message_)
			, loggerName(logger)
			, ll(loglevel)
			, ndc()
			, mdc()
			, thread()
			, timestamp(logging::helpers::now())
			, file(filename
				? LOGGING_C_STR_TO_TSTRING(filename)
				: logging::tstring())
			, function(function_
				? LOGGING_C_STR_TO_TSTRING(function_)
				: logging::tstring())
			, line(line_)
			, threadCached(false)
			, thread2Cached(false)
			, ndcCached(false)
			, mdcCached(false)
		{
		}


		InternalLoggingEvent::InternalLoggingEvent(const logging::tstring& logger,
			LogLevel loglevel, const logging::tstring& ndc_,
			MappedDiagnosticContextMap const & mdc_, const logging::tstring& message_,
			const logging::tstring& thread_, logging::helpers::Time time,
			const logging::tstring& file_, int line_,
			const logging::tstring & function_)
			: message(message_)
			, loggerName(logger)
			, ll(loglevel)
			, ndc(ndc_)
			, mdc(mdc_)
			, thread(thread_)
			, timestamp(time)
			, file(file_)
			, function(function_)
			, line(line_)
			, threadCached(true)
			, thread2Cached(true)
			, ndcCached(true)
			, mdcCached(true)
		{
		}


		InternalLoggingEvent::InternalLoggingEvent(const logging::tstring& logger,
			LogLevel loglevel, const logging::tstring& ndc_,
			MappedDiagnosticContextMap const & mdc_, const logging::tstring& message_,
			const logging::tstring& thread_, const logging::tstring& thread2_,
			logging::helpers::Time time, const logging::tstring& file_, int line_,
			const logging::tstring & function_)
			: message(message_)
			, loggerName(logger)
			, ll(loglevel)
			, ndc(ndc_)
			, mdc(mdc_)
			, thread(thread_)
			, thread2(thread2_)
			, timestamp(time)
			, file(file_)
			, function(function_)
			, line(line_)
			, threadCached(true)
			, thread2Cached(true)
			, ndcCached(true)
			, mdcCached(true)
		{
		}


		InternalLoggingEvent::InternalLoggingEvent()
			: ll(NOT_SET_LOG_LEVEL)
			, function()
			, line(0)
			, threadCached(false)
			, thread2Cached(false)
			, ndcCached(false)
			, mdcCached(false)
		{ }


		InternalLoggingEvent::InternalLoggingEvent(
			const logging::spi::InternalLoggingEvent& rhs)
			: message(rhs.getMessage())
			, loggerName(rhs.getLoggerName())
			, ll(rhs.getLogLevel())
			, ndc(rhs.getNDC())
			, mdc(rhs.getMDCCopy())
			, thread(rhs.getThread())
			, thread2(rhs.getThread2())
			, timestamp(rhs.getTimestamp())
			, file(rhs.getFile())
			, function(rhs.getFunction())
			, line(rhs.getLine())
			, threadCached(true)
			, thread2Cached(true)
			, ndcCached(true)
			, mdcCached(true)
		{
		}


		InternalLoggingEvent::~InternalLoggingEvent()
		{
		}



		///////////////////////////////////////////////////////////////////////////////
		// InternalLoggingEvent static methods
		///////////////////////////////////////////////////////////////////////////////

		unsigned int
			InternalLoggingEvent::getDefaultType()
		{
			return LOGGING_DEFAULT_TYPE;
		}



		///////////////////////////////////////////////////////////////////////////////
		// InternalLoggingEvent implementation
		///////////////////////////////////////////////////////////////////////////////

		void
			InternalLoggingEvent::setLoggingEvent(const logging::tstring & logger,
				LogLevel loglevel, const logging::tstring & msg, const char * filename,
				int fline, const char * function_)
		{
			// This could be imlemented using the swap idiom:
			//
			// InternalLoggingEvent (logger, loglevel, msg, filename, fline).swap (*this);
			//
			// But that defeats the optimization of using thread local instance
			// of InternalLoggingEvent to avoid memory allocation.

			loggerName = logger;
			ll = loglevel;
			message = msg;
			timestamp = helpers::now();

			if (filename)
				file = LOGGING_C_STR_TO_TSTRING(filename);
			else
				file.clear();

			if (function_)
				function = LOGGING_C_STR_TO_TSTRING(function_);
			else
				function.clear();

			line = fline;
			threadCached = false;
			thread2Cached = false;
			ndcCached = false;
			mdcCached = false;
		}


		void
			InternalLoggingEvent::setFunction(char const * func)
		{
			if (func)
				function = LOGGING_C_STR_TO_TSTRING(func);
			else
				function.clear();
		}


		void
			InternalLoggingEvent::setFunction(logging::tstring const & func)
		{
			function = func;
		}


		const logging::tstring&
			InternalLoggingEvent::getMessage() const
		{
			return message;
		}


		unsigned int
			InternalLoggingEvent::getType() const
		{
			return LOGGING_DEFAULT_TYPE;
		}



		std::unique_ptr<InternalLoggingEvent>
			InternalLoggingEvent::clone() const
		{
			std::unique_ptr<InternalLoggingEvent> tmp(new InternalLoggingEvent(*this));
			return tmp;
		}


		tstring const &
			InternalLoggingEvent::getMDC(tstring const & key) const
		{
			MappedDiagnosticContextMap const & mdc_ = getMDCCopy();
			MappedDiagnosticContextMap::const_iterator it = mdc_.find(key);
			if (it != mdc_.end())
				return it->second;
			else
				return internal::empty_str;
		}



		InternalLoggingEvent &
			InternalLoggingEvent::operator = (const InternalLoggingEvent& rhs)
		{
			InternalLoggingEvent(rhs).swap(*this);
			return *this;
		}


		void
			InternalLoggingEvent::gatherThreadSpecificData() const
		{
			getNDC();
			getMDCCopy();
			getThread();
			getThread2();
		}


		void
			InternalLoggingEvent::swap(InternalLoggingEvent & other)
		{
			using std::swap;

			swap(message, other.message);
			swap(loggerName, other.loggerName);
			swap(ll, other.ll);
			swap(ndc, other.ndc);
			swap(mdc, other.mdc);
			swap(thread, other.thread);
			swap(thread2, other.thread2);
			swap(timestamp, other.timestamp);
			swap(file, other.file);
			swap(function, other.function);
			swap(line, other.line);
			swap(threadCached, other.threadCached);
			swap(thread2Cached, other.thread2Cached);
			swap(ndcCached, other.ndcCached);
		}


	}
} // namespace logging {  namespace spi {
