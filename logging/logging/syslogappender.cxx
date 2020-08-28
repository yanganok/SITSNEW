#include <logging/syslogappender.h>
#include <logging/streams.h>
#include <logging/helpers/loglog.h>
#include <logging/helpers/property.h>
#include <logging/helpers/stringhelper.h>
#include <logging/spi/loggingevent.h>
#include <logging/internal/internal.h>
#include <logging/internal/env.h>
#include <logging/thread/syncprims-pub-impl.h>
#include <cstring>

#if defined (LOGGING_HAVE_SYSLOG_H)
#include <syslog.h>

#else // LOGGING_HAVE_SYSLOG_H

// The following bits were derived from SUSv4 documentation and
// RFC5424 document.

// priority codes
#define LOG_EMERG   0
#define LOG_ALERT   1
#define LOG_CRIT    2
#define LOG_ERR     3
#define LOG_WARNING 4
#define LOG_NOTICE  5
#define LOG_INFO    6
#define LOG_DEBUG   7

// facility codes
#define LOG_KERN      (0 << 3)
#define LOG_USER      (1 << 3)
#define LOG_MAIL      (2 << 3)
#define LOG_DAEMON    (3 << 3)
#define LOG_AUTH      (4 << 3)
#define LOG_SYSLOG    (5 << 3)
#define LOG_LPR       (6 << 3)
#define LOG_NEWS      (7 << 3)
#define LOG_UUCP      (8 << 3)
#define LOG_CRON      (9 << 3)
#define LOG_AUTHPRIV (10 << 3)
#define LOG_FTP      (11 << 3)
#define LOG_NTP      (12 << 3)
#define LOG_SECURITY (13 << 3)
#define LOG_CONSOLE  (14 << 3)
// (15 << 3) is missing here
#define LOG_LOCAL0   (16 << 3)
#define LOG_LOCAL1   (17 << 3)
#define LOG_LOCAL2   (18 << 3)
#define LOG_LOCAL3   (19 << 3)
#define LOG_LOCAL4   (20 << 3)
#define LOG_LOCAL5   (21 << 3)
#define LOG_LOCAL6   (22 << 3)
#define LOG_LOCAL7   (23 << 3)

#endif // LOGGING_HAVE_SYSLOG_H


namespace logging
{

	namespace
	{

		static
			const char*
			useIdent(const std::string& string)
		{
			if (string.empty())
				return nullptr;
			else
				return string.c_str();
		}


#ifdef LOG_USER
		int const fallback_facility = LOG_USER;

#else
		int const fallback_facility = 0;

#endif


