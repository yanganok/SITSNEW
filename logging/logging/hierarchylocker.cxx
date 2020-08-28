#include <logging/hierarchylocker.h>
#include <logging/hierarchy.h>
#include <logging/helpers/loglog.h>
#include <logging/spi/loggerimpl.h>
#include <logging/thread/syncprims-pub-impl.h>


namespace logging
{


	//////////////////////////////////////////////////////////////////////////////
	// HierarchyLocker ctor and dtor
	//////////////////////////////////////////////////////////////////////////////

	HierarchyLocker::HierarchyLocker(Hierarchy& _h)
		: h(_h),
		hierarchyLocker(h.hashtable_mutex),
		loggerList()
	{
		// Get a copy of all of the Hierarchy's Loggers (except the Root Logger)
		h.initializeLoggerList(loggerList);

		// Lock all of the Hierarchy's Loggers' mutexs
		LoggerList::iterator it;
		try
		{
			for (it = loggerList.begin(); it != loggerList.end(); ++it)
				it->value->appender_list_mutex.lock();
		}
		catch (...)
		{
			helpers::getLogLog().error(
				LOGGING_TEXT("HierarchyLocker::ctor()")
				LOGGING_TEXT("- An error occurred while locking"));
			LoggerList::iterator range_end = it;
			for (it = loggerList.begin(); it != range_end; ++it)
				it->value->appender_list_mutex.unlock();
			throw;
		}
	}


	HierarchyLocker::~HierarchyLocker() LOGGING_NOEXCEPT_FALSE
	{
		try {
			for (auto & logger : loggerList)
				logger.value->appender_list_mutex.unlock();
		}
		catch (...) {
			helpers::getLogLog().error(LOGGING_TEXT("HierarchyLocker::dtor()- An error occurred while unlocking"));
			throw;
		}
	}

	void
		HierarchyLocker::resetConfiguration()
	{
		Logger root = h.getRoot();
		h.disable(Hierarchy::DISABLE_OFF);

		// begin by closing nested appenders
		// then, remove all appenders
		root.setLogLevel(DEBUG_LOG_LEVEL);
		root.closeNestedAppenders();
		root.removeAllAppenders();

		// repeat
		for (auto & logger : loggerList)
		{
			logger.closeNestedAppenders();
			logger.removeAllAppenders();

			logger.setLogLevel(NOT_SET_LOG_LEVEL);
			logger.setAdditivity(true);
		}
	}


	Logger
		HierarchyLocker::getInstance(const tstring& name)
	{
		return h.getInstanceImpl(name, *h.getLoggerFactory());
	}


	Logger
		HierarchyLocker::getInstance(const tstring& name, spi::LoggerFactory& factory)
	{
		return h.getInstanceImpl(name, factory);
	}


	void
		HierarchyLocker::addAppender(Logger& logger, SharedAppenderPtr& appender)
	{
		for (auto & l : loggerList)
		{
			if (l.value == logger.value)
			{
				logger.value->appender_list_mutex.unlock();
				logger.addAppender(appender);
				logger.value->appender_list_mutex.lock();
				return;
			}
		}

		// I don't have this Logger locked
		logger.addAppender(appender);
	}


} // namespace logging
