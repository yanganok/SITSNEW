#include <logging/config.hxx>

#if defined (LOGGING_WITH_UNIT_TESTS)
// Include full Windows.h early for Catch.
#  include <logging/config/windowsh-inc-full.h>
#  define CATCH_CONFIG_RUNNER
#  include <logging/catch.hpp>
#endif

#include <logging/logging.h>

#include <logging/initializer.h>
#include <logging/config/windowsh-inc.h>
#include <logging/logger.h>
#include <logging/ndc.h>
#include <logging/mdc.h>
#include <logging/helpers/loglog.h>
#include <logging/internal/customloglevelmanager.h>
#include <logging/internal/internal.h>
#include <logging/thread/impl/tls.h>
#include <logging/thread/syncprims-pub-impl.h>
#include <logging/helpers/loglog.h>
#include <logging/spi/factory.h>
#include <logging/hierarchy.h>
#if ! defined (LOGGING_SINGLE_THREADED)
#include <logging/threadpool.hpp>
#endif
#include <cstdio>
#include <iostream>
#include <stdexcept>




// Tips for Getting Started: 
//   1. create Visual C++ Console App project: demo (Platform: x64)
//
//   2. add reference: logging																			[skipped]
//   3. [Properties] -> [General] -> Output Directory: $(SolutionDir)$(Platform)\$(Configuration)\		[skipped]
//   4. [Properties] -> [General] -> Intermediate Directory: $(Platform)\$(Configuration)\				[skipped]
//   5. [Properties] -> [General] -> Character Set: Use Unicode Character Set							[skipped]
//
//   6. [Properties] -> [C/C++] -> [General] -> Additional Include Directories: ..\..\include
//   7. [Properties] -> [Linker] -> [General] -> Additional Library Directories: $(SolutionDir)$(Platform)\$(Configuration)\
//   8. [Properties] -> [Linker] -> [Input] -> Additional Dependencies: logging.lib
//
//   9. Solution -> [Properties] -> Project Dependencies: logging (if not add reference logging)
//
//      [Build Events] -> [Post-Build Event] -> Command Line: (copy logging.dll and logging.lib to packages folder)
//      set FromDir = $(SolutionDir)$(Platform)\$(Configuration)\
//      set ToDir = $(SolutionDir)packages\
//      if exist %ToDir % (rmdir %ToDir% / S / Q)
//      if not exist %ToDir % (mkdir %ToDir%)
//      if exist %ToDir% (xcopy %FromDir%logging.* %ToDir% /S /E /Y /I /C )




// Forward Declarations
namespace logging
{

#ifdef UNICODE
	LOGGING_EXPORT tostream & tcout = std::wcout;
	LOGGING_EXPORT tostream & tcerr = std::wcerr;

#else
	LOGGING_EXPORT tostream & tcout = std::cout;
	LOGGING_EXPORT tostream & tcerr = std::cerr;

#endif // UNICODE


	struct InitializerImpl
	{
#if ! defined (LOGGING_SINGLE_THREADED)
		std::mutex mtx;

		static std::once_flag flag;
#endif

		unsigned count = 0;

		static InitializerImpl * instance;
	};

#if ! defined (LOGGING_SINGLE_THREADED)
	std::once_flag InitializerImpl::flag;
#endif
	InitializerImpl * InitializerImpl::instance;


	Initializer::Initializer()
	{
#if ! defined (LOGGING_SINGLE_THREADED)
		std::call_once(InitializerImpl::flag,
			[&] {
			InitializerImpl::instance = new InitializerImpl;
		});
#else
		InitializerImpl::instance = new InitializerImpl;
#endif

		LOGGING_THREADED(
			std::unique_lock<std::mutex> guard(
				InitializerImpl::instance->mtx));
		if (InitializerImpl::instance->count == 0)
			initialize();

		++InitializerImpl::instance->count;
	}


