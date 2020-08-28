#ifndef LOGGING_SPI_APPENDER_ATTACHABLE_HEADER_
#define LOGGING_SPI_APPENDER_ATTACHABLE_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/appender.h>
#include <logging/tstring.h>
#include <logging/helpers/pointer.h>
#include <vector>

namespace logging {
	// Forward Declarations
	typedef std::vector<logging::SharedAppenderPtr> SharedAppenderPtrList;

	namespace spi {

		/**
		 * This Interface is for attaching Appenders to objects.
		 */
		class LOGGING_EXPORT AppenderAttachable {
		public:
			// Methods
			  /**
			   * Add an appender.
			   */
			virtual void addAppender(SharedAppenderPtr newAppender) = 0;

			/**
			 * Get all previously added appenders as an Enumeration.
			 */
			virtual SharedAppenderPtrList getAllAppenders() = 0;

			/**
			 * Get an appender by name.
			 */
			virtual SharedAppenderPtr getAppender(const logging::tstring& name) = 0;

			/**
			 * Remove all previously added appenders.
			 */
			virtual void removeAllAppenders() = 0;

			/**
			 * Remove the appender passed as parameter from the list of appenders.
			 */
			virtual void removeAppender(SharedAppenderPtr appender) = 0;

			/**
			 * Remove the appender with the name passed as parameter from the
			 * list of appenders.
			 */
			virtual void removeAppender(const logging::tstring& name) = 0;

			// Dtor
			virtual ~AppenderAttachable() = 0;
		};

	} // end namespace spi
} // end namespace logging

#endif // LOGGING_SPI_APPENDER_ATTACHABLE_HEADER_
