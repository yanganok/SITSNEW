#ifndef LOGGING_INTERNAL_CUSTOMLOGLEVELMANAGER_HEADER_
#define LOGGING_INTERNAL_CUSTOMLOGLEVELMANAGER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#if ! defined (INSIDE_LOGGING)
#  error "This header must not be be used outside logging' implementation files."
#endif

#include <map>
#include <logging/thread/syncprims.h>
#include <logging/internal/internal.h>


namespace logging
{

	namespace internal
	{


		/**
		 * Custom log level manager used by C API.
		 */
		class CustomLogLevelManager
		{
		protected:
			logging::thread::Mutex mtx;
			bool pushed_methods;
			std::map<LogLevel, tstring> ll2nm;
			std::map<tstring, LogLevel> nm2ll;

		public:
			CustomLogLevelManager() : pushed_methods(false)
			{ }

			bool add(LogLevel ll, tstring const &nm)
			{
				logging::thread::MutexGuard guard(mtx);

				if (!pushed_methods)
				{
					pushed_methods = true;
					getLogLevelManager().pushToStringMethod(customToStringMethod);
					getLogLevelManager().pushFromStringMethod(customFromStringMethod);
				}

				auto i = ll2nm.lower_bound(ll);
				if ((i != ll2nm.end()) && (i->first == ll) && (i->second != nm))
					return false;

				auto j = nm2ll.lower_bound(nm);
				if ((j != nm2ll.end()) && (j->first == nm) && (j->second != ll))
					return false;

				// there is no else after return
				ll2nm.insert(i, std::make_pair(ll, nm));
				nm2ll.insert(j, std::make_pair(nm, ll));
				return true;
			}

			bool remove(LogLevel ll, tstring const &nm)
			{
				logging::thread::MutexGuard guard(mtx);

				auto i = ll2nm.find(ll);
				auto j = nm2ll.find(nm);
				if ((i != ll2nm.end()) && (j != nm2ll.end()) &&
					(i->first == j->second) && (i->second == j->first)) {
					ll2nm.erase(i);
					nm2ll.erase(j);

					return true;
				}

				// there is no else after return
				return false;
			}

		protected:
			tstring const & customToStringMethodWorker(LogLevel ll)
			{
				logging::thread::MutexGuard guard(mtx);
				auto i = ll2nm.find(ll);
				if (i != ll2nm.end())
					return i->second;

				return internal::empty_str;
			}

			LogLevel customFromStringMethodWorker(const tstring& nm)
			{
				logging::thread::MutexGuard guard(mtx);
				auto i = nm2ll.find(nm);
				if (i != nm2ll.end())
					return i->second;

				return NOT_SET_LOG_LEVEL;
			}

			LOGGING_PRIVATE static tstring const & customToStringMethod(LogLevel ll);
			LOGGING_PRIVATE static LogLevel customFromStringMethod(const tstring& nm);
		};

		LOGGING_PRIVATE CustomLogLevelManager & getCustomLogLevelManager();

	} // namespace internal

} // namespace logging


#endif // LOGGING_INTERNAL_CUSTOMLOGLEVELMANAGER_HEADER
