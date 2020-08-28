#ifndef LOGGING_HELPERS_SOCKET_BUFFER_HEADER_
#define LOGGING_HELPERS_SOCKET_BUFFER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/tstring.h>


namespace logging {
	namespace helpers {

		/**
		 *
		 */
		class LOGGING_EXPORT SocketBuffer
		{
		public:
			explicit SocketBuffer(std::size_t max);
			virtual ~SocketBuffer();

			char *getBuffer() const { return buffer; }
			std::size_t getMaxSize() const { return maxsize; }
			std::size_t getSize() const { return size; }
			void setSize(std::size_t s) { size = s; }
			std::size_t getPos() const { return pos; }

			unsigned char readByte();
			unsigned short readShort();
			unsigned int readInt();
			tstring readString(unsigned char sizeOfChar);

			void appendByte(unsigned char val);
			void appendShort(unsigned short val);
			void appendInt(unsigned int val);
			void appendString(const tstring& str);
			void appendBuffer(const SocketBuffer& buffer);

		private:
			// Data
			std::size_t maxsize;
			std::size_t size;
			std::size_t pos;
			char *buffer;

			SocketBuffer(SocketBuffer const & rhs);
			SocketBuffer& operator= (SocketBuffer const& rhs);
		};

	} // end namespace helpers
} // end namespace logging

#endif // LOGGING_HELPERS_SOCKET_HEADER_
