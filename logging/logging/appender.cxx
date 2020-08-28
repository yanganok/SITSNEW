#include <logging/appender.h>
#include <logging/layout.h>
#include <logging/helpers/loglog.h>
#include <logging/helpers/pointer.h>
#include <logging/helpers/stringhelper.h>
#include <logging/helpers/property.h>
#include <logging/spi/factory.h>
#include <logging/spi/loggingevent.h>
#include <logging/internal/internal.h>
#include <logging/thread/syncprims-pub-impl.h>
#include <stdexcept>


namespace logging
{


	///////////////////////////////////////////////////////////////////////////////
	// logging::ErrorHandler dtor
	///////////////////////////////////////////////////////////////////////////////

	ErrorHandler::ErrorHandler()
	{ }


	ErrorHandler::~ErrorHandler()
	{ }



	///////////////////////////////////////////////////////////////////////////////
	// logging::OnlyOnceErrorHandler
	///////////////////////////////////////////////////////////////////////////////

	OnlyOnceErrorHandler::OnlyOnceErrorHandler()
		: firstTime(true)
	{ }


	OnlyOnceErrorHandler::~OnlyOnceErrorHandler()
	{ }


	void
		OnlyOnceErrorHandler::error(const logging::tstring& err)
	{
		if (firstTime) {
			helpers::getLogLog().error(err);
			firstTime = false;
		}
	}



	void
		OnlyOnceErrorHandler::reset()
	{
		firstTime = true;
	}



	///////////////////////////////////////////////////////////////////////////////
	// logging::Appender ctors
	///////////////////////////////////////////////////////////////////////////////

	Appender::Appender()
		: layout(new SimpleLayout),
		name(internal::empty_str),
		threshold(NOT_SET_LOG_LEVEL),
		errorHandler(new OnlyOnceErrorHandler),
		useLockFile(false),
		async(false),
#if ! defined (LOGGING_SINGLE_THREADED)
		in_flight(0),
#endif
		closed(false)
	{
	}



	Appender::Appender(const logging::helpers::Properties & properties)
		: layout(new SimpleLayout)
		, name()
		, threshold(NOT_SET_LOG_LEVEL)
		, errorHandler(new OnlyOnceErrorHandler)
		, useLockFile(false)
		, async(false)
#if ! defined (LOGGING_SINGLE_THREADED)
		, in_flight(0)
#endif
		, closed(false)
	{
		if (properties.exists(LOGGING_TEXT("layout")))
		{
			logging::tstring const & factoryName
				= properties.getProperty(LOGGING_TEXT("layout"));
			spi::LayoutFactory* factory
				= spi::getLayoutFactoryRegistry().get(factoryName);
			if (factory == nullptr) {
				helpers::getLogLog().error(
					LOGGING_TEXT("Cannot find LayoutFactory: \"")
					+ factoryName
					+ LOGGING_TEXT("\""), true);
			}

			helpers::Properties layoutProperties =
				properties.getPropertySubset(LOGGING_TEXT("layout."));
			try {
				std::unique_ptr<Layout> newLayout(factory->createObject(layoutProperties));
				if (newLayout == nullptr) {
					helpers::getLogLog().error(
						LOGGING_TEXT("Failed to create Layout: ")
						+ factoryName, true);
				}
				else {
					layout = std::move(newLayout);
				}
			}
			catch (std::exception const & e) {
				helpers::getLogLog().error(
					LOGGING_TEXT("Error while creating Layout: ")
					+ LOGGING_C_STR_TO_TSTRING(e.what()), true);
			}

		}

		// Support for appender.Threshold in properties configuration file
		if (properties.exists(LOGGING_TEXT("Threshold"))) {
			tstring tmp = properties.getProperty(LOGGING_TEXT("Threshold"));
			tmp = logging::helpers::toUpper(tmp);
			threshold = logging::getLogLevelManager().fromString(tmp);
		}

		// Configure the filters
		helpers::Properties filterProps
			= properties.getPropertySubset(LOGGING_TEXT("filters."));
		unsigned filterCount = 0;
		tstring filterName;
		while (filterProps.exists(
			filterName = helpers::convertIntegerToString(++filterCount)))
		{
			tstring const & factoryName = filterProps.getProperty(filterName);
			spi::FilterFactory* factory
				= spi::getFilterFactoryRegistry().get(factoryName);

			if (!factory)
			{
				helpers::getLogLog().error(
					LOGGING_TEXT("Appender::ctor()- Cannot find FilterFactory: ")
					+ factoryName, true);
			}
			spi::FilterPtr tmpFilter = factory->createObject(
				filterProps.getPropertySubset(filterName + LOGGING_TEXT(".")));
			if (!tmpFilter)
			{
				helpers::getLogLog().error(
					LOGGING_TEXT("Appender::ctor()- Failed to create filter: ")
					+ filterName, true);
			}
			addFilter(std::move(tmpFilter));
		}

		// Deal with file locking settings.
		properties.getBool(useLockFile, LOGGING_TEXT("UseLockFile"));
		if (useLockFile)
		{
			tstring const & lockFileName
				= properties.getProperty(LOGGING_TEXT("LockFile"));
			if (!lockFileName.empty())
			{
				try
				{
					lockFile.reset(new helpers::LockFile(lockFileName));
				}
				catch (std::runtime_error const &)
				{
					return;
				}
			}
			else
			{
				helpers::getLogLog().debug(
					LOGGING_TEXT(
						"UseLockFile is true but LockFile is not specified"));
			}
		}

		// Deal with asynchronous append flag.
		properties.getBool(async, LOGGING_TEXT("AsyncAppend"));
	}