		static
			int
			parseFacility(const tstring& text)
		{
			if (text.empty())
				return fallback_facility;
#ifdef LOG_AUTH
			else if (text == LOGGING_TEXT("auth"))
				return LOG_AUTH;
#endif
#ifdef LOG_AUTHPRIV
			else if (text == LOGGING_TEXT("authpriv"))
				return LOG_AUTHPRIV;
#endif
#ifdef LOG_CONSOLE
			else if (text == LOGGING_TEXT("console"))
				return LOG_CONSOLE;
#endif
#ifdef LOG_CRON
			else if (text == LOGGING_TEXT("cron"))
				return LOG_CRON;
#endif
#ifdef LOG_DAEMON
			else if (text == LOGGING_TEXT("daemon"))
				return LOG_DAEMON;
#endif
#ifdef LOG_FTP
			else if (text == LOGGING_TEXT("ftp"))
				return LOG_FTP;
#endif
#ifdef LOG_KERN
			else if (text == LOGGING_TEXT("kern"))
				return LOG_KERN;
#endif
#ifdef LOG_LOCAL0
			else if (text == LOGGING_TEXT("local0"))
				return LOG_LOCAL0;
#endif
#ifdef LOG_LOCAL1
			else if (text == LOGGING_TEXT("local1"))
				return LOG_LOCAL1;
#endif
#ifdef LOG_LOCAL2
			else if (text == LOGGING_TEXT("local2"))
				return LOG_LOCAL2;
#endif
#ifdef LOG_LOCAL3
			else if (text == LOGGING_TEXT("local3"))
				return LOG_LOCAL3;
#endif
#ifdef LOG_LOCAL4
			else if (text == LOGGING_TEXT("local4"))
				return LOG_LOCAL4;
#endif
#ifdef LOG_LOCAL5
			else if (text == LOGGING_TEXT("local5"))
				return LOG_LOCAL5;
#endif
#ifdef LOG_LOCAL6
			else if (text == LOGGING_TEXT("local6"))
				return LOG_LOCAL6;
#endif
#ifdef LOG_LOCAL7
			else if (text == LOGGING_TEXT("local7"))
				return LOG_LOCAL7;
#endif
#ifdef LOG_LPR
			else if (text == LOGGING_TEXT("lpr"))
				return LOG_LPR;
#endif
#ifdef LOG_MAIL
			else if (text == LOGGING_TEXT("mail"))
				return LOG_MAIL;
#endif
#ifdef LOG_NEWS
			else if (text == LOGGING_TEXT("news"))
				return LOG_NEWS;
#endif
#ifdef LOG_NTP
			else if (text == LOGGING_TEXT("ntp"))
				return LOG_NTP;
#endif
#ifdef LOG_SECURITY
			else if (text == LOGGING_TEXT("security"))
				return LOG_SECURITY;
#endif
#ifdef LOG_SYSLOG
			else if (text == LOGGING_TEXT("syslog"))
				return LOG_SYSLOG;
#endif
#ifdef LOG_USER
			else if (text == LOGGING_TEXT("user"))
				return LOG_USER;
#endif
#ifdef LOG_UUCP
			else if (text == LOGGING_TEXT("uucp"))
				return LOG_UUCP;
#endif
			else
			{
				// Unknown facility.
				tstring msg(LOGGING_TEXT("Unknown syslog facility: "));
				msg += text;
				helpers::getLogLog().error(msg);

				return fallback_facility;
			}
		}


	} // namespace


	///////////////////////////////////////////////////////////////////////////////
	// SysLogAppender ctors and dtor
	///////////////////////////////////////////////////////////////////////////////

#if defined (LOGGING_HAVE_SYSLOG_H)
	SysLogAppender::SysLogAppender(const tstring& id)
		: ident(id)
		, facility(0)
		, appendFunc(&SysLogAppender::appendLocal)
		, port(0)
		, remoteSyslogType()
		, connected(false)
		// Store std::string form of ident as member of SysLogAppender so
		// the address of the c_str() result remains stable for openlog &
		// co to use even if we use wstrings.
		, identStr(LOGGING_TSTRING_TO_STRING(id))
		, hostname(helpers::getHostname(true))
	{
		::openlog(useIdent(identStr), 0, 0);
	}

#endif


	SysLogAppender::SysLogAppender(const helpers::Properties & properties)
		: Appender(properties)
		, facility(0)
		, appendFunc(nullptr)
		, port(0)
		, connected(false)
		, hostname(helpers::getHostname(true))
	{
		ident = properties.getProperty(LOGGING_TEXT("ident"));
		facility = parseFacility(
			helpers::toLower(
				properties.getProperty(LOGGING_TEXT("facility"))));
		identStr = LOGGING_TSTRING_TO_STRING(ident);

		bool udp = true;
		properties.getBool(udp, LOGGING_TEXT("udp"));
		remoteSyslogType = udp ? RSTUdp : RSTTcp;

		properties.getBool(ipv6, LOGGING_TEXT("IPv6"));

		properties.getString(host, LOGGING_TEXT("host"))
			|| properties.getString(host, LOGGING_TEXT("SyslogHost"));
		if (host.empty())
		{
#if defined (LOGGING_HAVE_SYSLOG_H)
			appendFunc = &SysLogAppender::appendLocal;
			::openlog(useIdent(identStr), 0, 0);

#else
			helpers::getLogLog().error(
				LOGGING_TEXT("SysLogAppender")
				LOGGING_TEXT("- local syslog not available"), true);

#endif
		}
		else
		{
			if (!properties.getInt(port, LOGGING_TEXT("port")))
				port = 514;

			appendFunc = &SysLogAppender::appendRemote;
			openSocket();
			initConnector();
		}
	}


