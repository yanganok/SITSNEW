#ifndef LOGGING_HIERARCHY_LOCKER_HEADER_
#define LOGGING_HIERARCHY_LOCKER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/tstring.h>
#include <logging/appender.h>
#include <logging/logger.h>


namespace logging
{

	class Hierarchy;


	/**
	 * This is used to lock a Hierarchy.  The dtor unlocks the Hierarchy.
	 */
	class LOGGING_EXPORT HierarchyLocker {
	public:
		// ctor & dtor
		HierarchyLocker(Hierarchy& h);
		~HierarchyLocker() LOGGING_NOEXCEPT_FALSE;

		/**
		 * Calls the <code>resetConfiguration()</code> method on the locked Hierarchy.
		 */
		void resetConfiguration();

		/**
		 * Calls the <code>getInstance()</code> method on the locked Hierarchy.
		 */
		Logger getInstance(const logging::tstring& name);

		/**
		 * Calls the <code>getInstance()</code> method on the locked Hierarchy.
		 */
		Logger getInstance(const logging::tstring& name, spi::LoggerFactory& factory);

		void addAppender(Logger &logger, logging::SharedAppenderPtr& appender);

	private:
		// Data
		Hierarchy& h;
		logging::thread::MutexGuard hierarchyLocker;
		LoggerList loggerList;
	};

} // end namespace logging

#endif // LOGGING_HIERARCHY_LOCKER_HEADER_
