#include <logging/appender.h>
#include <logging/helpers/appenderattachableimpl.h>
#include <logging/helpers/loglog.h>
#include <logging/spi/loggingevent.h>
#include <logging/thread/syncprims-pub-impl.h>

#include <algorithm>


namespace logging
{


	namespace spi
	{


		AppenderAttachable::~AppenderAttachable()
		{ }


	} // namespace spi


	namespace helpers
	{


		//////////////////////////////////////////////////////////////////////////////
		// logging::helpers::AppenderAttachableImpl ctor and dtor
		//////////////////////////////////////////////////////////////////////////////

		AppenderAttachableImpl::AppenderAttachableImpl()
		{ }


		AppenderAttachableImpl::~AppenderAttachableImpl()
		{ }



		///////////////////////////////////////////////////////////////////////////////
		// logging::helpers::AppenderAttachableImpl public methods
		///////////////////////////////////////////////////////////////////////////////

		void
			AppenderAttachableImpl::addAppender(SharedAppenderPtr newAppender)
		{
			if (!newAppender)
			{
				getLogLog().warn(LOGGING_TEXT("Tried to add NULL appender"));
				return;
			}

			thread::MutexGuard guard(appender_list_mutex);

			auto it = std::find(appenderList.begin(), appenderList.end(), newAppender);
			if (it == appenderList.end())
			{
				appenderList.push_back(newAppender);
			}
		}



		AppenderAttachableImpl::ListType
			AppenderAttachableImpl::getAllAppenders()
		{
			thread::MutexGuard guard(appender_list_mutex);

			return appenderList;
		}



		SharedAppenderPtr
			AppenderAttachableImpl::getAppender(const logging::tstring& name)
		{
			thread::MutexGuard guard(appender_list_mutex);

			for (SharedAppenderPtr & ptr : appenderList)
			{
				if (ptr->getName() == name)
					return ptr;
			}

			return SharedAppenderPtr();
		}



		void
			AppenderAttachableImpl::removeAllAppenders()
		{
			thread::MutexGuard guard(appender_list_mutex);

			// Clear appenders in specific order because the order of destruction of
			// std::vector elements is surprisingly unspecified and it breaks our
			// tests' expectations.

			for (auto & app : appenderList)
				app = SharedAppenderPtr();

			appenderList.clear();
		}



		void
			AppenderAttachableImpl::removeAppender(SharedAppenderPtr appender)
		{
			if (!appender)
			{
				getLogLog().warn(LOGGING_TEXT("Tried to remove NULL appender"));
				return;
			}

			thread::MutexGuard guard(appender_list_mutex);

			auto it = std::find(appenderList.begin(), appenderList.end(), appender);
			if (it != appenderList.end())
			{
				appenderList.erase(it);
			}
		}



		void
			AppenderAttachableImpl::removeAppender(const logging::tstring& name)
		{
			removeAppender(getAppender(name));
		}



		int
			AppenderAttachableImpl::appendLoopOnAppenders(const spi::InternalLoggingEvent& event) const
		{
			int count = 0;

			thread::MutexGuard guard(appender_list_mutex);

			for (auto & appender : appenderList)
			{
				++count;
				appender->doAppend(event);
			}

			return count;
		}


	} // namespace helpers


} // namespace logging
