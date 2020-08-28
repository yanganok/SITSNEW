#ifndef LOGGING_SPI_ROOT_LOGGER_HEADER_
#define LOGGING_SPI_ROOT_LOGGER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/spi/loggerimpl.h>

namespace logging {
	namespace spi {

		/**
		 * RootLogger sits at the top of the logger hierachy. It is a
		 * regular logger except that it provides several guarantees.
		 *
		 * First, it cannot be assigned a <code>NOT_SET_LOG_LEVEL</code>
		 * LogLevel. Second, since root logger cannot have a parent, the
		 * getChainedLogLevel method always returns the value of the
		 * ll field without walking the hierarchy.
		 */
		class LOGGING_EXPORT RootLogger : public LoggerImpl {
		public:
			// Ctors
			  /**
			   * The root logger names itself as "root". However, the root
			   * logger cannot be retrieved by name.
			   */
			RootLogger(Hierarchy& h, LogLevel ll);

			// Methods
			  /**
			   * Return the assigned LogLevel value without walking the logger
			   * hierarchy.
			   */
			virtual LogLevel getChainedLogLevel() const;

			/**
			 * Setting a NOT_SET_LOG_LEVEL value to the LogLevel of the root logger
			 * may have catastrophic results. We prevent this here.
			 */
			void setLogLevel(LogLevel);

		};

	} // end namespace spi
} // end namespace logging

#endif // LOGGING_SPI_ROOT_LOGGER_HEADER_

