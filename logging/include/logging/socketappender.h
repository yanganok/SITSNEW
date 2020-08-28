#ifndef LOGGING_SOCKET_APPENDER_HEADER_
#define LOGGING_SOCKET_APPENDER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/appender.h>
#include <logging/helpers/socket.h>
#include <logging/thread/syncprims.h>
#include <logging/thread/threads.h>
#include <logging/helpers/connectorthread.h>


namespace logging
{

#ifndef UNICODE
	std::size_t const LOGGING_MAX_MESSAGE_SIZE = 8 * 1024;
#else
	std::size_t const LOGGING_MAX_MESSAGE_SIZE = 2 * 8 * 1024;
#endif


	/**
	 * Sends {@link spi::InternalLoggingEvent} objects to a remote a log server.
	 *
	 * The SocketAppender has the following properties:
	 *
	 * <ul>
	 *
	 *   <li>Remote logging is non-intrusive as far as the log event
	 *   is concerned. In other words, the event will be logged with
	 *   the same time stamp, NDC, location info as if it were logged
	 *   locally by the client.
	 *
	 *   <li>SocketAppenders do not use a layout.
	 *
	 *   <li>Remote logging uses the TCP protocol. Consequently, if
	 *   the server is reachable, then log events will eventually arrive
	 *   at the server.
	 *
	 *   <li>If the remote server is down, the logging requests are
	 *   simply dropped. However, if and when the server comes back up,
	 *   then event transmission is resumed transparently. This
	 *   transparent reconneciton is performed by a <em>connector</em>
	 *   thread which periodically attempts to connect to the server.
	 *
	 *   <li>Logging events are automatically <em>buffered</em> by the
	 *   native TCP implementation. This means that if the link to server
	 *   is slow but still faster than the rate of (log) event production
	 *   by the client, the client will not be affected by the slow
	 *   network connection. However, if the network connection is slower
	 *   then the rate of event production, then the client can only
	 *   progress at the network rate. In particular, if the network link
	 *   to the the server is down, the client will be blocked.
	 *
	 *   <li>On the other hand, if the network link is up, but the server
	 *   is down, the client will not be blocked when making log requests
	 *   but the log events will be lost due to server unavailability.
	 * </ul>
	 *
	 * <h3>Properties</h3>
	 * <dl>
	 * <dt><tt>host</tt></dt>
	 * <dd>Remote host name to connect and send events to.</dd>
	 *
	 * <dt><tt>port</tt></dt>
	 * <dd>Port on remote host to send events to.</dd>
	 *
	 * <dt><tt>ServerName</tt></dt>
	 * <dd>Host name of event's origin prepended to each event.</dd>
	 *
	 * <dt><tt>IPv6</tt></dt>
	 * <dd>Boolean value specifying whether to use IPv6 (true) or IPv4
	 * (false). Default value is false.</dd>
	 *
	 * </dl>
	 */
	class LOGGING_EXPORT SocketAppender
		: public Appender
#if ! defined (LOGGING_SINGLE_THREADED)
		, protected virtual helpers::IConnectorThreadClient
#endif
	{
	public:
		// Ctors
		SocketAppender(const logging::tstring& host, unsigned short port,
			const logging::tstring& serverName = tstring(),
			bool ipv6 = false);
		SocketAppender(const logging::helpers::Properties & properties);

		// Dtor
		~SocketAppender();

		// Methods
		virtual void close();

	protected:
		void openSocket();
		void initConnector();
		virtual void append(const spi::InternalLoggingEvent& event);

		// Data
		logging::helpers::Socket socket;
		logging::tstring host;
		unsigned int port;
		logging::tstring serverName;
		bool ipv6 = false;

#if ! defined (LOGGING_SINGLE_THREADED)
		virtual thread::Mutex const & ctcGetAccessMutex() const;
		virtual helpers::Socket & ctcGetSocket();
		virtual helpers::Socket ctcConnect();
		virtual void ctcSetConnected();

		volatile bool connected;
		helpers::SharedObjectPtr<helpers::ConnectorThread> connector;
#endif

	private:
		// Disallow copying of instances of this class
		SocketAppender(const SocketAppender&);
		SocketAppender& operator=(const SocketAppender&);
	};

	namespace helpers {
		LOGGING_EXPORT
			void convertToBuffer(SocketBuffer & buffer,
				const logging::spi::InternalLoggingEvent& event,
				const logging::tstring& serverName);

		LOGGING_EXPORT
			logging::spi::InternalLoggingEvent readFromBuffer(SocketBuffer& buffer);
	} // end namespace helpers

} // end namespace logging

#endif // LOGGING_SOCKET_APPENDER_HEADER_
