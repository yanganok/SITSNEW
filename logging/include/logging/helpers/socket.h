#ifndef LOGGING_HELPERS_SOCKET_HEADER_
#define LOGGING_HELPERS_SOCKET_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <array>

#include <logging/tstring.h>
#include <logging/helpers/socketbuffer.h>


namespace logging {
	namespace helpers {

		enum SocketState {
			ok,
			not_opened,
			bad_address,
			connection_failed,
			broken_pipe,
			invalid_access_mode,
			message_truncated,
			accept_interrupted
		};

		typedef std::ptrdiff_t SOCKET_TYPE;

		extern LOGGING_EXPORT SOCKET_TYPE const INVALID_SOCKET_VALUE;

		class LOGGING_EXPORT AbstractSocket {
		public:
			AbstractSocket();
			AbstractSocket(SOCKET_TYPE sock, SocketState state, int err);
			AbstractSocket(AbstractSocket const &) = delete;
			AbstractSocket(AbstractSocket &&) LOGGING_NOEXCEPT;
			virtual ~AbstractSocket() = 0;

			/// Close socket
			virtual void close();
			virtual bool isOpen() const;
			virtual void shutdown();
			AbstractSocket & operator = (AbstractSocket && rhs) LOGGING_NOEXCEPT;

			void swap(AbstractSocket &);

		protected:
			SOCKET_TYPE sock;
			SocketState state;
			int err;
		};



		/**
		 * This class implements client sockets (also called just "sockets").
		 * A socket is an endpoint for communication between two machines.
		 */
		class LOGGING_EXPORT Socket : public AbstractSocket {
		public:
			// ctor and dtor
			Socket();
			Socket(SOCKET_TYPE sock, SocketState state, int err);
			Socket(const tstring& address, unsigned short port,
				bool udp = false, bool ipv6 = false);
			Socket(Socket &&) LOGGING_NOEXCEPT;
			virtual ~Socket();

			Socket & operator = (Socket &&) LOGGING_NOEXCEPT;

			// methods
			virtual bool read(SocketBuffer& buffer);
			virtual bool write(const SocketBuffer& buffer);
			virtual bool write(const std::string & buffer);
			virtual bool write(std::size_t bufferCount,
				SocketBuffer const * const * buffers);

			template <typename... Args>
			static bool write(Socket & socket, Args &&... args)
			{
				SocketBuffer const * const buffers[sizeof... (args)]{
					(&args)... };
				return socket.write(sizeof... (args), buffers);
			}
		};



		/**
		 * This class implements server sockets. A server socket waits for
		 * requests to come in over the network. It performs some operation
		 * based on that request, and then possibly returns a result to the
		 * requester.
		 */
		class LOGGING_EXPORT ServerSocket : public AbstractSocket {
		public:
			ServerSocket(unsigned short port, bool udp = false,
				bool ipv6 = false, tstring const & host = tstring());
			ServerSocket(ServerSocket &&) LOGGING_NOEXCEPT;
			virtual ~ServerSocket();

			ServerSocket & operator = (ServerSocket &&) LOGGING_NOEXCEPT;

			Socket accept();
			void interruptAccept();
			void swap(ServerSocket &);

		protected:
			std::array<std::ptrdiff_t, 2> interruptHandles;
		};


		LOGGING_EXPORT SOCKET_TYPE openSocket(unsigned short port, bool udp,
			bool ipv6, SocketState& state);
		LOGGING_EXPORT SOCKET_TYPE openSocket(tstring const & host,
			unsigned short port, bool udp, bool ipv6, SocketState& state);

		LOGGING_EXPORT SOCKET_TYPE connectSocket(const logging::tstring& hostn,
			unsigned short port, bool udp, bool ipv6, SocketState& state);
		LOGGING_EXPORT SOCKET_TYPE acceptSocket(SOCKET_TYPE sock, SocketState& state);
		LOGGING_EXPORT int closeSocket(SOCKET_TYPE sock);
		LOGGING_EXPORT int shutdownSocket(SOCKET_TYPE sock);

		LOGGING_EXPORT long read(SOCKET_TYPE sock, SocketBuffer& buffer);
		LOGGING_EXPORT long write(SOCKET_TYPE sock,
			const SocketBuffer& buffer);
		LOGGING_EXPORT long write(SOCKET_TYPE sock, std::size_t bufferCount,
			SocketBuffer const * const * buffers);
		LOGGING_EXPORT long write(SOCKET_TYPE sock,
			const std::string & buffer);

		LOGGING_EXPORT tstring getHostname(bool fqdn);
		LOGGING_EXPORT int setTCPNoDelay(SOCKET_TYPE, bool);

	} // end namespace helpers
} // end namespace logging

#endif // LOGGING_HELPERS_SOCKET_HEADER_