	// Forward declaration. Defined in this file.
	void shutdownThreadPool();

	Initializer::~Initializer()
	{
		bool destroy = false;
		{
			LOGGING_THREADED(
				std::unique_lock<std::mutex> guard(
					InitializerImpl::instance->mtx));
			--InitializerImpl::instance->count;
			if (InitializerImpl::instance->count == 0)
			{
				destroy = true;
				deinitialize();
			}
		}
		if (destroy)
		{
			delete InitializerImpl::instance;
			InitializerImpl::instance = nullptr;
		}
	}


	namespace
	{

#if ! defined (LOGGING_SINGLE_THREADED)
		static
			std::unique_ptr<logging::ThreadPool>
			instantiate_thread_pool()
		{
			logging::thread::SignalsBlocker sb;
			return std::unique_ptr<logging::ThreadPool>(new logging::ThreadPool(4));
		}
#endif


		//! Default context.
		struct DefaultContext
		{
			logging::thread::Mutex console_mutex;
			helpers::LogLog loglog;
			LogLevelManager log_level_manager;
			internal::CustomLogLevelManager custom_log_level_manager;
			helpers::Time TTCCLayout_time_base;
			NDC ndc;
			MDC mdc;
			spi::AppenderFactoryRegistry appender_factory_registry;
			spi::LayoutFactoryRegistry layout_factory_registry;
			spi::FilterFactoryRegistry filter_factory_registry;
			spi::LocaleFactoryRegistry locale_factory_registry;
#if ! defined (LOGGING_SINGLE_THREADED)
			std::unique_ptr<logging::ThreadPool> thread_pool{ instantiate_thread_pool() };
#endif
			Hierarchy hierarchy;
		};


		enum DCState
		{
			DC_UNINITIALIZED,
			DC_INITIALIZED,
			DC_DESTROYED
		};


		static DCState default_context_state = DC_UNINITIALIZED;
		static DefaultContext * default_context = nullptr;


		struct destroy_default_context
		{
			~destroy_default_context()
			{
				delete default_context;
				default_context = nullptr;
				default_context_state = DC_DESTROYED;
			}
		} static destroy_default_context_
			LOGGING_INIT_PRIORITY(LOGGING_INIT_PRIORITY_BASE + 1);


		static
			void
			alloc_dc()
		{
			assert(!default_context);
			assert(default_context_state == DC_UNINITIALIZED);

			if (default_context)
				throw std::logic_error(
					"alloc_dc() called with non-NULL default_context.");

			if (default_context_state == DC_INITIALIZED)
				throw std::logic_error("alloc_dc() called in DC_INITIALIZED state.");

			default_context = new DefaultContext;

			if (default_context_state == DC_DESTROYED)
				default_context->loglog.error(
					LOGGING_TEXT("Re-initializing default context after it has")
					LOGGING_TEXT(" already been destroyed.\n")
					LOGGING_TEXT("The memory will be leaked."));

			default_context_state = DC_INITIALIZED;
		}


		static
			DefaultContext *
			get_dc(
#ifdef LOGGING_REQUIRE_EXPLICIT_INITIALIZATION
				bool alloc = false
#else
				bool alloc = true
#endif
			)
		{
			if (LOGGING_UNLIKELY(!default_context))
			{
				if (alloc)
				{
					alloc_dc();
				}
				else
				{
#ifdef LOGGING_REQUIRE_EXPLICIT_INITIALIZATION
					throw std::logic_error("logging is not initialized"
						" and implicit initialization is turned off");
#endif
				}
			}
			return default_context;
		}


	} // namespace


	namespace internal {

		CustomLogLevelManager & getCustomLogLevelManager()
		{
			return get_dc()->custom_log_level_manager;
		}

	} // namespace internal


	namespace helpers
	{


		logging::thread::Mutex const &
			getConsoleOutputMutex()
		{
			return get_dc()->console_mutex;
		}


