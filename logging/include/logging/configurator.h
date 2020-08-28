#ifndef LOGGING_CONFIGURATOR_HEADER_
#define LOGGING_CONFIGURATOR_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/appender.h>
#include <logging/logger.h>
#include <logging/helpers/pointer.h>
#include <logging/helpers/property.h>

#include <map>


namespace logging
{
	class Hierarchy;


	/**
	 * Provides configuration from an external file.  See configure() for
	 * the expected format.
	 *
	 * <em>All option values admit variable substitution.</em> For
	 * example, if <code>userhome</code> environment property is set to
	 * <code>/home/xyz</code> and the File option is set to the string
	 * <code>${userhome}/test.log</code>, then File option will be
	 * interpreted as the string <code>/home/xyz/test.log</code>.
	 *
	 * The syntax of variable substitution is similar to that of UNIX
	 * shells. The string between an opening <b>&quot;${&quot;</b> and
	 * closing <b>&quot;}&quot;</b> is interpreted as a key. Its value is
	 * searched in the environment properties.  The corresponding value replaces
	 * the ${variableName} sequence.
	 *
	 * Configuration files also recognize <code>include
	 * <i>file.properties</i></code> directive that allow composing
	 * configuration from multiple files. There is no cyclic includes
	 * detection mechanism to stop unbound recursion.
	 */
	class LOGGING_EXPORT PropertyConfigurator
	{
	public:
		enum PCFlags
		{
			fRecursiveExpansion = (1 << 0)
			, fShadowEnvironment = (1 << 1)
			, fAllowEmptyVars = (1 << 2)

			// These encoding related options occupy 2 bits of the flags
			// and are mutually exclusive. These flags are synchronized with
			// PFlags in Properties.

			, fEncodingShift = 3
			, fEncodingMask = 0x3
			, fUnspecEncoding = (0 << fEncodingShift)
#if defined (LOGGING_HAVE_CODECVT_UTF8_FACET) && defined (UNICODE)
			, fUTF8 = (1 << fEncodingShift)
#endif
#if (defined (LOGGING_HAVE_CODECVT_UTF16_FACET) || defined (_WIN32)) \
    && defined (UNICODE)
			, fUTF16 = (2 << fEncodingShift)
#endif
#if defined (LOGGING_HAVE_CODECVT_UTF32_FACET) && defined (UNICODE)
			, fUTF32 = (3 << fEncodingShift)
#endif
		};

		// ctor and dtor
		PropertyConfigurator(const logging::tstring& propertyFile,
			Hierarchy& h = Logger::getDefaultHierarchy(), unsigned flags = 0);
		PropertyConfigurator(const logging::helpers::Properties& props,
			Hierarchy& h = Logger::getDefaultHierarchy(), unsigned flags = 0);
		PropertyConfigurator(logging::tistream& propertyStream,
			Hierarchy& h = Logger::getDefaultHierarchy(), unsigned flags = 0);
		virtual ~PropertyConfigurator();

		/**
		 * This method eliminates the need to create a temporary
		 * <code>PropertyConfigurator</code> to configure logging.
		 * It is equivalent to the following:<br>
		 * <code>
		 * PropertyConfigurator config("filename");
		 * config.configure();
		 * </code>
		 */
		static void doConfigure(const logging::tstring& configFilename,
			Hierarchy& h = Logger::getDefaultHierarchy(), unsigned flags = 0);

