#ifndef LOGGING_LOGGERHEADER_
#define LOGGING_LOGGERHEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/loglevel.h>
#include <logging/tstring.h>
#include <logging/spi/appenderattachable.h>
#include <logging/spi/loggerfactory.h>

#include <vector>


namespace logging
{
	// Forward declarations

	class Appender;
	class Hierarchy;
	class HierarchyLocker;
	class DefaultLoggerFactory;

	namespace spi
	{
		class LoggerImpl;
	}


	/** \typedef std::vector<Logger> LoggerList
	 * This is a list of {@link Logger Loggers}. */
	typedef std::vector<Logger> LoggerList;


	/**
	 * This is the central class in the logging package. One of the
	 * distintive features of logging are hierarchical loggers and their
	 * evaluation.
	 */
	class LOGGING_EXPORT Logger : public logging::spi::AppenderAttachable
	{
	public:
		//////////////////////////////////////////////////////////////////////////////
		// Static Methods
		//////////////////////////////////////////////////////////////////////////////

		/**
		   * Returns <code>true </code>if the named logger exists
		   * (in the default hierarchy).
		   *
		   * @param name The name of the logger to search for.
		   */
		static bool exists(const logging::tstring& name);

		/*
		 * Returns all the currently defined loggers in the default
		 * hierarchy.
		 *
		 * The root logger is <em>not</em> included in the returned
		 * list.
		*/
		static LoggerList getCurrentLoggers();

		/**
		 * Return the default Hierarchy instance.
		 */
		static Hierarchy& getDefaultHierarchy();

		/**
		 * Retrieve a logger with name <code>name</code>.  If the named
		 * logger already exists, then the existing instance will be returned.
		 * Otherwise, a new instance is created.
		 *
		 * By default, loggers do not have a set LogLevel but inherit
		 * it from the hierarchy. This is one of the central features of
		 * logging.
		 *
		 * @param name The name of the logger to retrieve.
		 */
		static Logger getInstance(const logging::tstring& name);

		/**
		 * Like getInstance() except that the type of logger
		 * instantiated depends on the type returned by the {@link
		 * spi::LoggerFactory#makeNewLoggerInstance} method of the
		 * <code>factory</code> parameter.
		 *
		 * This method is intended to be used by sub-classes.
		 *
		 * @param name The name of the logger to retrieve.
		 * @param factory A {@link spi::LoggerFactory} implementation that will
		 * actually create a new Instance.
		 */
		static Logger getInstance(const logging::tstring& name,
			spi::LoggerFactory& factory);

		/**
		 * Return the root of the default logger hierrachy.
		 *
		 * The root logger is always instantiated and available. It's
		 * name is "root".
		 *
		 * Nevertheless, calling {@link #getInstance
		 * Logger.getInstance("root")} does not retrieve the root logger
		 * but a logger just under root named "root".
		 */
		static Logger getRoot();

		/**
		 * Calling this method will <em>safely</em> close and remove all
		 * appenders in all the loggers including root contained in the
		 * default hierachy.
		 *
		 * Some appenders such as SocketAppender need to be closed before the
		 * application exits. Otherwise, pending logging events might be
		 * lost.
		 *
		 * The <code>shutdown</code> method is careful to close nested
		 * appenders before closing regular appenders. This is allows
		 * configurations where a regular appender is attached to a logger
		 * and again to a nested appender.
		 */
		static void shutdown();




		//////////////////////////////////////////////////////////////////////////////
		// Additional Methods
		//////////////////////////////////////////////////////////////////////////////
		void write(const logging::tstring& msg) const;





		//////////////////////////////////////////////////////////////////////////////
		// Non-Static Methods
		//////////////////////////////////////////////////////////////////////////////
		  /**
		   * If <code>assertionVal</code> parameter is <code>false</code>, then
		   * logs <code>msg</code> with FATAL_LOG_LEVEL log level.
		   *
		   * @param assertionVal Truth value of assertion condition.
		   * @param msg The message to print if <code>assertion</code> is
		   * false.
		   */
		void assertion(bool assertionVal, const logging::tstring& msg) const;

		/**
		 * Close all attached appenders implementing the AppenderAttachable
		 * interface.
		 */
		void closeNestedAppenders() const;

		/**
		 * Check whether this logger is enabled for a given
		 * LogLevel passed as parameter.
		 *
		 * @return boolean True if this logger is enabled for <code>ll</code>.
		 */
		bool isEnabledFor(LogLevel ll) const;