		LogLog &
			getLogLog()
		{
			return get_dc()->loglog;
		}


	} // namespace helpers


	helpers::Time const &
		getTTCCLayoutTimeBase()
	{
		return get_dc()->TTCCLayout_time_base;
	}


	LogLevelManager &
		getLogLevelManager()
	{
		return get_dc()->log_level_manager;
	}


	Hierarchy &
		getDefaultHierarchy()
	{
		return get_dc()->hierarchy;
	}


	NDC &
		getNDC()
	{
		return get_dc()->ndc;
	}


	MDC &
		getMDC()
	{
		return get_dc()->mdc;
	}


#if ! defined (LOGGING_SINGLE_THREADED)
	void
		enqueueAsyncDoAppend(SharedAppenderPtr const & appender,
			spi::InternalLoggingEvent const & event)
	{
		get_dc()->thread_pool->enqueue(
			[=]()
		{
			appender->asyncDoAppend(event);
		});
	}

#endif

	void
		shutdownThreadPool()
	{
#if ! defined (LOGGING_SINGLE_THREADED)
		DefaultContext * const dc = get_dc(false);
		if (dc && dc->thread_pool)
		{
			dc->thread_pool.reset();
		}
#endif
	}


	void
		waitUntilEmptyThreadPoolQueue()
	{
#if ! defined (LOGGING_SINGLE_THREADED)
		DefaultContext * const dc = get_dc(false);
		if (dc && dc->thread_pool)
		{
			dc->thread_pool->wait_until_empty();
			dc->thread_pool->wait_until_nothing_in_flight();
		}
#endif
	}


	namespace spi
	{


		AppenderFactoryRegistry &
			getAppenderFactoryRegistry()
		{
			return get_dc()->appender_factory_registry;
		}


		LayoutFactoryRegistry &
			getLayoutFactoryRegistry()
		{
			return get_dc()->layout_factory_registry;
		}


		FilterFactoryRegistry &
			getFilterFactoryRegistry()
		{
			return get_dc()->filter_factory_registry;
		}


		LocaleFactoryRegistry &
			getLocaleFactoryRegistry()
		{
			return get_dc()->locale_factory_registry;
		}


	} // namespace spi


	namespace internal
	{


		gft_scratch_pad::gft_scratch_pad()
			: uc_q_str_valid(false)
			, q_str_valid(false)
			, s_str_valid(false)
		{ }


		gft_scratch_pad::~gft_scratch_pad()
		{ }


		appender_sratch_pad::appender_sratch_pad()
		{ }


		appender_sratch_pad::~appender_sratch_pad()
		{ }


		per_thread_data::per_thread_data()
			: fnull(nullptr)
		{ }


		per_thread_data::~per_thread_data()
		{
			if (fnull)
				std::fclose(fnull);
		}


		logging::thread::impl::tls_key_type tls_storage_key;


#if ! defined (LOGGING_SINGLE_THREADED) \
    && defined (LOGGING_THREAD_LOCAL_VAR)

		LOGGING_THREAD_LOCAL_VAR per_thread_data * ptd = nullptr;


		per_thread_data *
			alloc_ptd()
		{
			auto * tmp = new per_thread_data;
			set_ptd(tmp);
			// This is a special hack. We set the keys' value to non-NULL to
			// get the ptd_cleanup_func to execute when this thread ends. The
			// cast is safe; the associated value will never be used if read
			// again using the key.
			thread::impl::tls_set_value(tls_storage_key,
				reinterpret_cast<void *>(1));

			return tmp;
		}

#  else

		per_thread_data *
			alloc_ptd()
		{
			auto * tmp = new per_thread_data;
			set_ptd(tmp);
			return tmp;
		}

#  endif

	} // namespace internal


	void initializeFactoryRegistry();


