#ifndef LOGGING_HELPERS_CONNECTORTHREAD_H
#define LOGGING_HELPERS_CONNECTORTHREAD_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/thread/syncprims.h>
#include <logging/thread/threads.h>
#include <logging/helpers/socket.h>


#if ! defined (LOGGING_SINGLE_THREADED)

namespace logging {
	namespace helpers {


		class LOGGING_EXPORT ConnectorThread;

		//! Interface implemented by users of ConnectorThread.
		class LOGGING_EXPORT IConnectorThreadClient
		{
		protected:
			virtual ~IConnectorThreadClient();

			//! \return Mutex for synchronization between ConnectorThread and
			//! its client object. This is usually SharedObject::access_mutex.
			virtual thread::Mutex const & ctcGetAccessMutex() const = 0;

			//! \return Socket variable in ConnectorThread client to maintain.
			virtual helpers::Socket & ctcGetSocket() = 0;

			//! \return ConnectorThread client's function returning connected
			//! socket.
			virtual helpers::Socket ctcConnect() = 0;

			//! Sets connected flag to true in ConnectorThread's client.
			virtual void ctcSetConnected() = 0;

			friend class LOGGING_EXPORT ConnectorThread;
		};


		//! This class is used by SocketAppender and (remote) SysLogAppender
		//! to provide asynchronous re-connection.
		class LOGGING_EXPORT ConnectorThread
			: public thread::AbstractThread
		{
		public:
			//! \param client reference to ConnectorThread's client object
			ConnectorThread(IConnectorThreadClient & client);
			virtual ~ConnectorThread();

			virtual void run();

			//! Call this function to terminate ConnectorThread. The function
			//! sets `exit_flag` and then triggers `trigger_ev` to wake up the
			//! ConnectorThread.
			void terminate();

			//! This function triggers (`trigger_ev`) connection check and
			//! attempt to re-connect a broken connection, when necessary.
			void trigger();

		protected:
			//! reference to ConnectorThread's client
			IConnectorThreadClient & ctc;

			//! This event is the re-connection trigger.
			thread::ManualResetEvent trigger_ev;

			//! When this variable set to true when ConnectorThread is signaled to 
			bool exit_flag;
		};


	}
} // namespace logging { namespace helpers {

#endif // ! defined (LOGGING_SINGLE_THREADED)

#endif // LOGGING_HELPERS_CONNECTORTHREAD_H