		/**
		 * Read configuration from a file. <b>The existing configuration is
		 * not cleared nor reset.</b> If you require a different behavior,
		 * then call {@link Hierarchy::resetConfiguration
		 * resetConfiguration} method before calling
		 * <code>doConfigure</code>.
		 *
		 * The configuration file consists of statements in the format
		 * <code>key=value</code>. The syntax of different configuration
		 * elements are discussed below.
		 *
		 * <h3>Appender configuration</h3>
		 *
		 * Appender configuration syntax is:
		 * <pre>
		 * # For appender named <i>appenderName</i>, set its class.
		 * # Note: The appender name can contain dots.
		 * logging.appender.appenderName=fully.qualified.name.of.appender.class
		 *
		 * # Set appender specific options.
		 * logging.appender.appenderName.option1=value1
		 * ...
		 * logging.appender.appenderName.optionN=valueN
		 * </pre>
		 *
		 * For each named appender you can configure its {@link Layout}. The
		 * syntax for configuring an appender's layout is:
		 * <pre>
		 * logging.appender.appenderName.layout=fully.qualified.name.of.layout.class
		 * logging.appender.appenderName.layout.option1=value1
		 * ....
		 * logging.appender.appenderName.layout.optionN=valueN
		 * </pre>
		 *
		 * <h3>Configuring loggers</h3>
		 *
		 * The syntax for configuring the root logger is:
		 * <pre>
		 * logging.rootLogger=[LogLevel], appenderName, appenderName, ...
		 * </pre>
		 *
		 * This syntax means that an optional <em>LogLevel value</em> can
		 * be supplied followed by appender names separated by commas.
		 *
		 * The LogLevel value can consist of the string values FATAL,
		 * ERROR, WARN, INFO, DEBUG or a <em>custom LogLevel</em> value.
		 *
		 * If a LogLevel value is specified, then the root LogLevel is set
		 * to the corresponding LogLevel.  If no LogLevel value is specified,
		 * then the root LogLevel remains untouched.
		 *
		 * The root logger can be assigned multiple appenders.
		 *
		 * Each <i>appenderName</i> (separated by commas) will be added to
		 * the root logger. The named appender is defined using the
		 * appender syntax defined above.
		 *
		 * For non-root loggers the syntax is almost the same:
		 * <pre>
		 * logging.logger.logger_name=[LogLevel|INHERITED], appenderName, appenderName, ...
		 * </pre>
		 *
		 * The meaning of the optional LogLevel value is discussed above
		 * in relation to the root logger. In addition however, the value
		 * INHERITED can be specified meaning that the named logger should
		 * inherit its LogLevel from the logger hierarchy.
		 *
		 * By default loggers inherit their LogLevel from the
		 * hierarchy.  However, if you set the LogLevel of a logger and
		 * later decide that that logger should inherit its LogLevel, then
		 * you should specify INHERITED as the value for the LogLevel value.
		 *
		 * Similar to the root logger syntax, each <i>appenderName</i>
		 * (separated by commas) will be attached to the named logger.
		 *
		 * See the <a href="../../../../manual.html#additivity">appender
		 * additivity rule</a> in the user manual for the meaning of the
		 * <code>additivity</code> flag.
		 *
		 * The user can override any of the {@link
		 * Hierarchy#disable} family of methods by setting the a key
		 * "logging.disableOverride" to <code>true</code> or any value other
		 * than false. As in <pre>logging.disableOverride=true </pre>
		 *
		 * <h3>Global configuration</h3>
		 *
		 * Property <pre>logging.threadPoolSize</pre> can be used to adjust
		 * size of logging' internal thread pool.
		 *
		 * <h3>Example</h3>
		 *
		 * An example configuration is given below.
		 *
		 * <pre>
		 *
		 * # Set options for appender named "A1".
		 * # Appender "A1" will be a SyslogAppender
		 * logging.appender.A1=logging::SyslogAppender
		 *
		 * # The syslog daemon resides on www.abc.net
		 * logging.appender.A1.SyslogHost=www.abc.net
		 *
		 * # A1's layout is a PatternLayout, using the conversion pattern
		 * # <b>%r %-5p %c{2} %M.%L %x - %m\n</b>. Thus, the log output will
		 * # include # the relative time since the start of the application in
		 * # milliseconds, followed by the LogLevel of the log request,
		 * # followed by the two rightmost components of the logger name,
		 * # followed by the callers method name, followed by the line number,
		 * # the nested disgnostic context and finally the message itself.
		 * # Refer to the documentation of {@link PatternLayout} for further information
		 * # on the syntax of the ConversionPattern key.
		 * logging.appender.A1.layout=logging::PatternLayout
		 * logging.appender.A1.layout.ConversionPattern=%-4r %-5p %c{2} %M.%L %x - %m\n
		 *
		 * # Set options for appender named "A2"
		 * # A2 should be a RollingFileAppender, with maximum file size of 10 MB
		 * # using at most one backup file. A2's layout is TTCC, using the
		 * # ISO8061 date format with context printing enabled.
		 * logging.appender.A2=logging::RollingFileAppender
		 * logging.appender.A2.MaxFileSize=10MB
		 * logging.appender.A2.MaxBackupIndex=1
		 * logging.appender.A2.layout=logging::TTCCLayout
		 * logging.appender.A2.layout.ContextPrinting=true
		 * logging.appender.A2.layout.DateFormat=ISO8601
		 *
		 * # Root logger set to DEBUG using the A2 appender defined above.
		 * logging.rootLogger=DEBUG, A2
		 *
		 * # Logger definitions:
		 * # The SECURITY logger inherits is LogLevel from root. However, it's output
		 * # will go to A1 appender defined above. It's additivity is non-cumulative.
		 * logging.logger.SECURITY=INHERIT, A1
		 * logging.additivity.SECURITY=false
		 *
		 * # Only warnings or above will be logged for the logger "SECURITY.access".
		 * # Output will go to A1.
		 * logging.logger.SECURITY.access=WARN
		 *
		 *
		 * # The logger "class.of.the.day" inherits its LogLevel from the
		 * # logger hierarchy.  Output will go to the appender's of the root
		 * # logger, A2 in this case.
		 * logging.logger.class.of.the.day=INHERIT
		 * </pre>
		 *
		 * Refer to the <b>setOption</b> method in each Appender and
		 * Layout for class specific options.
		 *
		 * Use the <code>#</code> character at the beginning of a line
		 * for comments.
		 */
		virtual void configure();

