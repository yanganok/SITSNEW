#include <logging/config.hxx>

#include <cstring>
#if defined (UNICODE)
#  include <cwctype>
#else
#  include <cctype>
#endif
#if defined (LOGGING_HAVE_CODECVT_UTF8_FACET) \
    || defined (LOGGING_HAVE_CODECVT_UTF16_FACET) \
    || defined (LOGGING_HAVE_CODECVT_UTF32_FACET)
#  include <codecvt>
#endif
#include <locale>
#include <fstream>
#include <sstream>
#include <logging/streams.h>
#include <logging/fstreams.h>
#include <logging/helpers/stringhelper.h>
#include <logging/helpers/property.h>
#include <logging/internal/internal.h>
#include <logging/internal/env.h>
#include <logging/helpers/loglog.h>

#if defined (LOGGING_WITH_UNIT_TESTS)
#include <logging/catch.hpp>
#endif


namespace logging {
	namespace helpers {


		const tchar Properties::PROPERTIES_COMMENT_CHAR = LOGGING_TEXT('#');


		namespace
		{


			static
				int
				is_space(tchar ch)
			{
#if defined (UNICODE)
				return std::iswspace(ch);
#else
				return std::isspace(static_cast<unsigned char>(ch));
#endif
			}


			static
				void
				trim_leading_ws(tstring & str)
			{
				tstring::iterator it = str.begin();
				for (; it != str.end(); ++it)
				{
					if (!is_space(*it))
						break;
				}
				str.erase(str.begin(), it);
			}


			static
				void
				trim_trailing_ws(tstring & str)
			{
				tstring::reverse_iterator rit = str.rbegin();
				for (; rit != str.rend(); ++rit)
				{
					if (!is_space(*rit))
						break;
				}
				str.erase(rit.base(), str.end());
			}


			static
				void
				trim_ws(tstring & str)
			{
				trim_trailing_ws(str);
				trim_leading_ws(str);
			}


#if defined (LOGGING_WITH_UNIT_TESTS)
			CATCH_TEST_CASE("String trimming", "[strings][properties]")
			{
				CATCH_SECTION("trim trailing whitespace")
				{
					tstring trailing_ws(LOGGING_TEXT("abcd \t\n\v\f\r"));
					trim_trailing_ws(trailing_ws);
					CATCH_REQUIRE(trailing_ws == LOGGING_TEXT("abcd"));
				}

				CATCH_SECTION("trim leading whitespace")
				{
					tstring leading_ws(LOGGING_TEXT(" \t\n\v\f\rabcd"));
					trim_leading_ws(leading_ws);
					CATCH_REQUIRE(leading_ws == LOGGING_TEXT("abcd"));
				}

				CATCH_SECTION("trim all whitespace")
				{
					tstring ws(LOGGING_TEXT(" \t\n\v\f\rabcd \t\n\v\f\r"));
					trim_ws(ws);
					CATCH_REQUIRE(ws == LOGGING_TEXT("abcd"));
				}
			}
#endif


			void
				imbue_file_from_flags(tistream & file, unsigned flags)
			{
				switch (flags & (Properties::fEncodingMask << Properties::fEncodingShift))
				{
#if defined (LOGGING_HAVE_CODECVT_UTF8_FACET) && defined (UNICODE)
				case Properties::fUTF8:
					file.imbue(
						std::locale(file.getloc(),
							new std::codecvt_utf8<tchar, 0x10FFFF,
							static_cast<std::codecvt_mode>(std::consume_header | std::little_endian)>));
					break;
#endif

#if defined (LOGGING_HAVE_CODECVT_UTF16_FACET) && defined (UNICODE)
				case Properties::fUTF16:
					file.imbue(
						std::locale(file.getloc(),
							new std::codecvt_utf16<tchar, 0x10FFFF,
							static_cast<std::codecvt_mode>(std::consume_header | std::little_endian)>));
					break;

#elif defined (UNICODE) && defined (WIN32)
				case Properties::fUTF16:
					file.imbue(
						std::locale(file.getloc(),
							// TODO: This should actually be a custom "null" facet
							// that just copies the chars to wchar_t buffer.
							new std::codecvt<wchar_t, char, std::mbstate_t>));
					break;

#endif

#if defined (LOGGING_HAVE_CODECVT_UTF32_FACET) && defined (UNICODE)
				case Properties::fUTF32:
					file.imbue(
						std::locale(file.getloc(),
							new std::codecvt_utf32<tchar, 0x10FFFF,
							static_cast<std::codecvt_mode>(std::consume_header | std::little_endian)>));
					break;
#endif

				case Properties::fUnspecEncoding:;
				default:
					// Do nothing.
					;
				}
			}


		} // namespace



