#ifndef LOGGING_INTERNAL_SOCKET_H_
#define LOGGING_INTERNAL_SOCKET_H_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#if ! defined (INSIDE_LOGGING)
#  error "This header must not be be used outside logging' implementation files."
#endif

#if defined(_WIN32)
#include <logging/config/windowsh-inc.h>
#endif
#include <logging/helpers/socket.h>

#include <cerrno>
#ifdef LOGGING_HAVE_ERRNO_H
#include <errno.h>
#endif

#ifdef LOGGING_HAVE_UNISTD_H
#include <unistd.h>
#endif

#if defined (LOGGING_HAVE_NETDB_H)
#include <netdb.h>
#endif


namespace logging {

	namespace helpers {

#if defined(_WIN32)
		typedef SOCKET os_socket_type;
		os_socket_type const INVALID_OS_SOCKET_VALUE = INVALID_SOCKET;

		struct ADDRINFOT_deleter
		{
			void
				operator () (ADDRINFOA * ptr) const
			{
				FreeAddrInfoA(ptr);
			}

			void
				operator () (ADDRINFOW * ptr) const
			{
				FreeAddrInfoW(ptr);
			}
		};


		struct socket_closer
		{
			void
				operator () (SOCKET s)
			{
				if (s && s != INVALID_OS_SOCKET_VALUE)
				{
					DWORD const eno = WSAGetLastError();
					::closesocket(s);
					WSASetLastError(eno);
				}
			}
		};


#else
		typedef int os_socket_type;
		os_socket_type const INVALID_OS_SOCKET_VALUE = -1;


		struct addrinfo_deleter
		{
			void
				operator () (struct addrinfo * ptr) const
			{
				freeaddrinfo(ptr);
			}
		};


		struct socket_closer
		{
			void
				operator () (os_socket_type s)
			{
				if (s >= 0)
				{
					int const eno = errno;
					close(s);
					errno = eno;
				}
			}
		};

#endif


		struct socket_holder
		{
			os_socket_type sock;

			socket_holder()
				: sock(INVALID_OS_SOCKET_VALUE)
			{ }

			socket_holder(os_socket_type s)
				: sock(s)
			{ }

			~socket_holder()
			{
				socket_closer()(sock);
			}

			void
				reset(os_socket_type s = INVALID_OS_SOCKET_VALUE)
			{
				if (sock != INVALID_OS_SOCKET_VALUE)
					socket_closer()(sock);

				sock = s;
			}

			os_socket_type
				detach()
			{
				os_socket_type s = sock;
				sock = INVALID_OS_SOCKET_VALUE;
				return s;
			}

			socket_holder(socket_holder &&) = delete;
			socket_holder(socket_holder const &) = delete;

			socket_holder operator = (socket_holder &&) = delete;
			socket_holder operator = (socket_holder const &) = delete;
		};


		static inline
			os_socket_type
			to_os_socket(SOCKET_TYPE const & x)
		{
			return static_cast<os_socket_type>(x);
		}


		static inline
			SOCKET_TYPE
			to_LOGGING_socket(os_socket_type const & x)
		{
			return static_cast<SOCKET_TYPE>(x);
		}


		static inline
			void
			set_last_socket_error(int err)
		{
			errno = err;
		}


		static inline
			int
			get_last_socket_error()
		{
			return errno;
		}


	} // namespace helpers {

} // namespace logging {


#endif // LOGGING_INTERNAL_SOCKET_H_