	Appender::~Appender()
	{
		helpers::LogLog & loglog = helpers::getLogLog();

		loglog.debug(LOGGING_TEXT("Destroying appender named [") + name
			+ LOGGING_TEXT("]."));

		if (!closed)
			loglog.error(
				LOGGING_TEXT("Derived Appender did not call destructorImpl()."));
	}



	///////////////////////////////////////////////////////////////////////////////
	// logging::Appender public methods
	///////////////////////////////////////////////////////////////////////////////

	void
		Appender::waitToFinishAsyncLogging()
	{
#if ! defined (LOGGING_SINGLE_THREADED)
		if (async)
		{
			// When async flag is true we might have some logging still in flight
			// on thread pool threads. Wait for them to finish.

			std::unique_lock<std::mutex> lock(in_flight_mutex);
			in_flight_condition.wait(lock,
				[&] { return this->in_flight == 0; });
		}
#endif
	}

	void
		Appender::destructorImpl()
	{
		// An appender might be closed then destroyed. There is no point
		// in closing twice. It can actually be a wrong thing to do, e.g.,
		// files get rolled more than once.
		if (closed)
			return;

		waitToFinishAsyncLogging();

		close();
		closed = true;
	}


	bool Appender::isClosed() const
	{
		return closed;
	}


#if ! defined (LOGGING_SINGLE_THREADED)
	void
		Appender::subtract_in_flight()
	{
		std::size_t const prev = std::atomic_fetch_sub_explicit(&in_flight,
			std::size_t(1), std::memory_order_acq_rel);
		if (prev == 1)
		{
			std::unique_lock<std::mutex> lock(in_flight_mutex);
			in_flight_condition.notify_all();
		}
	}

#endif


	// from global-init.cxx
	void enqueueAsyncDoAppend(SharedAppenderPtr const & appender,
		spi::InternalLoggingEvent const & event);


	void
		Appender::doAppend(const logging::spi::InternalLoggingEvent& event)
	{
#if ! defined (LOGGING_SINGLE_THREADED)
		if (async)
		{
			event.gatherThreadSpecificData();

			std::atomic_fetch_add_explicit(&in_flight, std::size_t(1),
				std::memory_order_relaxed);

			try
			{
				enqueueAsyncDoAppend(SharedAppenderPtr(this), event);
			}
			catch (...)
			{
				subtract_in_flight();
				throw;
			}
		}
		else
#endif
			syncDoAppend(event);
	}


