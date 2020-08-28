#ifndef LOGGING_APPENDER_HEADER_
#define LOGGING_APPENDER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/layout.h>
#include <logging/loglevel.h>
#include <logging/tstring.h>
#include <logging/helpers/pointer.h>
#include <logging/spi/filter.h>
#include <logging/helpers/lockfile.h>

#include <memory>
#include <mutex>
#include <atomic>
#include <condition_variable>


namespace logging {


	namespace helpers
	{

		class Properties;

	}


	/**
	 * This class is used to "handle" errors encountered in an {@link
	 * logging::Appender}.
	 */
	class LOGGING_EXPORT ErrorHandler
	{
	public:
		ErrorHandler();
		virtual ~ErrorHandler() = 0;
		virtual void error(const logging::tstring& err) = 0;
		virtual void reset() = 0;
	};


	class LOGGING_EXPORT OnlyOnceErrorHandler
		: public ErrorHandler
	{
	public:
		// Ctor
		OnlyOnceErrorHandler();
		virtual ~OnlyOnceErrorHandler();
		virtual void error(const logging::tstring& err);
		virtual void reset();

	private:
		bool firstTime;
	};


	/**
	 * Extend this class for implementing your own strategies for printing log
	 * statements.
	 *
	 * <h3>Properties</h3>
	 * <dl>
	 *
	 * <dt><tt>layout</tt></dt>
	 * <dd>This property specifies message layout used by
	 * Appender.
	 * \sa Layout
	 * </dd>
	 *
	 * <dt><tt>filters</tt></dt>
	 * <dd>This property specifies possibly multiple filters used by
	 * Appender. Each of multple filters and its properties is under a
	 * numbered subkey of filters key. E.g.:
	 * <tt>filters.<em>1</em>=logging::spi::LogLevelMatchFilter</tt>. Filter
	 * subkey numbers must be consecutive.</dd>
	 *
	 * <dt><tt>Threshold</tt></dt>
	 * <dd>This property specifies log level threshold. Events with
	 * lower log level than the threshold will not be logged by
	 * appender.</dd>
	 *
	 * <dt><tt>UseLockFile</tt></dt>
	 * <dd>Set this property to <tt>true</tt> if you want your output
	 * through this appender to be synchronized between multiple
	 * processes. When this property is set to true then logging
	 * uses OS specific facilities (e.g., <code>lockf()</code>) to
	 * provide inter-process locking. With the exception of
	 * FileAppender and its derived classes, it is also necessary to
	 * provide path to a lock file using the <tt>LockFile</tt>
	 * property.
	 * \sa FileAppender
	 * </dd>
	 *
	 * <dt><tt>LockFile</tt></dt>
	 * <dd>This property specifies lock file, file used for
	 * inter-process synchronization of log file access. The property
	 * is only used when <tt>UseLockFile</tt> is set to true. Then it
	 * is mandatory.
	 * \sa FileAppender
	 * </dd>
	 *
	 * <dt><tt>AsyncAppend</tt></dt>
	 * <dd>Set this property to <tt>true</tt> if you want all appends using
	 * this appender to be done asynchronously. Default is <tt>false</tt>.</dd>
	 *
	 * </dl>
	 */
	class LOGGING_EXPORT Appender
		: public virtual logging::helpers::SharedObject
	{
	public:
		// Ctor
		Appender();
		Appender(const logging::helpers::Properties & properties);

		// Dtor
		virtual ~Appender();

		/**
		 * This function is for derived appenders to call from their
		 * destructors. All classes derived from `Appender` class
		 * _must_ call this function from their destructors. It
		 * ensures that appenders will get properly closed during
		 * shutdown by call to `close()` function before they are
		 * destroyed.
		 */
		void destructorImpl();

		// Methods
		  /**
		   * Release any resources allocated within the appender such as file
		   * handles, network connections, etc.
		   *
		   * It is a programming error to append to a closed appender.
		   */
		virtual void close() = 0;

		/**
		 * Check if this appender is in closed state.
		 */
		bool isClosed() const;

		/**
		 * This method performs threshold checks and invokes filters before
		 * delegating actual logging to the subclasses specific {@link
		 * #append} method.
		 */
		void syncDoAppend(const logging::spi::InternalLoggingEvent& event);

		/**
		 * This method performs book keeping related to asynchronous logging
		 * and executes `syncDoAppend()` to do the actual logging.
		 */

		void asyncDoAppend(const logging::spi::InternalLoggingEvent& event);

		/**
		 * This function checks `async` flag. It either executes
		 * `syncDoAppend()` directly or enqueues its execution to thread pool
		 * thread.
		 */
		void doAppend(const logging::spi::InternalLoggingEvent& event);

		/**
		 * Get the name of this appender. The name uniquely identifies the
		 * appender.
		 */
		virtual logging::tstring getName();

		/**
		 * Set the name of this appender. The name is used by other
		 * components to identify this appender.
		 */
		virtual void setName(const logging::tstring& name);

		/**
		 * Set the {@link ErrorHandler} for this Appender.
		 */
		virtual void setErrorHandler(std::unique_ptr<ErrorHandler> eh);

		/**
		 * Return the currently set {@link ErrorHandler} for this
		 * Appender.
		 */
		virtual ErrorHandler* getErrorHandler();



		virtual void setLayout();


		/**
		 * Set the layout for this appender. Note that some appenders have
		 * their own (fixed) layouts or do not use one. For example, the
		 * SocketAppender ignores the layout set here.
		 */
		virtual void setLayout(std::unique_ptr<Layout> layout);


		/**
		 * Returns the layout of this appender. The value may be NULL.
		 *
		 * This class owns the returned pointer.
		 */
		virtual Layout* getLayout();

		/**
		 * Set the filter chain on this Appender.
		 */
		void setFilter(logging::spi::FilterPtr f);

		/**
		 * Get the filter chain on this Appender.
		 */
		logging::spi::FilterPtr getFilter() const;

		/**
		 * Add filter at the end of the filters chain.
		 */
		void addFilter(logging::spi::FilterPtr f);

		/**
		 * Add filter at the end of the filters chain.
		 */
		void addFilter(std::function<
			spi::FilterResult(const logging::spi::InternalLoggingEvent &)>);

		/**
		 * Returns this appenders threshold LogLevel. See the {@link
		 * #setThreshold} method for the meaning of this option.
		 */
		LogLevel getThreshold() const { return threshold; }

		/**
		 * Set the threshold LogLevel. All log events with lower LogLevel
		 * than the threshold LogLevel are ignored by the appender.
		 *
		 * In configuration files this option is specified by setting the
		 * value of the <b>Threshold</b> option to a LogLevel
		 * string, such as "DEBUG", "INFO" and so on.
		 */
		void setThreshold(LogLevel th) { threshold = th; }

		/**
		 * Check whether the message LogLevel is below the appender's
		 * threshold. If there is no threshold set, then the return value is
		 * always <code>true</code>.
		 */
		bool isAsSevereAsThreshold(LogLevel ll) const {
			return ((ll != NOT_SET_LOG_LEVEL) && (ll >= threshold));
		}

		/**
		 * This method waits for all events that are being asynchronously
		 * logged to finish.
		 */
		void waitToFinishAsyncLogging();

	protected:
		// Methods
		  /**
		   * Subclasses of <code>Appender</code> should implement this
		   * method to perform actual logging.
		   * @see doAppend method.
		   */
		virtual void append(const logging::spi::InternalLoggingEvent& event) = 0;

		tstring & formatEvent(const logging::spi::InternalLoggingEvent& event) const;

		// Data
		  /** The layout variable does not need to be set if the appender
		   *  implementation has its own layout. */
		std::unique_ptr<Layout> layout;

		/** Appenders are named. */
		logging::tstring name;

		/** There is no LogLevel threshold filtering by default.  */
		LogLevel threshold;

		/** The first filter in the filter chain. Set to <code>null</code>
		 *  initially. */
		logging::spi::FilterPtr filter;

		/** It is assumed and enforced that errorHandler is never null. */
		std::unique_ptr<ErrorHandler> errorHandler;

		//! Optional system wide synchronization lock.
		std::unique_ptr<helpers::LockFile> lockFile;

		//! Use lock file for inter-process synchronization of access
		//! to log file.
		bool useLockFile;

		//! Asynchronous append.
		bool async;
#if ! defined (LOGGING_SINGLE_THREADED)
		std::atomic<std::size_t> in_flight;
		std::mutex in_flight_mutex;
		std::condition_variable in_flight_condition;
#endif

		/** Is this appender closed? */
		bool closed;

	private:
#if ! defined (LOGGING_SINGLE_THREADED)
		void subtract_in_flight();
#endif
	};

	/** This is a pointer to an Appender. */
	typedef helpers::SharedObjectPtr<Appender> SharedAppenderPtr;

} // end namespace logging

#endif // LOGGING_APPENDER_HEADER_