	//! Thread local storage clean up function for POSIX threads.
#if defined (LOGGING_USE_WIN32_THREADS)
	static
		void NTAPI
#else
	static
		void
#endif
		ptd_cleanup_func(void * arg)
	{
		internal::per_thread_data * const arg_ptd
			= static_cast<internal::per_thread_data *>(arg);
		internal::per_thread_data * const ptd = internal::get_ptd(false);
		(void)ptd;

		// Either it is a dummy value or it should be the per thread data
		// pointer we get from internal::get_ptd().
		assert(arg == reinterpret_cast<void *>(1)
			|| arg_ptd == ptd
			|| (!ptd && arg_ptd));

		if (arg == reinterpret_cast<void *>(1))
			// Setting the value through the key here is necessary in case
			// we are using TLS using __thread or __declspec(thread) or
			// similar constructs with POSIX threads.  Otherwise POSIX
			// calls this cleanup routine more than once if the value
			// stays non-NULL after it returns.
			thread::impl::tls_set_value(internal::tls_storage_key, nullptr);
		else if (arg)
		{
			// Instead of using internal::get_ptd(false) here we are using
			// the value passed to this function directly.  This is
			// necessary because of the following (from SUSv4):
			//
			// A call to pthread_getspecific() for the thread-specific
			// data key being destroyed shall return the value NULL,
			// unless the value is changed (after the destructor starts)
			// by a call to pthread_setspecific().
			delete arg_ptd;
			thread::impl::tls_set_value(internal::tls_storage_key, nullptr);
		}
		else
		{
			// In this case we fall through to threadCleanup() and it does
			// all the necessary work itself.
			;
		}

		threadCleanup();
	}


	static void threadSetup()
	{
		internal::get_ptd(true);
	}


	void initializeLogging()
	{
		static bool initialized = false;
		if (initialized)
			return;

		internal::tls_storage_key = thread::impl::tls_init(ptd_cleanup_func);
		threadSetup();

		DefaultContext * dc = get_dc(true);
		dc->TTCCLayout_time_base = helpers::now();
		Logger::getRoot();
		initializeFactoryRegistry();

		initialized = true;
	}


	void initialize()
	{
		initializeLogging();
	}


	void deinitialize()
	{
		shutdownThreadPool();
		Logger::shutdown();
	}


	void threadCleanup()
	{
		// Here we check that we can get CRT's heap handle because if we do not
		// then the following `delete` will fail with access violation in
		// `RtlFreeHeap()`.
		//
		// How is it possible that the CRT heap handle is NULL?
		//
		// This function can be called from TLS initializer/terminator by loader
		// when logging is compiled and linked to as a static library. In case of
		// other threads temination, it should do its job and free per-thread
		// data. However, when the whole process is being terminated, it is called
		// after the CRT has been uninitialized and the CRT heap is not available
		// any more. In such case, instead of crashing, we just give up and leak
		// the memory for the short while before the process terminates anyway.
		//
		// It is possible to work around this situation in user application by
		// calling `threadCleanup()` manually before `main()` exits.
#if defined (_WIN32)
		if (_get_heap_handle() != 0)
		{
#endif
			// Do thread-specific cleanup.
			internal::per_thread_data * ptd = internal::get_ptd(false);
			delete ptd;
#if defined (_WIN32)
		}
		else
		{
			OutputDebugString(
				LOGGING_TEXT("logging: ")
				LOGGING_TEXT("CRT heap is already gone in threadCleanup()\n"));
		}
#endif
		internal::set_ptd(nullptr);
	}


	void
		setThreadPoolSize(std::size_t LOGGING_THREADED(pool_size))
	{
#if ! defined (LOGGING_SINGLE_THREADED)
		get_dc()->thread_pool->set_pool_size(pool_size);
#endif
	}


