#include <logging/helpers/stringhelper.h>
#include <logging/helpers/loglog.h>

#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <cassert>
#include <vector>


namespace logging
{

	namespace helpers
	{


		void clear_mbstate(std::mbstate_t & mbs);


#if defined (LOGGING_WORKING_C_LOCALE)

		static
			void
			tostring_internal(std::string & result, wchar_t const * src, std::size_t size)
		{
			std::vector<char> result_buf(MB_CUR_MAX);

			wchar_t const * src_it = src;
			wchar_t const * const src_end_it = src + size;

			std::mbstate_t mbs;
			clear_mbstate(mbs);

			result.clear();
			result.reserve(size + size / 3 + 1);

			while (src_it != src_end_it)
			{
				std::size_t ret = std::wcrtomb(&result_buf[0], *src_it, &mbs);
				if (ret == static_cast<std::size_t>(-1))
				{
					result.push_back('?');
					clear_mbstate(mbs);
					++src_it;
				}
				else
				{
					result.append(result_buf.begin(), result_buf.begin() + ret);
					++src_it;
				}
			}
		}


		std::string
			tostring(const std::wstring & src)
		{
			std::string ret;
			tostring_internal(ret, src.c_str(), src.size());
			return ret;
		}


		std::string
			tostring(wchar_t const * src)
		{
			assert(src);
			std::string ret;
			tostring_internal(ret, src, std::wcslen(src));
			return ret;
		}


		static
			void
			towstring_internal(std::wstring & result, char const * src, std::size_t size)
		{
			char const * src_it = src;
			char const * const src_end_it = src + size;

			std::mbstate_t mbs;
			clear_mbstate(mbs);

			result.clear();
			result.reserve(size);

			while (src_it != src_end_it)
			{
				std::size_t const n = size - (src - src_it);
				wchar_t result_char;
				std::size_t ret = std::mbrtowc(&result_char, src_it, n, &mbs);
				if (ret > 0)
				{
					result.push_back(result_char);
					src_it += ret;
				}
				else
				{
					result.push_back(ret == 0 ? L'\0' : L'?');
					clear_mbstate(mbs);
					++src_it;
				}
			}
		}


		std::wstring
			towstring(const std::string& src)
		{
			std::wstring ret;
			towstring_internal(ret, src.c_str(), src.size());
			return ret;
		}


		std::wstring
			towstring(char const * src)
		{
			assert(src);
			std::wstring ret;
			towstring_internal(ret, src, std::strlen(src));
			return ret;
		}

#endif // LOGGING_WORKING_C_LOCALE

	} // namespace helpers

} // namespace logging
