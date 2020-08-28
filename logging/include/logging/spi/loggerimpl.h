#ifndef LOGGING_SPI_LOGGER_HEADER_
#define LOGGING_SPI_LOGGER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/tstring.h>
#include <logging/helpers/appenderattachableimpl.h>
#include <logging/helpers/pointer.h>
#include <logging/spi/loggerfactory.h>
#include <memory>
#include <vector>


namespace logging {
	class DefaultLoggerFactory;

	namespace spi {

		/**
		 * This is the central class in the logging package. One of the
		 * distintive features of logging are hierarchical loggers and their
		 * evaluation.
		 */
		class LOGGING_EXPORT LoggerImpl
			: public virtual logging::helpers::SharedObject,
			public logging::helpers::AppenderAttachableImpl
		{
		public:
			typedef helpers::SharedObjectPtr<LoggerImpl> SharedLoggerImplPtr;

			// Methods

			  /**
			   * Call the appenders in the hierrachy starting at
			   * <code>this</code>.  If no appenders could be found, emit a
			   * warning.
			   *
			   * This method calls all the appenders inherited from the
			   * hierarchy circumventing any evaluation of whether to log or not
			   * to log the particular log request.
			   *
			   * @param event The event to log.
			   */
			virtual void callAppenders(const InternalLoggingEvent& event);

			/**
			 * Close all attached appenders implementing the AppenderAttachable
			 * interface.
			 */
			virtual void closeNestedAppenders();

			/**
			 * Check whether this logger is enabled for a given LogLevel passed
			 * as parameter.
			 *
			 * @return boolean True if this logger is enabled for <code>ll</code>.
			 */
			virtual bool isEnabledFor(LogLevel ll) const;

			/**
			 * This generic form is intended to be used by wrappers.
			 */
			virtual void log(LogLevel ll, const logging::tstring& message,
				const char* file = nullptr, int line = -1,
				const char* function = nullptr);

			virtual void log(spi::InternalLoggingEvent const &);

			/**
			 * Starting from this logger, search the logger hierarchy for a
			 * "set" LogLevel and return it. Otherwise, return the LogLevel of the
			 * root logger.
			 *
			 * The Logger class is designed so that this method executes as
			 * quickly as possible.
			 */
			virtual LogLevel getChainedLogLevel() const;

			/**
			 * Returns the assigned LogLevel, if any, for this Logger.
			 *
			 * @return LogLevel - the assigned LogLevel.
			 */
			LogLevel getLogLevel() const { return this->ll; }

			/**
			 * Set the LogLevel of this Logger.
			 */
			void setLogLevel(LogLevel _ll) { this->ll = _ll; }

			/**
			 * Return the the {@link Hierarchy} where this <code>Logger</code>
			 * instance is attached.
			 */
			virtual Hierarchy& getHierarchy() const;

			/**
			 * Return the logger name.
			 */
			logging::tstring const & getName() const { return name; }

			/**
			 * Get the additivity flag for this Logger instance.
			 */
			bool getAdditivity() const;

			/**
			 * Set the additivity flag for this Logger instance.
			 */
			void setAdditivity(bool additive);

			virtual ~LoggerImpl();

		protected:
			// Ctors
			  /**
			   * This constructor created a new <code>Logger</code> instance and
			   * sets its name.
			   *
			   * It is intended to be used by sub-classes only. You should not
			   * create loggers directly.
			   *
			   * @param name The name of the logger.
			   * @param h Hierarchy
			   */
			LoggerImpl(const logging::tstring& name, Hierarchy& h);


			// Methods
			  /**
			   * This method creates a new logging event and logs the event
			   * without further checks.
			   */
			virtual void forcedLog(LogLevel ll,
				const logging::tstring& message,
				const char* file,
				int line,
				const char* function);

			virtual void forcedLog(spi::InternalLoggingEvent const & ev);


			// Data
			  /** The name of this logger */
			logging::tstring name;

			/**
			 * The assigned LogLevel of this logger.
			 */
			LogLevel ll;

			/**
			 * The parent of this logger. All loggers have at least one
			 * ancestor which is the root logger.
			 */
			SharedLoggerImplPtr parent;

			/**
			 * Additivity is set to true by default, that is children inherit
			 * the appenders of their ancestors by default. If this variable is
			 * set to <code>false</code> then the appenders found in the
			 * ancestors of this logger are not used. However, the children
			 * of this logger will inherit its appenders, unless the children
			 * have their additivity flag set to <code>false</code> too. See
			 * the user manual for more details.
			 */
			bool additive;

		private:
			// Data
			  /** Loggers need to know what Hierarchy they are in. */
			Hierarchy& hierarchy;

			// Disallow copying of instances of this class
			LoggerImpl(const LoggerImpl&) = delete;
			LoggerImpl& operator=(const LoggerImpl&) = delete;

			// Friends
			friend class logging::Logger;
			friend class logging::DefaultLoggerFactory;
			friend class logging::Hierarchy;
		};

		typedef LoggerImpl::SharedLoggerImplPtr SharedLoggerImplPtr;

	} // end namespace spi
} // end namespace logging

#endif // LOGGING_SPI_LOGGER_HEADER_