	static
		void
		freeTLSSlot()
	{
		if (internal::tls_storage_key != thread::impl::tls_key_type())
		{
			thread::impl::tls_cleanup(internal::tls_storage_key);
			internal::tls_storage_key = thread::impl::tls_key_type();
		}
	}


#if defined (_WIN32)
	static
		VOID CALLBACK
		initializeLoggingApcProc(ULONG_PTR /*dwParam*/)
	{
		initializeLogging();
		threadSetup();
	}


	static
		void
		queueLoggingInitializationThroughAPC()
	{
#if defined (LOGGING_BUILD_DLL)
		if (!QueueUserAPC(initializeLoggingApcProc, GetCurrentThread(),
			0))
			throw std::runtime_error("QueueUserAPC() has failed");
#endif
	}


	static
		void NTAPI
		thread_callback(LPVOID /*hinstDLL*/, DWORD fdwReason, LPVOID /*lpReserved*/)
	{
		// Perform actions based on the reason for calling.
		switch (fdwReason)
		{
		case DLL_PROCESS_ATTACH:
		{
#if !defined(LOGGING_REQUIRE_EXPLICIT_INITIALIZATION)
			// We cannot initialize logging directly here. This is because
			// DllMain() is called under loader lock. When we are using C++11
			// threads and synchronization primitives then there is a deadlock
			// somewhere in internals of std::mutex::lock().
			queueLoggingInitializationThroughAPC();
#endif
			break;
		}

		case DLL_THREAD_ATTACH:
		{
			// We could call threadSetup() here but that imposes overhead
			// on threads that do not use logging. Thread local data will
			// be initialized lazily instead.
			break;
		}

		case DLL_THREAD_DETACH:
		{
			// Do thread-specific cleanup.
			logging::threadCleanup();

			break;
		}

		case DLL_PROCESS_DETACH:
		{
			// Perform any necessary cleanup.

			// Do thread-specific cleanup.
			logging::threadCleanup();
			logging::freeTLSSlot();

			break;
		}

		} // switch
	}


	static
		void NTAPI
		thread_callback_initializer(LPVOID hinstDLL, DWORD fdwReason, LPVOID lpReserved)
	{
		if (fdwReason == DLL_PROCESS_ATTACH
			|| fdwReason == DLL_THREAD_ATTACH)
			thread_callback(hinstDLL, fdwReason, lpReserved);
	}

	static
		void NTAPI
		thread_callback_terminator(LPVOID hinstDLL, DWORD fdwReason, LPVOID lpReserved)
	{
		if (fdwReason == DLL_THREAD_DETACH
			|| fdwReason == DLL_PROCESS_DETACH)
			thread_callback(hinstDLL, fdwReason, lpReserved);
	}

#endif




#if defined (LOGGING_WITH_UNIT_TESTS)

	LOGGING_EXPORT int unit_tests_main(int argc, char* argv[]);

	int
		unit_tests_main(int argc, char * argv[])
	{
		return Catch::Session().run(argc, argv);
	}

#endif // defined (LOGGING_WITH_UNIT_TESTS)

	LOGGING_EXPORT Logger create(const logging::tstring& filename,
		long maxFileSize,				// Size = 10 MB
		int maxBackupIndex)				// Backup = 10		
	{
		SharedAppenderPtr consoleAppender(new  ConsoleAppender());
		consoleAppender->setName(LOGGING_TEXT("ConsoleAppender"));
		consoleAppender->setLayout();

		SharedFileAppenderPtr rollingFileAppender(new RollingFileAppender(filename, maxFileSize, maxBackupIndex, true, true));
		rollingFileAppender->setName(LOGGING_TEXT("RollingFileAppender"));
		rollingFileAppender->setLayout();

		auto logger = Logger::getInstance(filename);
		logger.setLogLevel(ALL_LOG_LEVEL);

		logger.addAppender(SharedAppenderPtr(consoleAppender.get()));
		logger.addAppender(SharedAppenderPtr(rollingFileAppender.get()));

		return logger;
	}

} // namespace logging