		/**
		 * This generic form is intended to be used by wrappers.
		 */
		void log(LogLevel ll, const logging::tstring& message,
			const char* file = LOGGING_CALLER_FILE(),
			int line = LOGGING_CALLER_LINE(),
			const char* function = LOGGING_CALLER_FUNCTION()) const;

		void log(spi::InternalLoggingEvent const &) const;

		/**
		 * This method creates a new logging event and logs the event
		 * without further checks.
		 */
		void forcedLog(LogLevel ll, const logging::tstring& message,
			const char* file = LOGGING_CALLER_FILE(),
			int line = LOGGING_CALLER_LINE(),
			const char* function = LOGGING_CALLER_FUNCTION()) const;

		void forcedLog(spi::InternalLoggingEvent const &) const;

		/**
		 * Call the appenders in the hierrachy starting at
		 * <code>this</code>.  If no appenders could be found, emit a
		 * warning.
		 *
		 * This method calls all the appenders inherited from the
		 * hierarchy circumventing any evaluation of whether to log or not
		 * to log the particular log request.
		 *
		 * @param event the event to log.
		 */
		void callAppenders(const spi::InternalLoggingEvent& event) const;

		/**
		 * Starting from this logger, search the logger hierarchy for a
		 * "set" LogLevel and return it. Otherwise, return the LogLevel of the
		 * root logger.
		 *
		 * The Logger class is designed so that this method executes as
		 * quickly as possible.
		 */
		LogLevel getChainedLogLevel() const;

		/**
		 * Returns the assigned LogLevel, if any, for this Logger.
		 *
		 * @return LogLevel - the assigned LogLevel, can be <code>NOT_SET_LOG_LEVEL</code>.
		 */
		LogLevel getLogLevel() const;

		/**
		 * Set the LogLevel of this Logger.
		 */
		void setLogLevel(LogLevel ll);

		/**
		 * Return the the {@link Hierarchy} where this <code>Logger</code> instance is
		 * attached.
		 */
		Hierarchy& getHierarchy() const;

		/**
		 * Return the logger name.
		 */
		logging::tstring const & getName() const;

		/**
		 * Get the additivity flag for this Logger instance.
		 */
		bool getAdditivity() const;

		/**
		 * Set the additivity flag for this Logger instance.
		 */
		void setAdditivity(bool additive);

		// AppenderAttachable Methods
		virtual void addAppender(SharedAppenderPtr newAppender);

		virtual SharedAppenderPtrList getAllAppenders();

		virtual SharedAppenderPtr getAppender(const logging::tstring& name);

		virtual void removeAllAppenders();

		virtual void removeAppender(SharedAppenderPtr appender);

		virtual void removeAppender(const logging::tstring& name);

		Logger() LOGGING_NOEXCEPT;
		Logger(const Logger& rhs) LOGGING_NOEXCEPT;
		Logger& operator=(const Logger& rhs) LOGGING_NOEXCEPT;
		Logger(Logger && rhs) LOGGING_NOEXCEPT;
		Logger & operator = (Logger && rhs) LOGGING_NOEXCEPT;
		virtual ~Logger();

		void swap(Logger &) LOGGING_NOEXCEPT;

		/**
		 * Used to retrieve the parent of this Logger in the
		 * Logger tree.
		 */
		Logger getParent() const;

	protected:
		// Data
		  /** This is a pointer to the implementation class. */
		spi::LoggerImpl * value = nullptr;

	private:
		// Ctors
		  /**
		   * This constructor created a new <code>Logger</code> instance
		   * with a pointer to a Logger implementation.
		   *
		   * You should not create loggers directly.
		   *
		   * @param ptr A pointer to the Logger implementation.  This value
		   *            cannot be NULL.
		   */
		Logger(spi::LoggerImpl * ptr) LOGGING_NOEXCEPT;

		// Friends
		friend class logging::spi::LoggerImpl;
		friend class logging::Hierarchy;
		friend class logging::HierarchyLocker;
		friend class logging::DefaultLoggerFactory;
	};


	/**
	 * This class is used to create the default implementation of
	 * the Logger class.
	 */
	class LOGGING_EXPORT DefaultLoggerFactory : public spi::LoggerFactory
	{
	public:
		Logger makeNewLoggerInstance(const logging::tstring& name, Hierarchy& h);

	protected:
		virtual spi::LoggerImpl * makeNewLoggerImplInstance(const logging::tstring& name, Hierarchy& h);
	};


} // end namespace logging


#endif // LOGGING_LOGGERHEADER_
