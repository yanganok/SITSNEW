#ifndef LOGGING_NT_EVENT_LOG_APPENDER_HEADER_
#define LOGGING_NT_EVENT_LOG_APPENDER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#if defined (LOGGING_HAVE_NT_EVENT_LOG)

#include <logging/appender.h>
#include <logging/config/windowsh-inc.h>


namespace logging {

	/**
	 * Appends log events to NT EventLog.
	 */
	class LOGGING_EXPORT NTEventLogAppender : public Appender {
	public:
		// ctors
		NTEventLogAppender(const logging::tstring& server,
			const logging::tstring& log,
			const logging::tstring& source);
		NTEventLogAppender(const logging::helpers::Properties & properties);

		// dtor
		virtual ~NTEventLogAppender();

		// public Methods
		virtual void close();

	protected:
		virtual void append(const spi::InternalLoggingEvent& event);
		virtual WORD getEventType(const spi::InternalLoggingEvent& event);
		virtual WORD getEventCategory(const spi::InternalLoggingEvent& event);
		void init();

		/*
		 * Add this source with appropriate configuration keys to the registry.
		 */
		void addRegistryInfo();

		// Data
		logging::tstring server;
		logging::tstring log;
		logging::tstring source;
		HANDLE hEventLog;
		SID* pCurrentUserSID;

	private:
		// Disallow copying of instances of this class
		NTEventLogAppender(const NTEventLogAppender&);
		NTEventLogAppender& operator=(const NTEventLogAppender&);
	};

} // end namespace logging

#endif // LOGGING_HAVE_NT_EVENT_LOG
#endif //LOGGING_NT_EVENT_LOG_APPENDER_HEADER_
