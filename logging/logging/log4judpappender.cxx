#include <logging/log4judpappender.h>
#include <logging/layout.h>
#include <logging/streams.h>
#include <logging/helpers/loglog.h>
#include <logging/helpers/property.h>
#include <logging/spi/loggingevent.h>
#include <logging/internal/internal.h>
#include <logging/thread/syncprims-pub-impl.h>
#include <iomanip>
#include <cstring>
#if defined (UNICODE)
#include <cwctype>
#else
#include <cctype>
#endif


namespace logging
{

	namespace
	{


		static inline bool
			is_control(tchar ch)
		{
#if defined (UNICODE)
			return !!std::iswcntrl(std::char_traits<tchar>::to_int_type(ch));
#else
			return !!std::iscntrl(std::char_traits<tchar>::to_int_type(ch));
#endif
		}


		//! Outputs str with reserved XML characters escaped.
		static
			void
			output_xml_escaped(tostream & os, tstring const & str)
		{
			for (tstring::const_iterator it = str.begin(); it != str.end(); ++it)
			{
				tchar const & ch = *it;
				switch (ch)
				{
				case LOGGING_TEXT('<'):
					os << LOGGING_TEXT("&lt;");
					break;

				case LOGGING_TEXT('>'):
					os << LOGGING_TEXT("&gt;");
					break;

				case LOGGING_TEXT('&'):
					os << LOGGING_TEXT("&amp;");
					break;

				case LOGGING_TEXT('\''):
					os << LOGGING_TEXT("&apos;");
					break;

				case LOGGING_TEXT('"'):
					os << LOGGING_TEXT("&quot;");
					break;

				default:
					if (is_control(ch))
					{
						tchar const prev_fill = os.fill();
						std::ios_base::fmtflags const prev_flags = os.flags();
						os.flags(std::ios_base::hex | std::ios_base::right);
						os.fill(LOGGING_TEXT('0'));

						os << std::setw(0) << LOGGING_TEXT("&#x")
							<< std::setw(2) << std::char_traits<tchar>::to_int_type(ch)
							<< std::setw(0) << LOGGING_TEXT(";");

						os.fill(prev_fill);
						os.flags(prev_flags);
					}
					else
						os.put(ch);
				}
			}
		}


		//! Helper manipulator like class for escaped XML output.
		struct outputXMLEscaped
		{
			outputXMLEscaped(tstring const & s)
				: str(s)
			{ }

			tstring const & str;
		};


		//! Overload stream insertion for outputXMLEscaped.
		static
			tostream &
			operator << (tostream & os, outputXMLEscaped const & x)
		{
			output_xml_escaped(os, x.str);
			return os;
		}


	} // namespace


	//////////////////////////////////////////////////////////////////////////////
	// Log4jUdpAppender ctors and dtor
	//////////////////////////////////////////////////////////////////////////////

	Log4jUdpAppender::Log4jUdpAppender(const tstring& host_, int port_, bool ipv6_)
		: host(host_)
		, port(port_)
		, ipv6(ipv6_)
	{
		layout.reset(new PatternLayout(LOGGING_TEXT("%m")));
		openSocket();
	}



	Log4jUdpAppender::Log4jUdpAppender(const helpers::Properties & properties)
		: Appender(properties)
		, port(5000)
	{
		host = properties.getProperty(LOGGING_TEXT("host"),
			LOGGING_TEXT("localhost"));
		properties.getInt(port, LOGGING_TEXT("port"));
		properties.getBool(ipv6, LOGGING_TEXT("IPv6"));

		openSocket();
	}



	Log4jUdpAppender::~Log4jUdpAppender()
	{
		destructorImpl();
	}



	//////////////////////////////////////////////////////////////////////////////
	// Log4jUdpAppender public methods
	//////////////////////////////////////////////////////////////////////////////

	void
		Log4jUdpAppender::close()
	{
		helpers::getLogLog().debug(
			LOGGING_TEXT("Entering Log4jUdpAppender::close()..."));

		socket.close();
		closed = true;
	}



	//////////////////////////////////////////////////////////////////////////////
	// Log4jUdpAppender protected methods
	//////////////////////////////////////////////////////////////////////////////

	void
		Log4jUdpAppender::openSocket()
	{
		if (!socket.isOpen()) {
			socket = helpers::Socket(host, port, true, ipv6);
		}
	}

	void
		Log4jUdpAppender::append(const spi::InternalLoggingEvent& event)
	{
		if (!socket.isOpen()) {
			openSocket();
			if (!socket.isOpen()) {
				helpers::getLogLog().error(
					LOGGING_TEXT("Log4jUdpAppender::append()")
					LOGGING_TEXT("- Cannot connect to server"));
				return;
			}
		}

		tstring & str = formatEvent(event);

		internal::appender_sratch_pad & appender_sp
			= internal::get_appender_sp();
		tostringstream & buffer = appender_sp.oss;
		detail::clear_tostringstream(buffer);

		buffer << LOGGING_TEXT("<log4j:event logger=\"")
			<< outputXMLEscaped(event.getLoggerName())
			<< LOGGING_TEXT("\" level=\"")
			// TODO: Some escaping of special characters is needed here.
			<< outputXMLEscaped(getLogLevelManager()
				.toString(event.getLogLevel()))
			<< LOGGING_TEXT("\" timestamp=\"")
			<< helpers::getFormattedTime(LOGGING_TEXT("%s%q"),
				event.getTimestamp())
			<< LOGGING_TEXT("\" thread=\"") << event.getThread()
			<< LOGGING_TEXT("\">")

			<< LOGGING_TEXT("<log4j:message>")
			// TODO: Some escaping of special characters is needed here.
			<< outputXMLEscaped(str)
			<< LOGGING_TEXT("</log4j:message>")

			<< LOGGING_TEXT("<log4j:NDC>")
			// TODO: Some escaping of special characters is needed here.
			<< outputXMLEscaped(event.getNDC())
			<< LOGGING_TEXT("</log4j:NDC>")

			<< LOGGING_TEXT("<log4j:locationInfo class=\"\" file=\"")
			// TODO: Some escaping of special characters is needed here.
			<< outputXMLEscaped(event.getFile())
			<< LOGGING_TEXT("\" method=\"")
			<< outputXMLEscaped(event.getFunction())
			<< LOGGING_TEXT("\" line=\"")
			<< event.getLine()
			<< LOGGING_TEXT("\"/>")
			<< LOGGING_TEXT("</log4j:event>");

		appender_sp.chstr = LOGGING_TSTRING_TO_STRING(buffer.str());

		bool ret = socket.write(appender_sp.chstr);
		if (!ret)
		{
			helpers::getLogLog().error(
				LOGGING_TEXT(
					"Log4jUdpAppender::append()- Cannot write to server"));
		}
	}

} // namespace logging
