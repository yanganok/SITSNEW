#include <cstring>
#include <limits>
#include <logging/helpers/socketbuffer.h>
#include <logging/helpers/loglog.h>

#if defined (LOGGING_HAVE_SYS_TYPES_H)
#include <sys/types.h>
#endif

#if !defined(_WIN32)
#  include <netdb.h>
#else
#  include <logging/config/windowsh-inc.h>
#endif

#if defined (LOGGING_HAVE_NETINET_IN_H)
#include <netinet/in.h>
#endif

#if defined (LOGGING_WITH_UNIT_TESTS)
#include <logging/catch.hpp>
#endif


namespace logging {
	namespace helpers {


		//////////////////////////////////////////////////////////////////////////////
		// SocketBuffer ctors and dtor
		//////////////////////////////////////////////////////////////////////////////

		SocketBuffer::SocketBuffer(std::size_t maxsize_)
			: maxsize(maxsize_),
			size(0),
			pos(0),
			buffer(new char[maxsize])
		{
		}


		SocketBuffer::~SocketBuffer()
		{
			delete[] buffer;
		}


		//////////////////////////////////////////////////////////////////////////////
		// SocketBuffer methods
		//////////////////////////////////////////////////////////////////////////////

		unsigned char
			SocketBuffer::readByte()
		{
			if (pos >= maxsize) {
				getLogLog().error(LOGGING_TEXT("SocketBuffer::readByte()- end of buffer reached"));
				return 0;
			}
			else if ((pos + sizeof(unsigned char)) > maxsize) {
				getLogLog().error(LOGGING_TEXT("SocketBuffer::readByte()- Attempt to read beyond end of buffer"));
				return 0;
			}

			unsigned char ret = static_cast<unsigned char>(buffer[pos]);
			pos += sizeof(unsigned char);

			return ret;
		}



		unsigned short
			SocketBuffer::readShort()
		{
			if (pos >= maxsize) {
				getLogLog().error(LOGGING_TEXT("SocketBuffer::readShort()- end of buffer reached"));
				return 0;
			}
			else if ((pos + sizeof(unsigned short)) > maxsize) {
				getLogLog().error(LOGGING_TEXT("SocketBuffer::readShort()- Attempt to read beyond end of buffer"));
				return 0;
			}

			unsigned short ret;
			std::memcpy(&ret, buffer + pos, sizeof(ret));
			ret = ntohs(ret);
			pos += sizeof(unsigned short);

			return ret;
		}



		unsigned int
			SocketBuffer::readInt()
		{
			if (pos >= maxsize) {
				getLogLog().error(LOGGING_TEXT("SocketBuffer::readInt()- end of buffer reached"));
				return 0;
			}
			else if ((pos + sizeof(unsigned int)) > maxsize) {
				getLogLog().error(LOGGING_TEXT("SocketBuffer::readInt()- Attempt to read beyond end of buffer"));
				return 0;
			}

			unsigned int ret;
			std::memcpy(&ret, buffer + pos, sizeof(ret));
			ret = ntohl(ret);
			pos += sizeof(unsigned int);

			return ret;
		}


		tstring
			SocketBuffer::readString(unsigned char sizeOfChar)
		{
			std::size_t strlen = readInt();
			std::size_t bufferLen = strlen * sizeOfChar;

			if (strlen == 0) {
				return tstring();
			}
			if (pos > maxsize) {
				getLogLog().error(LOGGING_TEXT("SocketBuffer::readString()- end of buffer reached"));
				return tstring();
			}

			if ((pos + bufferLen) > maxsize) {
				getLogLog().error(LOGGING_TEXT("SocketBuffer::readString()- Attempt to read beyond end of buffer"));
				bufferLen = (maxsize - 1) - pos;
				strlen = bufferLen / sizeOfChar;
			}

#ifndef UNICODE
			if (sizeOfChar == 1) {
				tstring ret(&buffer[pos], strlen);
				pos += strlen;
				return ret;
			}
			else if (sizeOfChar == 2) {
				tstring ret;
				for (tstring::size_type i = 0; i < strlen; ++i) {
					unsigned short tmp = readShort();
					ret += static_cast<char>(tmp < 256 ? tmp : ' ');
				}
				return ret;
			}
			else {
				getLogLog().error(LOGGING_TEXT("SocketBuffer::readString()- Invalid sizeOfChar!!!!"));
			}

#else /* UNICODE */
			if (sizeOfChar == 1) {
				std::string ret(&buffer[pos], strlen);
				pos += strlen;
				return towstring(ret);
			}
			else if (sizeOfChar == 2) {
				tstring ret;
				for (tstring::size_type i = 0; i < strlen; ++i) {
					ret += static_cast<tchar>(readShort());
				}
				return ret;
			}
			else {
				getLogLog().error(LOGGING_TEXT("SocketBuffer::readString()- Invalid sizeOfChar!!!!"));
			}
#endif

			return tstring();
		}



