#ifndef LOGGING_LOG4J_UDP_APPENDER_HEADER_
#define LOGGING_LOG4J_UDP_APPENDER_HEADER_

#include <logging/config.hxx>
#include <logging/appender.h>
#include <logging/helpers/socket.h>

namespace logging {

	/**
	 * Sends log events as Log4j XML to a remote a log server.
	 *
	 * The Log4jUdpAppender has the following properties:
	 *
	 * <ul>
	 *   <li>Remote logging is non-intrusive as far as the log event
	 *   is concerned. In other words, the event will be logged with
	 *   the same time stamp, NDC, location info as if it were logged
	 *   locally by the client.</li>
	 *
	 *   <li>Remote logging uses the UDP protocol.</li>
	 * </ul>
	 *
	 * <h3>Properties</h3>
	 * <dl>
	 * <dt><tt>host</tt></dt>
	 * <dd>Remote host name to connect and send events to.</dd>
	 *
	 * <dt><tt>port</tt></dt>
	 * <dd>Port on remote host to send events to. Default is 5000.</dd>
	 *
	 * <dt><tt>IPv6</tt></dt>
	 * <dd>Boolean value specifying whether to use IPv6 (true) or IPv4
	 * (false). Default value is false.</dd>
	 *
	 * </dl>
	 */
	class LOGGING_EXPORT Log4jUdpAppender : public Appender {
	public:
		// Ctors
		Log4jUdpAppender(const logging::tstring& host, int port,
			bool ipv6 = false);
		Log4jUdpAppender(const logging::helpers::Properties & properties);

		// Dtor
		~Log4jUdpAppender();

		// Methods
		virtual void close();

	protected:
		void openSocket();
		virtual void append(const spi::InternalLoggingEvent& event);

		// Data
		logging::helpers::Socket socket;
		logging::tstring host;
		int port;
		bool ipv6 = false;

	private:
		// Disallow copying of instances of this class
		Log4jUdpAppender(const Log4jUdpAppender&);
		Log4jUdpAppender& operator=(const Log4jUdpAppender&);
	};
} // end namespace logging

#endif // LOGGING_LOG4J_UDP_APPENDER_HEADER_
