#ifndef LOGGING_TSTRING_HEADER_
#define LOGGING_TSTRING_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <string>
#include <logging/tchar.h>

namespace logging
{

	typedef std::basic_string<tchar> tstring;


	namespace helpers
	{

		inline
			std::string
			tostring(char const * str)
		{
			return std::string(str);
		}

		inline
			std::string
			tostring(std::string const & str)
		{
			return str;
		}

		inline
			std::string const &
			tostring(std::string & str)
		{
			return str;
		}

		inline
			std::string
			tostring(std::string && str)
		{
			return std::move(str);
		}


		inline
			std::wstring
			towstring(wchar_t const * str)
		{
			return std::wstring(str);
		}

		inline
			std::wstring
			towstring(std::wstring const & str)
		{
			return str;
		}

		inline
			std::wstring const &
			towstring(std::wstring & str)
		{
			return str;
		}

		inline
			std::wstring
			towstring(std::wstring && str)
		{
			return std::move(str);
		}


		LOGGING_EXPORT std::string tostring(const std::wstring&);
		LOGGING_EXPORT std::string tostring(wchar_t const *);

		LOGGING_EXPORT std::wstring towstring(const std::string&);
		LOGGING_EXPORT std::wstring towstring(char const *);

	} // namespace helpers

#ifdef UNICODE

#define LOGGING_C_STR_TO_TSTRING(STRING) logging::helpers::towstring(STRING)
#define LOGGING_STRING_TO_TSTRING(STRING) logging::helpers::towstring(STRING)
#define LOGGING_TSTRING_TO_STRING(STRING) logging::helpers::tostring(STRING)

#else // UNICODE

#define LOGGING_C_STR_TO_TSTRING(STRING) (std::string(STRING))
#define LOGGING_STRING_TO_TSTRING(STRING) STRING
#define LOGGING_TSTRING_TO_STRING(STRING) STRING

#endif // UNICODE

} // namespace logging


#endif // LOGGING_TSTRING_HEADER_
