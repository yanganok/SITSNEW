#include <logging/helpers/connectorthread.h>
#include <logging/helpers/loglog.h>


#if ! defined (LOGGING_SINGLE_THREADED)

namespace logging {
	namespace helpers {


		IConnectorThreadClient::~IConnectorThreadClient()
		{ }

		//
		//
		//

		ConnectorThread::ConnectorThread(
			IConnectorThreadClient & client)
			: ctc(client)
			, exit_flag(false)
		{ }


		ConnectorThread::~ConnectorThread()
		{ }


		void
			ConnectorThread::run()
		{
			while (true)
			{
				trigger_ev.timed_wait(30 * 1000);

				helpers::getLogLog().debug(
					LOGGING_TEXT("ConnectorThread::run()- running..."));

				// Check exit condition as the very first thing.

				{
					thread::MutexGuard guard(access_mutex);
					if (exit_flag)
						return;
					trigger_ev.reset();
				}

				// Do not try to re-open already open socket.

				helpers::Socket & client_socket = ctc.ctcGetSocket();
				thread::Mutex const & client_access_mutex = ctc.ctcGetAccessMutex();
				{
					thread::MutexGuard guard(client_access_mutex);
					if (client_socket.isOpen())
						continue;
				}

				// The socket is not open, try to reconnect.

				helpers::Socket new_socket(ctc.ctcConnect());
				if (!new_socket.isOpen())
				{
					helpers::getLogLog().error(
						LOGGING_TEXT("ConnectorThread::run()")
						LOGGING_TEXT("- Cannot connect to server"));

					// Sleep for a short while after unsuccessful connection attempt
					// so that we do not try to reconnect after each logging attempt
					// which could be many times per second.
					std::this_thread::sleep_for(std::chrono::seconds(5));

					continue;
				}

				// Connection was successful, move the socket into client.

				{
					thread::MutexGuard guard(client_access_mutex);
					client_socket = std::move(new_socket);
					ctc.ctcSetConnected();
				}
			}
		}


		void
			ConnectorThread::terminate()
		{
			{
				thread::MutexGuard guard(access_mutex);
				exit_flag = true;
				trigger_ev.signal();
			}
			join();
		}


		void
			ConnectorThread::trigger()
		{
			trigger_ev.signal();
		}


	}
} // namespace logging { namespace helpers {

#endif // ! defined (LOGGING_SINGLE_THREADED)
