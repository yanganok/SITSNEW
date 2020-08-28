#include <logging/helpers/loglog.h>
#include <logging/internal/socket.h>
#include <logging/internal/internal.h>


namespace logging {
	namespace helpers {


		extern LOGGING_EXPORT SOCKET_TYPE const INVALID_SOCKET_VALUE
#if defined(_WIN32)
			= static_cast<SOCKET_TYPE>(INVALID_SOCKET);
#else
			= static_cast<SOCKET_TYPE>(-1);
#endif


		//////////////////////////////////////////////////////////////////////////////
		// AbstractSocket ctors and dtor
		//////////////////////////////////////////////////////////////////////////////

		AbstractSocket::AbstractSocket()
			: sock(INVALID_SOCKET_VALUE),
			state(not_opened),
			err(0)
		{
		}



		AbstractSocket::AbstractSocket(SOCKET_TYPE sock_, SocketState state_, int err_)
			: sock(sock_),
			state(state_),
			err(err_)
		{
		}



		AbstractSocket::AbstractSocket(AbstractSocket && rhs) LOGGING_NOEXCEPT
			: AbstractSocket()
		{
			swap(rhs);
		}


		AbstractSocket::~AbstractSocket()
		{
			close();
		}



		//////////////////////////////////////////////////////////////////////////////
		// AbstractSocket methods
		//////////////////////////////////////////////////////////////////////////////

		void
			AbstractSocket::close()
		{
			if (sock != INVALID_SOCKET_VALUE)
			{
				closeSocket(sock);
				sock = INVALID_SOCKET_VALUE;
				state = not_opened;
			}
		}


		void
			AbstractSocket::shutdown()
		{
			if (sock != INVALID_SOCKET_VALUE)
				shutdownSocket(sock);
		}


		bool
			AbstractSocket::isOpen() const
		{
			return sock != INVALID_SOCKET_VALUE;
		}


		AbstractSocket &
			AbstractSocket::operator = (AbstractSocket && rhs) LOGGING_NOEXCEPT
		{
			swap(rhs);
			return *this;
		}


		void
			AbstractSocket::swap(AbstractSocket & rhs)
		{
			using std::swap;

			swap(sock, rhs.sock);
			swap(state, rhs.state);
			swap(err, rhs.err);
		}


		//////////////////////////////////////////////////////////////////////////////
		// Socket ctors and dtor
		//////////////////////////////////////////////////////////////////////////////

		Socket::Socket()
			: AbstractSocket()
		{ }


		Socket::Socket(const tstring& address, unsigned short port,
			bool udp /*= false*/, bool ipv6 /*= false */)
			: AbstractSocket()
		{
			sock = connectSocket(address, port, udp, ipv6, state);
			if (sock == INVALID_SOCKET_VALUE)
				goto error;

			if (!udp && setTCPNoDelay(sock, true) != 0)
				goto error;

			return;

		error:
			err = get_last_socket_error();
		}


		Socket::Socket(SOCKET_TYPE sock_, SocketState state_, int err_)
			: AbstractSocket(sock_, state_, err_)
		{ }


		Socket::Socket(Socket && other) LOGGING_NOEXCEPT
			: AbstractSocket(std::move(other))
		{ }


		Socket::~Socket()
		{ }


		Socket &
			Socket::operator = (Socket && other) LOGGING_NOEXCEPT
		{
			swap(other);
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////////
		// Socket methods
		//////////////////////////////////////////////////////////////////////////////

		bool
			Socket::read(SocketBuffer& buffer)
		{
			long retval = helpers::read(sock, buffer);
			if (retval <= 0) {
				close();
			}
			else {
				buffer.setSize(retval);
			}

			return (retval > 0);
		}



		bool
			Socket::write(const SocketBuffer& buffer)
		{
			long retval = helpers::write(sock, buffer);
			if (retval <= 0) {
				close();
			}

			return (retval > 0);
		}


		bool
			Socket::write(std::size_t bufferCount, SocketBuffer const * const * buffers)
		{
			long retval = helpers::write(sock, bufferCount, buffers);
			if (retval <= 0)
				close();

			return retval > 0;
		}


		bool
			Socket::write(const std::string & buffer)
		{
			long retval = helpers::write(sock, buffer);
			if (retval <= 0)
				close();

			return retval > 0;
		}


		//
		//
		//

		ServerSocket::ServerSocket(ServerSocket && other) LOGGING_NOEXCEPT
			: AbstractSocket(std::move(other))
		{
			interruptHandles[0] = -1;
			interruptHandles[1] = -1;
			interruptHandles.swap(other.interruptHandles);
		}


		ServerSocket &
			ServerSocket::operator = (ServerSocket && other) LOGGING_NOEXCEPT
		{
			swap(other);
			return *this;
		}


		void
			ServerSocket::swap(ServerSocket & other)
		{
			AbstractSocket::swap(other);
			interruptHandles.swap(other.interruptHandles);
		}


		//
		//
		//

		SOCKET_TYPE
			openSocket(unsigned short port, bool udp, bool ipv6, SocketState& state)
		{
			return openSocket(logging::internal::empty_str, port, udp, ipv6, state);
		}


	}
} // namespace logging { namespace helpers {