#if defined (_WIN32)
#if defined (LOGGING_BUILD_DLL) && defined (_DLL)
extern "C"
BOOL
WINAPI
DllMain(LOGGING_DLLMAIN_HINSTANCE hinstDLL, DWORD fdwReason,
	LPVOID lpReserved)
{
	logging::thread_callback(hinstDLL, fdwReason, lpReserved);

	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

#elif defined (_MSC_VER) && _MSC_VER >= 1400 && defined (_DLL)
extern "C"
{

	// This magic has been pieced together from several sources:
	// - <http://www.nynaeve.net/?p=183>
	// - <http://lists.llvm.org/pipermail/cfe-dev/2011-November/018818.html>
	// - `internal_shared.h` in CRT source in Visual Studio 2015

#pragma data_seg (push, old_seg)
#ifdef _WIN64
#pragma const_seg (".CRT$XLY")
	extern const
#else
#pragma data_seg (".CRT$XLY")
#endif
	PIMAGE_TLS_CALLBACK LOGGING_p_thread_callback_initializer = logging::thread_callback_initializer;
#pragma data_seg (pop, old_seg)

#pragma data_seg (push, old_seg)
#ifdef _WIN64
#pragma const_seg (".CRT$XLAA")
	extern const
#else
#pragma data_seg (".CRT$XLAA")
#endif
	PIMAGE_TLS_CALLBACK LOGGING_p_thread_callback_terminator = logging::thread_callback_terminator;
#pragma data_seg (pop, old_seg)

#ifdef _WIN64
#pragma comment (linker, "/INCLUDE:_tls_used")
#if ! defined (LOGGING_REQUIRE_EXPLICIT_INITIALIZATION)
#pragma comment (linker, "/INCLUDE:LOGGING_p_thread_callback_initializer")
#endif
#pragma comment (linker, "/INCLUDE:LOGGING_p_thread_callback_terminator")
#else
#pragma comment (linker, "/INCLUDE:__tls_used")
#if ! defined (LOGGING_REQUIRE_EXPLICIT_INITIALIZATION)
#pragma comment (linker, "/INCLUDE:_LOGGING_p_thread_callback_initializer")
#endif
#pragma comment (linker, "/INCLUDE:_LOGGING_p_thread_callback_terminator")
#endif

} // extern "C"

#endif

namespace {

	struct _static_LOGGING_initializer
	{
#if ! defined (LOGGING_REQUIRE_EXPLICIT_INITIALIZATION)
		_static_LOGGING_initializer()
		{
			// It is not possible to reliably call initializeLogging() here
			// when we are using Visual Studio and C++11 threads
			// and synchronization primitives. It would result into a deadlock
			// on loader lock.
#if ! defined (_MSC_VER)
			logging::initializeLogging();
#endif
		}
#endif

		~_static_LOGGING_initializer()
		{
			// Last thread cleanup.
			logging::threadCleanup();
			logging::freeTLSSlot();
		}
	} static initializer;

} // namespace


#else // defined (WIN32)
namespace {

#if ! defined (LOGGING_REQUIRE_EXPLICIT_INITIALIZATION)
	static void
		_LOGGING_initializer_func()
		LOGGING_CONSTRUCTOR_FUNC(LOGGING_INIT_PRIORITY_BASE);
	static void
		_LOGGING_initializer_func()
	{
		logging::initializeLogging();
	}
#endif

	struct _static_LOGGING_initializer
	{
#if ! defined (LOGGING_REQUIRE_EXPLICIT_INITIALIZATION)
		_static_LOGGING_initializer()
		{
			logging::initializeLogging();
		}
#endif

		~_static_LOGGING_initializer()
		{
			// Last thread cleanup.
			logging::threadCleanup();
			logging::freeTLSSlot();
		}
	} static initializer
		LOGGING_INIT_PRIORITY(LOGGING_INIT_PRIORITY_BASE);

} // namespace

#endif
