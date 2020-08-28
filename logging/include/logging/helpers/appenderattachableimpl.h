#ifndef LOGGING_HELPERS_APPENDER_ATTACHABLE_IMPL_HEADER_
#define LOGGING_HELPERS_APPENDER_ATTACHABLE_IMPL_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/tstring.h>
#include <logging/helpers/pointer.h>
#include <logging/spi/appenderattachable.h>
#include <logging/thread/syncprims.h>

#include <memory>
#include <vector>


namespace logging
{
	namespace helpers
	{

		/**
		 * This Interface is for attaching Appenders to objects.
		 */
		class LOGGING_EXPORT AppenderAttachableImpl : public logging::spi::AppenderAttachable
		{
		public:
			// Data
			thread::Mutex appender_list_mutex;

			// Ctors
			AppenderAttachableImpl();

			// Dtor
			virtual ~AppenderAttachableImpl();

			// Methods
			  /**
			   * Add an appender.  If the appender is already in the list in
			   * won't be added again.
			   */
			virtual void addAppender(SharedAppenderPtr newAppender);

			/**
			 * Get all previously added appenders as an vectory.
			 */
			virtual SharedAppenderPtrList getAllAppenders();

			/**
			 * Look for an attached appender named as <code>name</code>.
			 *
			 * Return the appender with that name if in the list. Return null
			 * otherwise.
			 */
			virtual SharedAppenderPtr getAppender(const logging::tstring& name);

			/**
			 * Remove all previously added appenders.
			 */
			virtual void removeAllAppenders();

			/**
			 * Remove the appender passed as parameter from the list of appenders.
			 */
			virtual void removeAppender(SharedAppenderPtr appender);

			/**
			 * Remove the appender with the name passed as parameter from the
			 * list of appenders.
			 */
			virtual void removeAppender(const logging::tstring& name);

			/**
			 * Call the <code>doAppend</code> method on all attached appenders.
			 */
			int appendLoopOnAppenders(const spi::InternalLoggingEvent& event) const;

		protected:
			// Types
			typedef std::vector<SharedAppenderPtr> ListType;

			// Data
			  /** Array of appenders. */
			ListType appenderList;

		private:
			AppenderAttachableImpl(AppenderAttachableImpl const &);
			AppenderAttachableImpl & operator = (AppenderAttachableImpl const &);
		};  // end class AppenderAttachableImpl

	} // end namespace helpers
} // end namespace logging

#endif // LOGGING_HELPERS_APPENDER_ATTACHABLE_IMPL_HEADER_