	SysLogAppender::SysLogAppender(const tstring& id, const tstring & h,
		int p, const tstring & f, SysLogAppender::RemoteSyslogType rst,
		bool ipv6_ /*= false*/)
		: ident(id)
		, facility(parseFacility(helpers::toLower(f)))
		, appendFunc(&SysLogAppender::appendRemote)
		, host(h)
		, port(p)
		, remoteSyslogType(rst)
		, connected(false)
		, ipv6(ipv6_)
		// Store std::string form of ident as member of SysLogAppender so
		// the address of the c_str() result remains stable for openlog &
		// co to use even if we use wstrings.
		, identStr(LOGGING_TSTRING_TO_STRING(id))
		, hostname(helpers::getHostname(true))
	{
		openSocket();
		initConnector();
	}


	SysLogAppender::~SysLogAppender()
	{
		destructorImpl();
	}



	///////////////////////////////////////////////////////////////////////////////
	// SysLogAppender public methods
	///////////////////////////////////////////////////////////////////////////////

	void
		SysLogAppender::close()
	{
		helpers::getLogLog().debug(
			LOGGING_TEXT("Entering SysLogAppender::close()..."));
		thread::MutexGuard guard(access_mutex);

		if (host.empty())
		{
#if defined (LOGGING_HAVE_SYSLOG_H)
			::closelog();
#endif
		}
		else
			syslogSocket.close();

#if ! defined (LOGGING_SINGLE_THREADED)
		if (connector)
			connector->terminate();
#endif

		closed = true;
	}



	///////////////////////////////////////////////////////////////////////////////
	// SysLogAppender protected methods
	///////////////////////////////////////////////////////////////////////////////

	int
		SysLogAppender::getSysLogLevel(const LogLevel& ll) const
	{
		if (ll < INFO_LOG_LEVEL /* || ll < DEBUG_LOG_LEVEL*/) {
			return LOG_DEBUG;
		}
		else if (ll < WARN_LOG_LEVEL) {
			return LOG_INFO;
		}
		else if (ll < ERROR_LOG_LEVEL) {
			return LOG_WARNING;
		}
		else if (ll < FATAL_LOG_LEVEL) {
			return LOG_ERR;
		}
		else if (ll == FATAL_LOG_LEVEL) {
			return LOG_CRIT;
		}

		return LOG_ALERT;  // ll > FATAL_LOG_LEVEL
	}


	// This method does not need to be locked since it is called by
	// doAppend() which performs the locking
	void
		SysLogAppender::append(const spi::InternalLoggingEvent& event)
	{
		(this->*appendFunc) (event);
	}


#if defined (LOGGING_HAVE_SYSLOG_H)
	void
		SysLogAppender::appendLocal(const spi::InternalLoggingEvent& event)
	{
		int const level = getSysLogLevel(event.getLogLevel());
		internal::appender_sratch_pad & appender_sp = internal::get_appender_sp();
		detail::clear_tostringstream(appender_sp.oss);
		layout->formatAndAppend(appender_sp.oss, event);
		appender_sp.str = appender_sp.oss.str();
		::syslog(facility | level, "%s",
			LOGGING_TSTRING_TO_STRING(appender_sp.str).c_str());
	}

#endif


	tstring const SysLogAppender::remoteTimeFormat(
		LOGGING_TEXT("%Y-%m-%dT%H:%M:%S.%qZ"));


