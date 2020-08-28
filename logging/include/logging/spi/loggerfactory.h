#ifndef LOGGING_SPI_LOGGER_FACTORY_HEADER
#define LOGGING_SPI_LOGGER_FACTORY_HEADER

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/tstring.h>


namespace logging {
	// Forward Declarations
	class Logger;
	class Hierarchy;

	namespace spi {
		class LoggerImpl;

		/**
		 * Implement this interface to create new instances of Logger or
		 * a sub-class of Logger.
		 */
		class LOGGING_EXPORT LoggerFactory {
		public:
			/**
			 * Creates a new <code>Logger</code> object.
			 */
			virtual Logger makeNewLoggerInstance(const logging::tstring& name,
				Hierarchy& h) = 0;
			virtual ~LoggerFactory() = 0;

		protected:
			virtual LoggerImpl * makeNewLoggerImplInstance(
				const logging::tstring& name, Hierarchy& h) = 0;
		};

	} // end namespace spi
} // end namespace logging

#endif // LOGGING_SPI_LOGGER_FACTORY_HEADER