		/**
		 * \return The return value is reference to Properties
		 * container of properties with the <code>"logging."</code>
		 * prefix removed and references to other properties and/or
		 * environment variables expanded.
		 */
		logging::helpers::Properties const & getProperties() const;

		/**
		 * \return The return value is a reference to logging::tstring
		 * containing filename of properties source file. It will be
		 * string "UNAVAILABLE" if the PropertyConfigurator instance has been
		 * constructed using one of the other constructors that do not take
		 * filename as parameter.
		 */
		logging::tstring const & getPropertyFilename() const;

	protected:
		// Methods
		void init();  // called by the ctor
		void reconfigure();
		void replaceEnvironVariables();
		void configureLoggers();
		void configureLogger(logging::Logger logger, const logging::tstring& config);
		void configureAppenders();
		void configureAdditivity();

		virtual Logger getLogger(const logging::tstring& name);
		virtual void addAppender(Logger &logger, logging::SharedAppenderPtr& appender);

		// Types
		typedef std::map<logging::tstring, logging::SharedAppenderPtr> AppenderMap;

		// Data
		Hierarchy& h;
		logging::tstring propertyFilename;
		logging::helpers::Properties properties;
		AppenderMap appenders;
		unsigned flags;

	private:
		// Disable copy
		PropertyConfigurator(const PropertyConfigurator&);
		PropertyConfigurator& operator=(PropertyConfigurator&);
	};



	/**
	 * Use this class to quickly configure the package. For file based
	 * configuration see PropertyConfigurator. BasicConfigurator
	 * automatically attaches ConsoleAppender to
	 * <code>rootLogger</code>, with output going to standard output,
	 * using DEBUG LogLevel value. The additional parameter
	 * logToStdErr may redirect the output to standard error.
	 */
	class LOGGING_EXPORT BasicConfigurator : public PropertyConfigurator {
	public:
		// ctor and dtor
		BasicConfigurator(Hierarchy& h = Logger::getDefaultHierarchy(),
			bool logToStdErr = false);
		virtual ~BasicConfigurator();

		/**
		 * This method eliminates the need to create a temporary
		 * <code>BasicConfigurator</code> object to configure logging.
		 * It is equivalent to the following:<br>
		 * <code><pre>
		 * BasicConfigurator config;
		 * config.configure();
		 * </pre></code>
		 */
		static void doConfigure(Hierarchy& h = Logger::getDefaultHierarchy(),
			bool logToStdErr = false);

		//! Property name for disable override.
		static logging::tstring const DISABLE_OVERRIDE_KEY;

	private:
		// Disable copy
		BasicConfigurator(const BasicConfigurator&);
		BasicConfigurator& operator=(BasicConfigurator&);
	};


#if !defined(LOGGING_SINGLE_THREADED)
	// Forward Declarations
	class ConfigurationWatchDogThread;


	class LOGGING_EXPORT ConfigureAndWatchThread {
	public:
		// ctor and dtor
		ConfigureAndWatchThread(const logging::tstring& propertyFile,
			unsigned int millis = 60 * 1000);
		virtual ~ConfigureAndWatchThread();

	private:
		// Disallow copying of instances of this class
		ConfigureAndWatchThread(const ConfigureAndWatchThread&);
		ConfigureAndWatchThread& operator=(const ConfigureAndWatchThread&);

		// Data
		ConfigurationWatchDogThread * watchDogThread;
	};
#endif

} // end namespace logging

#endif // LOGGING_CONFIGURATOR_HEADER_
