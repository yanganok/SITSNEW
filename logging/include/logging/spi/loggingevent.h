#ifndef LOGGING_SPI_INTERNAL_LOGGING_EVENT_HEADER_
#define LOGGING_SPI_INTERNAL_LOGGING_EVENT_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <memory>
#include <logging/loglevel.h>
#include <logging/ndc.h>
#include <logging/mdc.h>
#include <logging/tstring.h>
#include <logging/helpers/timehelper.h>
#include <logging/thread/threads.h>

namespace logging {
	namespace spi {
		/**
		 * The internal representation of logging events. When an affirmative
		 * decision is made to log then a <code>InternalLoggingEvent</code>
		 * instance is created. This instance is passed around to the
		 * different logging components.
		 *
		 * This class is of concern to those wishing to extend logging.
		 */
		class LOGGING_EXPORT InternalLoggingEvent {
		public:
			// Ctors
			   /**
				* Instantiate a LoggingEvent from the supplied parameters.
				*
				* @param logger   The logger of this event.
				* @param loglevel The LogLevel of this event.
				* @param message  The message of this event.
				* @param filename Name of file where this event has occurred,
				* can be NULL.
				* @param line     Line number in file specified by
				*                 the <code>filename</code> parameter.
				* @param function Name of function that is logging this event.
				*/
			InternalLoggingEvent(const logging::tstring& logger,
				LogLevel loglevel, const logging::tstring& message,
				const char* filename, int line, const char * function = nullptr);

			InternalLoggingEvent(const logging::tstring& logger,
				LogLevel loglevel, const logging::tstring& ndc,
				MappedDiagnosticContextMap const & mdc,
				const logging::tstring& message,
				const logging::tstring& thread,
				logging::helpers::Time time, const logging::tstring& file,
				int line, const logging::tstring & function
				= logging::tstring()) LOGGING_ATTRIBUTE_DEPRECATED;

			InternalLoggingEvent(const logging::tstring& logger,
				LogLevel loglevel, const logging::tstring& ndc,
				MappedDiagnosticContextMap const & mdc,
				const logging::tstring& message,
				const logging::tstring& thread,
				const logging::tstring& thread2,
				logging::helpers::Time time, const logging::tstring& file,
				int line, const logging::tstring & function
				= logging::tstring());

			InternalLoggingEvent();

			InternalLoggingEvent(
				const logging::spi::InternalLoggingEvent& rhs);

			virtual ~InternalLoggingEvent();

			void setLoggingEvent(const logging::tstring & logger,
				LogLevel ll, const logging::tstring & message,
				const char * filename, int line,
				const char * function = nullptr);

			void setFunction(char const * func);
			void setFunction(logging::tstring const &);


			// public virtual methods
			  /** The application supplied message of logging event. */
			virtual const logging::tstring& getMessage() const;

			/** Returns the 'type' of InternalLoggingEvent.  Derived classes
			 *  should override this method.  (NOTE: Values <= 1000 are
			 *  reserved for logging and should not be used.)
			 */
			virtual unsigned int getType() const;

			/** Returns a copy of this object.  Derived classes
			  *  should override this method.
			  */
			virtual std::unique_ptr<InternalLoggingEvent> clone() const;


			// public methods
			  /** The logger of the logging event. It is set by
			   *  the LoggingEvent constructor.
			   */
			const logging::tstring& getLoggerName() const
			{
				return loggerName;
			}

			/** LogLevel of logging event. */
			LogLevel getLogLevel() const
			{
				return ll;
			}

			/** The nested diagnostic context (NDC) of logging event. */
			const logging::tstring& getNDC() const
			{
				if (!ndcCached)
				{
					ndc = logging::getNDC().get();
					ndcCached = true;
				}
				return ndc;
			}

			MappedDiagnosticContextMap const & getMDCCopy() const
			{
				if (!mdcCached)
				{
					mdc = logging::getMDC().getContext();
					mdcCached = true;
				}
				return mdc;
			}

			tstring const & getMDC(tstring const & key) const;

			/** The name of thread in which this logging event was generated. */
			const logging::tstring& getThread() const
			{
				if (!threadCached)
				{
					thread = thread::getCurrentThreadName();
					threadCached = true;
				}
				return thread;
			}

			//! The alternative name of thread in which this logging event
			//! was generated.
			const logging::tstring& getThread2() const
			{
				if (!thread2Cached)
				{
					thread2 = thread::getCurrentThreadName2();
					thread2Cached = true;
				}
				return thread2;
			}


			/** Time stamp when the event was created. */
			const logging::helpers::Time& getTimestamp() const
			{
				return timestamp;
			}

			/** The is the file where this log statement was written */
			const logging::tstring& getFile() const
			{
				return file;
			}

			/** The is the line where this log statement was written */
			int getLine() const { return line; }

			logging::tstring const & getFunction() const
			{
				return function;
			}

			void gatherThreadSpecificData() const;

			void swap(InternalLoggingEvent &);

			// public operators
			logging::spi::InternalLoggingEvent&
				operator=(const logging::spi::InternalLoggingEvent& rhs);

			// static methods
			static unsigned int getDefaultType();

		protected:
			// Data
			logging::tstring message;
			logging::tstring loggerName;
			LogLevel ll;
			mutable logging::tstring ndc;
			mutable MappedDiagnosticContextMap mdc;
			mutable logging::tstring thread;
			mutable logging::tstring thread2;
			logging::helpers::Time timestamp;
			logging::tstring file;
			logging::tstring function;
			int line;
			/** Indicates whether or not the Threadname has been retrieved. */
			mutable bool threadCached;
			mutable bool thread2Cached;
			/** Indicates whether or not the NDC has been retrieved. */
			mutable bool ndcCached;
			/** Indicates whether or not the MDC has been retrieved. */
			mutable bool mdcCached;
		};

	} // end namespace spi
} // end namespace logging

#endif // LOGGING_SPI_INTERNAL_LOGGING_EVENT_HEADER_