		///////////////////////////////////////////////////////////////////////////////
		// Properties ctors and dtor
		///////////////////////////////////////////////////////////////////////////////

		Properties::Properties()
			: flags(0)
		{
		}



		Properties::Properties(tistream& input)
			: flags(0)
		{
			init(input);
		}



		Properties::Properties(const tstring& inputFile, unsigned f)
			: flags(f)
		{
			if (inputFile.empty())
				return;

			tifstream file;
			imbue_file_from_flags(file, flags);

			file.open(LOGGING_FSTREAM_PREFERED_FILE_NAME(inputFile).c_str(),
				std::ios::binary);
			if (!file.good())
				helpers::getLogLog().error(LOGGING_TEXT("could not open file ")
					+ inputFile);

			init(file);
		}



		void
			Properties::init(tistream& input)
		{
			if (!input)
				return;

			tstring buffer;
			while (std::getline(input, buffer))
			{
				trim_leading_ws(buffer);

				tstring::size_type const buffLen = buffer.size();
				if (buffLen == 0 || buffer[0] == PROPERTIES_COMMENT_CHAR)
					continue;

				// Check if we have a trailing \r because we are
				// reading a properties file produced on Windows.
				if (buffer[buffLen - 1] == LOGGING_TEXT('\r'))
					// Remove trailing 'Windows' \r.
					buffer.resize(buffLen - 1);

				if (buffer.size() >= 7 + 1 + 1
					&& buffer.compare(0, 7, LOGGING_TEXT("include")) == 0
					&& is_space(buffer[7]))
				{
					tstring included(buffer, 8);
					trim_ws(included);

					tifstream file;
					imbue_file_from_flags(file, flags);

					file.open(LOGGING_FSTREAM_PREFERED_FILE_NAME(included).c_str(),
						std::ios::binary);
					if (!file.good())
						helpers::getLogLog().error(
							LOGGING_TEXT("could not open file ") + included);

					init(file);
				}
				else
				{
					tstring::size_type const idx = buffer.find(LOGGING_TEXT('='));
					if (idx != tstring::npos)
					{
						tstring key = buffer.substr(0, idx);
						tstring value = buffer.substr(idx + 1);
						trim_trailing_ws(key);
						trim_ws(value);
						setProperty(key, value);
					}
				}
			}
		}



		Properties::~Properties()
		{
		}



		///////////////////////////////////////////////////////////////////////////////
		// helpers::Properties public methods
		///////////////////////////////////////////////////////////////////////////////


		bool
			Properties::exists(const logging::tstring& key) const
		{
			return data.find(key) != data.end();
		}


		bool
			Properties::exists(tchar const * key) const
		{
			return data.find(key) != data.end();
		}


		tstring const &
			Properties::getProperty(const tstring& key) const
		{
			return get_property_worker(key);
		}


		logging::tstring const &
			Properties::getProperty(tchar const * key) const
		{
			return get_property_worker(key);
		}


		tstring
			Properties::getProperty(const tstring& key, const tstring& defaultVal) const
		{
			StringMap::const_iterator it(data.find(key));
			if (it == data.end())
				return defaultVal;
			else
				return it->second;
		}


		std::vector<tstring>
			Properties::propertyNames() const
		{
			std::vector<tstring> tmp;
			tmp.reserve(data.size());
			for (auto const & kv : data)
				tmp.push_back(kv.first);

			return tmp;
		}



		void
			Properties::setProperty(const logging::tstring& key,
				const logging::tstring& value)
		{
			data[key] = value;
		}


		bool
			Properties::removeProperty(const logging::tstring& key)
		{
			return data.erase(key) > 0;
		}


		Properties
			Properties::getPropertySubset(const logging::tstring& prefix) const
		{
			Properties ret;
			auto const prefix_len = prefix.size();
			std::vector<tstring> keys = propertyNames();
			for (tstring const & key : keys)
			{
				int result = key.compare(0, prefix_len, prefix);
				if (result == 0)
					ret.setProperty(key.substr(prefix_len), getProperty(key));
			}

			return ret;
		}


		bool
			Properties::getInt(int & val, logging::tstring const & key) const
		{
			return get_type_val_worker(val, key);
		}


		bool
			Properties::getUInt(unsigned & val, logging::tstring const & key) const
		{
			return get_type_val_worker(val, key);
		}


		bool
			Properties::getLong(long & val, logging::tstring const & key) const
		{
			return get_type_val_worker(val, key);
		}