	void
		Appender::asyncDoAppend(const logging::spi::InternalLoggingEvent& event)
	{
#if ! defined (LOGGING_SINGLE_THREADED)
		struct handle_in_flight
		{
			Appender * const app;

			explicit
				handle_in_flight(Appender * app_)
				: app(app_)
			{ }

			~handle_in_flight()
			{
				app->subtract_in_flight();
			}
		};

		handle_in_flight guard(this);
#endif

		syncDoAppend(event);
	}


	void
		Appender::syncDoAppend(const logging::spi::InternalLoggingEvent& event)
	{
		thread::MutexGuard guard(access_mutex);

		if (closed) {
			helpers::getLogLog().error(
				LOGGING_TEXT("Attempted to append to closed appender named [")
				+ name
				+ LOGGING_TEXT("]."));
			return;
		}

		// Check appender's threshold logging level.

		if (!isAsSevereAsThreshold(event.getLogLevel()))
			return;

		// Evaluate filters attached to this appender.

		if (checkFilter(filter.get(), event) == spi::DENY)
			return;

		// Lock system wide lock.

		helpers::LockFileGuard lfguard;
		if (useLockFile && lockFile.get())
		{
			try
			{
				lfguard.attach_and_lock(*lockFile);
			}
			catch (std::runtime_error const &)
			{
				return;
			}
		}

		// Finally append given event.

		append(event);
	}


	tstring &
		Appender::formatEvent(const spi::InternalLoggingEvent& event) const
	{
		internal::appender_sratch_pad & appender_sp = internal::get_appender_sp();
		detail::clear_tostringstream(appender_sp.oss);
		layout->formatAndAppend(appender_sp.oss, event);
		appender_sp.str = appender_sp.oss.str();
		return appender_sp.str;
	}


	logging::tstring
		Appender::getName()
	{
		return name;
	}



	void
		Appender::setName(const logging::tstring& n)
	{
		this->name = n;
	}


	ErrorHandler*
		Appender::getErrorHandler()
	{
		return errorHandler.get();
	}




	void
		Appender::setErrorHandler(std::unique_ptr<ErrorHandler> eh)
	{
		if (!eh.get())
		{
			// We do not throw exception here since the cause is probably a
			// bad config file.
			helpers::getLogLog().warn(
				LOGGING_TEXT("You have tried to set a null error-handler."));
			return;
		}

		thread::MutexGuard guard(access_mutex);

		this->errorHandler = std::move(eh);
	}



	void Appender::setLayout()
	{
		logging::tstring pattern = LOGGING_TEXT("%D{%Y/%m/%d %H:%M:%S,%q} [%-5p] %m [%l]%n");

		auto layout = new PatternLayout(pattern);

		this->setLayout(std::unique_ptr<Layout>(layout));
	}


	void
		Appender::setLayout(std::unique_ptr<Layout> lo)
	{
		thread::MutexGuard guard(access_mutex);

		this->layout = std::move(lo);
	}




	Layout*
		Appender::getLayout()
	{
		thread::MutexGuard guard(access_mutex);

		return layout.get();
	}


	void
		Appender::setFilter(logging::spi::FilterPtr f)
	{
		thread::MutexGuard guard(access_mutex);

		filter = std::move(f);
	}


	logging::spi::FilterPtr
		Appender::getFilter() const
	{
		thread::MutexGuard guard(access_mutex);

		return filter;
	}


	void
		Appender::addFilter(logging::spi::FilterPtr f)
	{
		thread::MutexGuard guard(access_mutex);

		logging::spi::FilterPtr filterChain = getFilter();
		if (filterChain)
			filterChain->appendFilter(std::move(f));
		else
			filterChain = std::move(f);

		setFilter(filterChain);
	}


	void
		Appender::addFilter(std::function<
			spi::FilterResult(const spi::InternalLoggingEvent &)> filterFunction)
	{
		addFilter(
			spi::FilterPtr(new spi::FunctionFilter(std::move(filterFunction))));
	}


} // namespace logging