		void
			SocketBuffer::appendByte(unsigned char val)
		{
			if ((pos + sizeof(unsigned char)) > maxsize) {
				getLogLog().error(
					LOGGING_TEXT("SocketBuffer::appendByte()-")
					LOGGING_TEXT(" Attempt to write beyond end of buffer"),
					true);
			}

			buffer[pos] = static_cast<char>(val);
			pos += sizeof(unsigned char);
			size = pos;
		}



		void
			SocketBuffer::appendShort(unsigned short val)
		{
			if ((pos + sizeof(unsigned short)) > maxsize) {
				getLogLog().error(
					LOGGING_TEXT("SocketBuffer::appendShort()-")
					LOGGING_TEXT("Attempt to write beyond end of buffer"),
					true);
			}

			unsigned short s = htons(val);
			std::memcpy(buffer + pos, &s, sizeof(s));
			pos += sizeof(s);
			size = pos;
		}



		void
			SocketBuffer::appendInt(unsigned int val)
		{
			if ((pos + sizeof(unsigned int)) > maxsize) {
				getLogLog().error(
					LOGGING_TEXT("SocketBuffer::appendInt()-")
					LOGGING_TEXT(" Attempt to write beyond end of buffer"),
					true);
				return;
			}

			int i = htonl(val);
			std::memcpy(buffer + pos, &i, sizeof(i));
			pos += sizeof(i);
			size = pos;
		}



		void
			SocketBuffer::appendString(const tstring& str)
		{
			std::size_t const strlen = str.length();
			std::size_t const sizeOfChar = sizeof(tchar) == 1 ? 1 : 2;

			if ((pos + sizeof(unsigned int) + strlen * sizeOfChar) > maxsize)
			{
				getLogLog().error(
					LOGGING_TEXT("SocketBuffer::appendString()-")
					LOGGING_TEXT(" Attempt to write beyond end of buffer"),
					true);
				return;
			}

			appendInt(static_cast<unsigned>(strlen));
#ifndef UNICODE
			std::memcpy(&buffer[pos], str.data(), strlen);
			pos += strlen;
			size = pos;
#else
			for (tstring::size_type i = 0; i < strlen; ++i) {
				appendShort(static_cast<unsigned short>(str[i]));
			}
#endif
		}



		void
			SocketBuffer::appendBuffer(const SocketBuffer& buf)
		{
			if ((pos + buf.getSize()) > maxsize) {
				getLogLog().error(
					LOGGING_TEXT("SocketBuffer::appendBuffer()-")
					LOGGING_TEXT(" Attempt to write beyond end of buffer"),
					true);
				return;
			}

			std::memcpy(&buffer[pos], buf.buffer, buf.getSize());
			pos += buf.getSize();
			size = pos;
		}


#if defined (LOGGING_WITH_UNIT_TESTS)
		CATCH_TEST_CASE("SocketBuffer", "[sockets]")
		{
			static const std::size_t SMALL_BUFFER_SIZE = 4;
			SocketBuffer small_sb(SMALL_BUFFER_SIZE);

			CATCH_SECTION("new object is initialized")
			{
				CATCH_REQUIRE(small_sb.getPos() == 0);
				CATCH_REQUIRE(small_sb.getSize() == 0);
				CATCH_REQUIRE(small_sb.getMaxSize() == SMALL_BUFFER_SIZE);
				CATCH_REQUIRE(!!small_sb.getBuffer());
			}

			CATCH_SECTION("appending to buffer works")
			{
				small_sb.appendByte(1);
				CATCH_REQUIRE(small_sb.getPos() == 1);
				CATCH_REQUIRE(small_sb.getSize() == 1);
				CATCH_REQUIRE(small_sb.getMaxSize() == SMALL_BUFFER_SIZE);
			}

			CATCH_SECTION("exception is thrown on overflow ")
			{
				for (std::size_t i = 0; i != SMALL_BUFFER_SIZE; ++i)
					small_sb.appendByte(static_cast<unsigned char>(i));

				CATCH_REQUIRE_THROWS(small_sb.appendByte(1));
			}
		}
#endif


	}
} // namespace logging { namespace helpers {