	void
		SysLogAppender::appendRemote(const spi::InternalLoggingEvent& event)
	{

		if (!connected)
		{
#if ! defined (LOGGING_SINGLE_THREADED)
			connector->trigger();
			return;

#else
			openSocket();
			if (!connected)
			{
				helpers::getLogLog().error(
					LOGGING_TEXT("SysLogAppender")
					LOGGING_TEXT("- failed to connect to ")
					+ host + LOGGING_TEXT(":")
					+ helpers::convertIntegerToString(port));
				return;
			}
#endif
		}

		int const level = getSysLogLevel(event.getLogLevel());
		internal::appender_sratch_pad & appender_sp = internal::get_appender_sp();
		detail::clear_tostringstream(appender_sp.oss);

		appender_sp.oss
			// PRI
			<< LOGGING_TEXT('<') << (level | facility) << LOGGING_TEXT('>')
			// VERSION
			<< 1
			// TIMESTAMP
			<< LOGGING_TEXT(' ')
			<< helpers::getFormattedTime(remoteTimeFormat, event.getTimestamp(),
				true)
			// HOSTNAME
			<< LOGGING_TEXT(' ') << hostname
			// APP-NAME
			<< LOGGING_TEXT(' ') << ident
			// PROCID
			<< LOGGING_TEXT(' ') << internal::get_process_id()
			// MSGID
			<< LOGGING_TEXT(' ') << event.getLoggerName()
			// STRUCTURED-DATA
			// no structured data, it could be whole MDC
			<< LOGGING_TEXT(" - ");

		// MSG
		layout->formatAndAppend(appender_sp.oss, event);

		appender_sp.chstr = LOGGING_TSTRING_TO_STRING(appender_sp.oss.str());

		if (remoteSyslogType != RSTUdp)
		{
			// see (RFC6587, 3.4.1 Octet
			// Counting)[http://tools.ietf.org/html/rfc6587#section-3.4.1]
			std::string syslogFrameHeader(
				helpers::convertIntegerToNarrowString(appender_sp.chstr.size()));
			syslogFrameHeader += ' ';
			appender_sp.chstr.insert(appender_sp.chstr.begin(),
				syslogFrameHeader.begin(), syslogFrameHeader.end());
		}

		bool ret = syslogSocket.write(appender_sp.chstr);
		if (!ret)
		{
			helpers::getLogLog().warn(
				LOGGING_TEXT("SysLogAppender::appendRemote")
				LOGGING_TEXT("- socket write failed"));

			connected = false;

#if ! defined (LOGGING_SINGLE_THREADED)
			connector->trigger();
#endif
		}
	}


#if ! defined (LOGGING_SINGLE_THREADED)
	thread::Mutex const &
		SysLogAppender::ctcGetAccessMutex() const
	{
		return access_mutex;
	}


	helpers::Socket &
		SysLogAppender::ctcGetSocket()
	{
		return syslogSocket;
	}


	helpers::Socket
		SysLogAppender::ctcConnect()
	{
		return helpers::Socket(host, static_cast<unsigned short>(port),
			remoteSyslogType == RSTUdp);
	}


	void
		SysLogAppender::ctcSetConnected()
	{
		connected = true;
	}

#endif


	void
		SysLogAppender::initConnector()
	{
#if ! defined (LOGGING_SINGLE_THREADED)
		connected = true;
		connector = new helpers::ConnectorThread(*this);
		connector->start();
#endif
	}


	void
		SysLogAppender::openSocket()
	{
		syslogSocket = helpers::Socket(host, static_cast<unsigned short>(port),
			remoteSyslogType == RSTUdp, ipv6);
		connected = syslogSocket.isOpen();
		if (!connected)
			helpers::getLogLog().error(
				LOGGING_TEXT("SysLogAppender")
				LOGGING_TEXT("- failed to connect to ")
				+ host
				+ LOGGING_TEXT(":") + helpers::convertIntegerToString(port));
	}


} // namespace logging
