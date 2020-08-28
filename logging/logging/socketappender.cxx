#include <cstdlib>
#include <stdexcept>
#include <logging/socketappender.h>
#include <logging/layout.h>
#include <logging/spi/loggingevent.h>
#include <logging/helpers/loglog.h>
#include <logging/helpers/property.h>
#include <logging/thread/syncprims-pub-impl.h>
#include <logging/internal/internal.h>


namespace logging {

	int const LOGGING_MESSAGE_VERSION = 3;


	//////////////////////////////////////////////////////////////////////////////
	// SocketAppender ctors and dtor
	//////////////////////////////////////////////////////////////////////////////

	SocketAppender::SocketAppender(const tstring& host_,
		unsigned short port_, const tstring& serverName_, bool ipv6_ /*= false*/)
		: host(host_)
		, port(port_)
		, serverName(serverName_)
		, ipv6(ipv6_)
	{
		openSocket();
		initConnector();
	}



	SocketAppender::SocketAppender(const helpers::Properties & properties)
		: Appender(properties),
		port(9998)
	{
		host = properties.getProperty(LOGGING_TEXT("host"));
		properties.getUInt(port, LOGGING_TEXT("port"));
		serverName = properties.getProperty(LOGGING_TEXT("ServerName"));
		properties.getBool(ipv6, LOGGING_TEXT("IPv6"));

		openSocket();
		initConnector();
	}



	SocketAppender::~SocketAppender()
	{
		destructorImpl();
	}



	//////////////////////////////////////////////////////////////////////////////
	// SocketAppender public methods
	//////////////////////////////////////////////////////////////////////////////

	void
		SocketAppender::close()
	{
		helpers::getLogLog().debug(
			LOGGING_TEXT("Entering SocketAppender::close()..."));

#if ! defined (LOGGING_SINGLE_THREADED)
		connector->terminate();
#endif

		socket.close();
		closed = true;
	}



	//////////////////////////////////////////////////////////////////////////////
	// SocketAppender protected methods
	//////////////////////////////////////////////////////////////////////////////

	void
		SocketAppender::openSocket()
	{
		if (!socket.isOpen()) {
			socket = helpers::Socket(host, static_cast<unsigned short>(port), false, ipv6);
		}
	}


	void
		SocketAppender::initConnector()
	{
#if ! defined (LOGGING_SINGLE_THREADED)
		connected = true;
		connector = new helpers::ConnectorThread(*this);
		connector->start();
#endif
	}


	void
		SocketAppender::append(const spi::InternalLoggingEvent& event)
	{
#if ! defined (LOGGING_SINGLE_THREADED)
		if (!connected)
		{
			connector->trigger();
			return;
		}

#else
		if (!socket.isOpen()) {
			openSocket();
			if (!socket.isOpen()) {
				helpers::getLogLog().error(
					LOGGING_TEXT(
						"SocketAppender::append()- Cannot connect to server"));
				return;
			}
		}
#endif

		helpers::SocketBuffer msgBuffer(LOGGING_MAX_MESSAGE_SIZE
			- sizeof(unsigned int));

		try
		{
			convertToBuffer(msgBuffer, event, serverName);
		}
		catch (std::runtime_error const &)
		{
			return;
		}

		helpers::SocketBuffer buffer(sizeof(unsigned int));
		buffer.appendInt(static_cast<unsigned>(msgBuffer.getSize()));

		bool ret = helpers::Socket::write(socket, buffer, msgBuffer);
		if (!ret)
		{
			helpers::getLogLog().error(
				LOGGING_TEXT(
					"SocketAppender::append()- Write failed"));

#if ! defined (LOGGING_SINGLE_THREADED)
			connected = false;
			connector->trigger();
#endif
		}
	}


#if ! defined (LOGGING_SINGLE_THREADED)
	thread::Mutex const &
		SocketAppender::ctcGetAccessMutex() const
	{
		return access_mutex;
	}


	helpers::Socket &
		SocketAppender::ctcGetSocket()
	{
		return socket;
	}


	helpers::Socket
		SocketAppender::ctcConnect()
	{
		return helpers::Socket(host, static_cast<unsigned short>(port));
	}

	void
		SocketAppender::ctcSetConnected()
	{
		connected = true;
	}

#endif


	/////////////////////////////////////////////////////////////////////////////
	// namespace helpers methods
	/////////////////////////////////////////////////////////////////////////////

	namespace helpers
	{


		void
			convertToBuffer(SocketBuffer & buffer,
				const spi::InternalLoggingEvent& event,
				const tstring& serverName)
		{
			buffer.appendByte(LOGGING_MESSAGE_VERSION);
#ifndef UNICODE
			buffer.appendByte(1);
#else
			buffer.appendByte(2);
#endif

			buffer.appendString(serverName);
			buffer.appendString(event.getLoggerName());
			buffer.appendInt(event.getLogLevel());
			buffer.appendString(event.getNDC());
			buffer.appendString(event.getMessage());
			buffer.appendString(event.getThread());
			buffer.appendInt(
				static_cast<unsigned int>(to_time_t(event.getTimestamp())));
			buffer.appendInt(
				static_cast<unsigned int>(microseconds_part(event.getTimestamp())));
			buffer.appendString(event.getFile());
			buffer.appendInt(event.getLine());
			buffer.appendString(event.getFunction());
		}


		spi::InternalLoggingEvent
			readFromBuffer(SocketBuffer& buffer)
		{
			unsigned char msgVersion = buffer.readByte();
			if (msgVersion != LOGGING_MESSAGE_VERSION) {
				LogLog * loglog = LogLog::getLogLog();
				loglog->warn(LOGGING_TEXT("readFromBuffer() received socket message with an invalid version"));
			}

			unsigned char sizeOfChar = buffer.readByte();

			tstring serverName = buffer.readString(sizeOfChar);
			tstring loggerName = buffer.readString(sizeOfChar);
			LogLevel ll = buffer.readInt();
			tstring ndc = buffer.readString(sizeOfChar);
			if (!serverName.empty()) {
				if (ndc.empty()) {
					ndc = serverName;
				}
				else {
					ndc = serverName + LOGGING_TEXT(" - ") + ndc;
				}
			}
			tstring message = buffer.readString(sizeOfChar);
			tstring thread = buffer.readString(sizeOfChar);
			long sec = buffer.readInt();
			long usec = buffer.readInt();
			tstring file = buffer.readString(sizeOfChar);
			int line = buffer.readInt();
			tstring function = buffer.readString(sizeOfChar);

			// TODO: Pass MDC through.
			spi::InternalLoggingEvent ev(loggerName, ll, ndc,
				MappedDiagnosticContextMap(), message, thread, internal::empty_str,
				from_time_t(sec) + chrono::microseconds(usec), file,
				line, function);
			return ev;
		}


	} // namespace helpers


} // namespace logging
