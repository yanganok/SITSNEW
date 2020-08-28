#ifndef LOGGING_SYSLOG_APPENDER_HEADER_
#define LOGGING_SYSLOG_APPENDER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/appender.h>
#include <logging/helpers/socket.h>
#include <logging/helpers/connectorthread.h>


namespace logging
{

	/**
	 * Appends log events to a file.
	 *
	 * <h3>Properties</h3>
	 * <dl>
	 * <dt><tt>ident</tt></dt>
	 * <dd>First argument to <code>openlog()</code>, a string that
	 * will be prepended to every message.</dd>
	 *
	 * <dt><tt>facility</tt></dt>
	 * <dd>Facility is used in combination with syslog level in first
	 * argument to syslog(). It can be one of the supported facility
	 * names (case insensitive), e.g. auth, cron, kern, mail, news
	 * etc.</dd>
	 *
	 * <dt><tt>host</tt></dt>
	 * <dd>Destination syslog host. When this property is specified,
	 * messages are sent using UDP to destination host, otherwise
	 * messages are logged to local syslog.</dd>
	 *
	 * <dt><tt>port</tt></dt>
	 * <dd>Destination port of syslog service on host specified by the
	 * <tt>host</tt> property. The default value is port 514.</dd>
	 *
	 * <dt><tt>udp</tt></dt> <dd>When the syslog is remote, this
	 * property picks the IP protocol. When the value is true, UDP is
	 * used. When the value is false, TCP is used. The default value
	 * is true.</dd>
	 *
	 * <dt><tt>IPv6</tt></dt>
	 * <dd>Boolean value specifying whether to use IPv6 (true) or IPv4
	 * (false). Default value is false.</dd>
	 *
	 * </dl>
	 *
	 * \note Messages sent to remote syslog using UDP are conforming
	 * to RFC5424. Messages sent to remote syslog using TCP are
	 * using octet counting as described in RFC6587.
	 */
	class LOGGING_EXPORT SysLogAppender
		: public Appender
#if ! defined (LOGGING_SINGLE_THREADED)
		, protected virtual helpers::IConnectorThreadClient
#endif
	{
	public:
		//! Remote syslog IP protocol type.
		enum RemoteSyslogType
		{
			RSTUdp,
			RSTTcp
		};

		// Ctors
#if defined (LOGGING_HAVE_SYSLOG_H)
		SysLogAppender(const tstring& ident);
#endif
		SysLogAppender(const tstring& ident, const tstring & host,
			int port = 514, const tstring & facility = tstring(),
			RemoteSyslogType remoteSyslogType = RSTUdp, bool ipv6 = false);
		SysLogAppender(const logging::helpers::Properties & properties);

		// Dtor
		virtual ~SysLogAppender();

		// Methods
		virtual void close();

	protected:
		virtual int getSysLogLevel(const LogLevel& ll) const;
		virtual void append(const spi::InternalLoggingEvent& event);
#if defined (LOGGING_HAVE_SYSLOG_H)
		//! Local syslog (served by `syslog()`) worker function.
		void appendLocal(const spi::InternalLoggingEvent& event);
#endif
		//! Remote syslog worker function.
		void appendRemote(const spi::InternalLoggingEvent& event);

		// Data
		tstring ident;
		int facility;

		typedef void (SysLogAppender:: * AppendFuncType) (
			const spi::InternalLoggingEvent&);
		AppendFuncType appendFunc;

		tstring host;
		int port;
		RemoteSyslogType remoteSyslogType;
		helpers::Socket syslogSocket;
		bool connected;
		bool ipv6 = false;

		static tstring const remoteTimeFormat;

		void initConnector();
		void openSocket();

#if ! defined (LOGGING_SINGLE_THREADED)
		virtual thread::Mutex const & ctcGetAccessMutex() const;
		virtual helpers::Socket & ctcGetSocket();
		virtual helpers::Socket ctcConnect();
		virtual void ctcSetConnected();

		helpers::SharedObjectPtr<helpers::ConnectorThread> connector;
#endif

	private:
		// Disallow copying of instances of this class
		SysLogAppender(const SysLogAppender&);
		SysLogAppender& operator=(const SysLogAppender&);

		std::string identStr;
		tstring hostname;
	};

} // end namespace logging


#endif // LOGGING_SYSLOG_APPENDER_HEADER_