		bool
			Properties::getULong(unsigned long & val, logging::tstring const & key) const
		{
			return get_type_val_worker(val, key);
		}


		bool
			Properties::getBool(bool & val, logging::tstring const & key) const
		{
			if (!exists(key))
				return false;

			logging::tstring const & prop_val = getProperty(key);
			return internal::parse_bool(val, prop_val);
		}


		bool
			Properties::getString(logging::tstring & val, logging::tstring const & key)
			const
		{
			StringMap::const_iterator it(data.find(key));
			if (it == data.end())
				return false;

			val = it->second;
			return true;
		}


		template <typename StringType>
		logging::tstring const &
			Properties::get_property_worker(StringType const & key) const
		{
			StringMap::const_iterator it(data.find(key));
			if (it == data.end())
				return logging::internal::empty_str;
			else
				return it->second;
		}


		template <typename ValType>
		bool
			Properties::get_type_val_worker(ValType & val, logging::tstring const & key)
			const
		{
			if (!exists(key))
				return false;

			logging::tstring const & prop_val = getProperty(key);
			logging::tistringstream iss(prop_val);
			ValType tmp_val;
			tchar ch;

			iss >> tmp_val;
			if (!iss)
				return false;
			iss >> ch;
			if (iss)
				return false;

			val = tmp_val;
			return true;
		}


#if defined (LOGGING_WITH_UNIT_TESTS)
		CATCH_TEST_CASE("Properties", "[properties]")
		{
			static tchar const PROP_ABC[] = LOGGING_TEXT("a.b.c");
			Properties props;

			CATCH_SECTION("new object is empty")
			{
				CATCH_REQUIRE(props.size() == 0);
			}

			CATCH_SECTION("added property can be retrieved")
			{
				props.setProperty(PROP_ABC, LOGGING_TEXT("true"));
				CATCH_REQUIRE(props.exists(PROP_ABC));
				CATCH_REQUIRE(props.exists(LOGGING_C_STR_TO_TSTRING(PROP_ABC)));
				CATCH_REQUIRE(props.getProperty(PROP_ABC)
					== LOGGING_TEXT("true"));
			}

			CATCH_SECTION("type conversions work")
			{
				bool bool_;
				int int_;
				unsigned int uint;
				long long_;
				unsigned long ulong;

				tistringstream iss(
					LOGGING_TEXT("bool=true\r\n")
					LOGGING_TEXT("bool1=1\n")
					LOGGING_TEXT("int=-1\n")
					LOGGING_TEXT("uint=42\n")
					LOGGING_TEXT("long=-65537\n")
					LOGGING_TEXT("ulong=65537")
				);
				Properties from_stream(iss);

				CATCH_REQUIRE(from_stream.getBool(bool_, LOGGING_TEXT("bool")));
				CATCH_REQUIRE(bool_);
				CATCH_REQUIRE(from_stream.getBool(bool_, LOGGING_TEXT("bool1")));
				CATCH_REQUIRE(bool_);
				CATCH_REQUIRE(from_stream.getInt(int_, LOGGING_TEXT("int")));
				CATCH_REQUIRE(int_ == -1);
				CATCH_REQUIRE(from_stream.getUInt(uint, LOGGING_TEXT("uint")));
				CATCH_REQUIRE(uint == 42);
				CATCH_REQUIRE(from_stream.getLong(long_, LOGGING_TEXT("long")));
				CATCH_REQUIRE(long_ == -65537);
				CATCH_REQUIRE(from_stream.getULong(ulong, LOGGING_TEXT("ulong")));
				CATCH_REQUIRE(ulong == 65537);
			}

			CATCH_SECTION("remove property")
			{
				props.setProperty(PROP_ABC, LOGGING_TEXT("true"));
				CATCH_REQUIRE(props.exists(PROP_ABC));
				props.removeProperty(PROP_ABC);
				CATCH_REQUIRE(!props.exists(PROP_ABC));
			}

			CATCH_SECTION("retrieve property names")
			{
				props.setProperty(PROP_ABC, LOGGING_TEXT("true"));
				static tchar const PROP_SECOND[] = LOGGING_TEXT("second");
				props.setProperty(LOGGING_TEXT("second"), LOGGING_TEXT("false"));
				std::vector<logging::tstring> names(props.propertyNames());
				CATCH_REQUIRE(std::find(std::begin(names), std::end(names),
					PROP_ABC) != std::end(names));
				CATCH_REQUIRE(std::find(std::begin(names), std::end(names),
					PROP_SECOND) != std::end(names));
			}
		}
#endif


	}
} // namespace logging { namespace helpers {
