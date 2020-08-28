#include <logging/layout.h>
#include <logging/helpers/loglog.h>
#include <logging/helpers/timehelper.h>
#include <logging/helpers/stringhelper.h>
#include <logging/helpers/socket.h>
#include <logging/helpers/property.h>
#include <logging/spi/loggingevent.h>
#include <logging/internal/internal.h>
#include <logging/internal/env.h>
#include <limits>
#include <cstdlib>

#if defined (LOGGING_WITH_UNIT_TESTS)
#include <logging/catch.hpp>
#endif


namespace
{


	static
		logging::tstring
		get_basename(const logging::tstring& filename)
	{
#if defined(_WIN32)
		logging::tstring const dir_sep(LOGGING_TEXT("\\/"));
#else
		logging::tchar const dir_sep(LOGGING_TEXT('/'));
#endif

		logging::tstring::size_type pos = filename.find_last_of(dir_sep);
		if (pos != logging::tstring::npos)
			return filename.substr(pos + 1);
		else
			return filename;
	}


} // namespace


namespace logging
{

	static tchar const ESCAPE_CHAR = LOGGING_TEXT('%');

	extern void formatRelativeTimestamp(logging::tostream & output,
		logging::spi::InternalLoggingEvent const & event);


	namespace pattern
	{


		/**
		 * This is used by PatternConverter class to inform them how to format
		 * their output.
		 */
		struct FormattingInfo {
			int minLen;
			std::size_t maxLen;
			bool leftAlign : 1;
			bool trimStart : 1;
			FormattingInfo() { reset(); }

			void reset();
			void dump(helpers::LogLog&);
		};



		/**
		 * This is the base class of all "Converter" classes that format a
		 * field of InternalLoggingEvent objects.  In fact, the PatternLayout
		 * class simply uses an array of PatternConverter objects to format
		 * and append a logging event.
		 */
		class PatternConverter
		{
		public:
			explicit PatternConverter(const FormattingInfo& info);
			virtual ~PatternConverter() {}
			void formatAndAppend(tostream& output,
				const spi::InternalLoggingEvent& event);

			virtual void convert(tstring & result,
				const spi::InternalLoggingEvent& event) = 0;

		private:
			int minLen;
			std::size_t maxLen;
			bool leftAlign : 1;
			bool trimStart : 1;
		};


		typedef std::vector<std::unique_ptr<pattern::PatternConverter> >
			PatternConverterList;


		/**
		 * This PatternConverter returns a constant string.
		 */
		class LiteralPatternConverter : public PatternConverter
		{
		public:
			LiteralPatternConverter();
			explicit LiteralPatternConverter(const tstring& str);
			virtual void convert(tstring & result,
				const spi::InternalLoggingEvent&)
			{
				result = str;
			}

		private:
			tstring str;
		};


		/**
		 * This PatternConverter is used to format most of the "simple" fields
		 * found in the InternalLoggingEvent object.
		 */
		class BasicPatternConverter
			: public PatternConverter
		{
		public:
			enum Type {
				THREAD_CONVERTER,
				THREAD2_CONVERTER,
				PROCESS_CONVERTER,
				LOGLEVEL_CONVERTER,
				NDC_CONVERTER,
				MESSAGE_CONVERTER,
				NEWLINE_CONVERTER,
				BASENAME_CONVERTER,
				FILE_CONVERTER,
				LINE_CONVERTER,
				FULL_LOCATION_CONVERTER,
				FUNCTION_CONVERTER
			};
			BasicPatternConverter(const FormattingInfo& info, Type type);
			virtual void convert(tstring & result,
				const spi::InternalLoggingEvent& event);

		private:
			// Disable copy
			BasicPatternConverter(const BasicPatternConverter&);
			BasicPatternConverter& operator=(BasicPatternConverter&);

			LogLevelManager& llmCache;
			Type type;
		};



		/**
		 * This PatternConverter is used to format the Logger field found in
		 * the InternalLoggingEvent object.
		 */
		class LoggerPatternConverter : public PatternConverter {
		public:
			LoggerPatternConverter(const FormattingInfo& info, int precision);
			virtual void convert(tstring & result,
				const spi::InternalLoggingEvent& event);

		private:
			int precision;
		};



		/**
		 * This PatternConverter is used to format the timestamp field found in
		 * the InternalLoggingEvent object.  It will be formatted according to
		 * the specified "pattern".
		 */
		class DatePatternConverter : public PatternConverter {
		public:
			DatePatternConverter(const FormattingInfo& info,
				const tstring& pattern,
				bool use_gmtime);
			virtual void convert(tstring & result,
				const spi::InternalLoggingEvent& event);

		private:
			bool use_gmtime;
			tstring format;
		};


		/**
		 * This PatternConverter is used to format an environment variable
		 */
		class EnvPatternConverter : public PatternConverter {
		public:
			EnvPatternConverter(const FormattingInfo& info,
				const logging::tstring& env);
			virtual void convert(tstring & result,
				const spi::InternalLoggingEvent& event);

		private:
			logging::tstring envKey;
		};


		//! This pattern is used to format miliseconds since process start.
		class RelativeTimestampConverter : public PatternConverter {
		public:
			RelativeTimestampConverter(const FormattingInfo& info);
			virtual void convert(tstring & result,
				const spi::InternalLoggingEvent& event);
		};


		/**
		 * This PatternConverter is used to format the hostname field.
		 */
		class HostnamePatternConverter : public PatternConverter {
		public:
			HostnamePatternConverter(const FormattingInfo& info, bool fqdn);
			virtual void convert(tstring & result,
				const spi::InternalLoggingEvent& event);

		private:
			tstring hostname_;
		};


		/**
		 * This PatternConverter is used to format the MDC field found in
		 * the InternalLoggingEvent object, optionally limited to
		 * \c k Mapped diagnostic context key.
		 */
		class MDCPatternConverter
			: public PatternConverter
		{
		public:
			MDCPatternConverter(const FormattingInfo& info, tstring const & k);
			virtual void convert(tstring & result,
				const spi::InternalLoggingEvent& event);

		private:
			tstring key;
		};


		/**
		 * This PatternConverter is used to format the NDC field found in
		 * the InternalLoggingEvent object, optionally limited to
		 * \c precision levels (using space to separate levels).
		 */
		class NDCPatternConverter : public PatternConverter {
		public:
			NDCPatternConverter(const FormattingInfo& info, int precision);
			virtual void convert(tstring & result,
				const spi::InternalLoggingEvent& event);

		private:
			int precision;
		};



		/**
		 * This class parses a "pattern" string into an array of
		 * PatternConverter objects.
		 * <p>
		 * @see PatternLayout for the formatting of the "pattern" string.
		 */
		class PatternParser
		{
		public:
			PatternParser(const tstring& pattern, unsigned ndcMaxDepth);
			PatternConverterList parse();

		private:
			// Types
			enum ParserState {
				LITERAL_STATE,
				CONVERTER_STATE,
				DOT_STATE,
				MIN_STATE,
				MAX_STATE
			};

			// Methods
			tstring extractOption();
			int extractPrecisionOption();
			void finalizeConverter(tchar c);

			// Data
			tstring pattern;
			FormattingInfo formattingInfo;
			PatternConverterList list;
			ParserState state;
			tstring::size_type pos;
			tstring currentLiteral;
			unsigned ndcMaxDepth;
		};


		////////////////////////////////////////////////
		// FormattingInfo methods:
		////////////////////////////////////////////////

		void
			FormattingInfo::reset() {
			minLen = -1;
			maxLen = std::numeric_limits<std::size_t>::max();
			leftAlign = false;
			trimStart = true;
		}


		void
			FormattingInfo::dump(helpers::LogLog& loglog) {
			tostringstream buf;
			buf << LOGGING_TEXT("min=") << minLen
				<< LOGGING_TEXT(", max=") << maxLen
				<< LOGGING_TEXT(", leftAlign=") << std::boolalpha << leftAlign
				<< LOGGING_TEXT(", trimStart=") << std::boolalpha << trimStart;
			loglog.debug(buf.str());
		}




		////////////////////////////////////////////////
		// PatternConverter methods:
		////////////////////////////////////////////////

		PatternConverter::PatternConverter(const FormattingInfo& i)
		{
			minLen = i.minLen;
			maxLen = i.maxLen;
			leftAlign = i.leftAlign;
			trimStart = i.trimStart;
		}



		void
			PatternConverter::formatAndAppend(
				tostream& output, const spi::InternalLoggingEvent& event)
		{
			tstring & s = internal::get_ptd()->faa_str;
			convert(s, event);
			std::size_t len = s.length();

			if (len > maxLen)
			{
				if (trimStart)
					output << s.substr(len - maxLen);
				else
					output << s.substr(0, maxLen);
			}
			else if (static_cast<int>(len) < minLen)
			{
				std::ios_base::fmtflags const original_flags = output.flags();
				tchar const fill = output.fill(LOGGING_TEXT(' '));
				output.setf(leftAlign ? std::ios_base::left : std::ios_base::right,
					std::ios_base::adjustfield);
				output.width(minLen);
				output << s;
				output.fill(fill);
				output.flags(original_flags);
			}
			else
				output << s;
		}



		////////////////////////////////////////////////
		// LiteralPatternConverter methods:
		////////////////////////////////////////////////

		LiteralPatternConverter::LiteralPatternConverter()
			: PatternConverter(FormattingInfo())
			, str()
		{ }


		LiteralPatternConverter::LiteralPatternConverter(
			const tstring& str_)
			: PatternConverter(FormattingInfo())
			, str(str_)
		{
		}



		////////////////////////////////////////////////
		// BasicPatternConverter methods:
		////////////////////////////////////////////////

		BasicPatternConverter::BasicPatternConverter(
			const FormattingInfo& info, Type type_)
			: PatternConverter(info)
			, llmCache(getLogLevelManager())
			, type(type_)
		{
		}



		void
			BasicPatternConverter::convert(tstring & result,
				const spi::InternalLoggingEvent& event)
		{
			switch (type)
			{
			case LOGLEVEL_CONVERTER:
				result = llmCache.toString(event.getLogLevel());
				return;

			case BASENAME_CONVERTER:
				result = get_basename(event.getFile());
				return;

			case PROCESS_CONVERTER:
				helpers::convertIntegerToString(result, internal::get_process_id());
				return;

			case NDC_CONVERTER:
				result = event.getNDC();
				return;

			case MESSAGE_CONVERTER:
				result = event.getMessage();
				return;

			case NEWLINE_CONVERTER:
				result = LOGGING_TEXT("\n");
				return;

			case FILE_CONVERTER:
				result = event.getFile();
				return;

			case THREAD_CONVERTER:
				result = event.getThread();
				return;

			case THREAD2_CONVERTER:
				result = event.getThread2();
				return;

			case LINE_CONVERTER:
			{
				if (event.getLine() != -1)
					helpers::convertIntegerToString(result, event.getLine());
				else
					result.clear();
				return;
			}

			case FULL_LOCATION_CONVERTER:
			{
				tstring const & file = event.getFile();
				if (!file.empty())
				{
					result = file;
					result += LOGGING_TEXT(":");
					result += helpers::convertIntegerToString(event.getLine());
				}
				else
					result = LOGGING_TEXT(":");
				return;
			}

			case FUNCTION_CONVERTER:
				result = event.getFunction();
				return;
			}

			result = LOGGING_TEXT("INTERNAL LOGGING ERROR");
		}



		////////////////////////////////////////////////
		// LoggerPatternConverter methods:
		////////////////////////////////////////////////

		LoggerPatternConverter::LoggerPatternConverter(
			const FormattingInfo& info, int prec)
			: PatternConverter(info)
			, precision(prec)
		{
		}



		void
			LoggerPatternConverter::convert(tstring & result,
				const spi::InternalLoggingEvent& event)
		{
			const tstring& name = event.getLoggerName();
			if (precision <= 0) {
				result = name;
			}
			else {
				auto len = name.length();

				// We substract 1 from 'len' when assigning to 'end' to avoid out of
				// bounds exception in return r.substring(end+1, len). This can happen
				// if precision is 1 and the logger name ends with a dot.
				auto end = len - 1;
				for (int i = precision; i > 0; --i)
				{
					end = name.rfind(LOGGING_TEXT('.'), end - 1);
					if (end == tstring::npos) {
						result = name;
						return;
					}
				}
				result.assign(name, end + 1, tstring::npos);
			}
		}



		////////////////////////////////////////////////
		// DatePatternConverter methods:
		////////////////////////////////////////////////


		DatePatternConverter::DatePatternConverter(
			const FormattingInfo& info, const tstring& pattern,
			bool use_gmtime_)
			: PatternConverter(info)
			, use_gmtime(use_gmtime_)
			, format(pattern)
		{
		}



		void
			DatePatternConverter::convert(tstring & result,
				const spi::InternalLoggingEvent& event)
		{
			result = helpers::getFormattedTime(format, event.getTimestamp(),
				use_gmtime);
		}


		////////////////////////////////////////////////
		// EnvPatternConverter methods:
		////////////////////////////////////////////////


		EnvPatternConverter::EnvPatternConverter(
			const FormattingInfo& info, const tstring& env)
			: PatternConverter(info)
			, envKey(env)
		{ }


		void
			EnvPatternConverter::convert(tstring & result,
				const spi::InternalLoggingEvent&)
		{
			if (!internal::get_env_var(result, envKey))
			{
				// Variable doesn't exist, return empty string.
				result.clear();
			}
		}


		//
		//
		//

		RelativeTimestampConverter::RelativeTimestampConverter(FormattingInfo const & info)
			: PatternConverter(info)
		{ }


		void
			RelativeTimestampConverter::convert(tstring & result,
				spi::InternalLoggingEvent const & event)
		{
			tostringstream & oss = internal::get_ptd()->layout_oss;
			detail::clear_tostringstream(oss);
			logging::formatRelativeTimestamp(oss, event);
			result = oss.str();
		}


		////////////////////////////////////////////////
		// HostnamePatternConverter methods:
		////////////////////////////////////////////////

		HostnamePatternConverter::HostnamePatternConverter(
			const FormattingInfo& info, bool fqdn)
			: PatternConverter(info)
			, hostname_(helpers::getHostname(fqdn))
		{ }


		void
			HostnamePatternConverter::convert(
				tstring & result, const spi::InternalLoggingEvent&)
		{
			result = hostname_;
		}



		////////////////////////////////////////////////
		// MDCPatternConverter methods:
		////////////////////////////////////////////////

		logging::pattern::MDCPatternConverter::MDCPatternConverter(
			const FormattingInfo& info, tstring const & k)
			: PatternConverter(info)
			, key(k)
		{ }


		void
			logging::pattern::MDCPatternConverter::convert(tstring & result,
				const spi::InternalLoggingEvent& event)
		{
			if (!key.empty())
			{
				result = event.getMDC(key);
			}
			else
			{
				result.clear();

				MappedDiagnosticContextMap const & mdcMap = event.getMDCCopy();
				for (auto const & kv : mdcMap)
				{
					tstring const & name = kv.first;
					tstring const & value = kv.second;

					result += LOGGING_TEXT("{");
					result += name;
					result += LOGGING_TEXT(", ");
					result += value;
					result += LOGGING_TEXT("}");

				}
			}
		}


		////////////////////////////////////////////////
		// NDCPatternConverter methods:
		////////////////////////////////////////////////

		logging::pattern::NDCPatternConverter::NDCPatternConverter(
			const FormattingInfo& info, int precision_)
			: PatternConverter(info)
			, precision(precision_)
		{ }


		void
			logging::pattern::NDCPatternConverter::convert(tstring & result,
				const spi::InternalLoggingEvent& event)
		{
			const logging::tstring& text = event.getNDC();
			if (precision <= 0)
				result = text;
			else
			{
				tstring::size_type p = text.find(LOGGING_TEXT(' '));
				for (int i = 1; i < precision && p != tstring::npos; ++i)
					p = text.find(LOGGING_TEXT(' '), p + 1);

				result.assign(text, 0, p);
			}
		}



		////////////////////////////////////////////////
		// PatternParser methods:
		////////////////////////////////////////////////

		PatternParser::PatternParser(
			const tstring& pattern_, unsigned ndcMaxDepth_)
			: pattern(pattern_)
			, state(LITERAL_STATE)
			, pos(0)
			, ndcMaxDepth(ndcMaxDepth_)
		{
		}



		tstring
			PatternParser::extractOption()
		{
			tstring r;

			if ((pos < pattern.length())
				&& (pattern[pos] == LOGGING_TEXT('{')))
			{
				tstring::size_type end = pattern.find_first_of(LOGGING_TEXT('}'), pos);
				if (end != tstring::npos) {
					r.assign(pattern, pos + 1, end - pos - 1);
					pos = end + 1;
					return r;
				}
				else {
					logging::tostringstream buf;
					buf << LOGGING_TEXT("No matching '}' found in conversion pattern string \"")
						<< pattern
						<< LOGGING_TEXT("\"");
					helpers::getLogLog().error(buf.str());
					pos = pattern.length();
				}
			}

			return r;
		}


		int
			PatternParser::extractPrecisionOption()
		{
			tstring opt = extractOption();
			int r = 0;
			if (!opt.empty())
				r = std::atoi(LOGGING_TSTRING_TO_STRING(opt).c_str());

			return r;
		}



		PatternConverterList
			PatternParser::parse()
		{
			pos = 0;
			while (pos < pattern.length()) {
				tchar const c = pattern[pos++];
				switch (state) {
				case LITERAL_STATE:
					// In literal state, the last char is always a literal.
					if (pos == pattern.length()) {
						currentLiteral += c;
						continue;
					}
					if (c == ESCAPE_CHAR) {
						// peek at the next char.
						switch (pattern[pos]) {
						case ESCAPE_CHAR:
							currentLiteral += c;
							pos++; // move pointer
							break;
						default:
							if (!currentLiteral.empty()) {
								list.push_back
								(std::unique_ptr<PatternConverter>(
									new LiteralPatternConverter(currentLiteral)));
								//getLogLog().debug("Parsed LITERAL converter: \""
								//                  +currentLiteral+"\".");
							}
							currentLiteral.resize(0);
							currentLiteral += c; // append %
							state = CONVERTER_STATE;
							formattingInfo.reset();
						}
					}
					else {
						currentLiteral += c;
					}
					break;

				case CONVERTER_STATE:
					currentLiteral += c;
					switch (c) {
					case LOGGING_TEXT('-'):
						formattingInfo.leftAlign = true;
						break;
					case LOGGING_TEXT('.'):
						state = DOT_STATE;
						break;
					default:
						if (c >= LOGGING_TEXT('0') && c <= LOGGING_TEXT('9')) {
							formattingInfo.minLen = c - LOGGING_TEXT('0');
							state = MIN_STATE;
						}
						else {
							finalizeConverter(c);
						}
					} // switch
					break;

				case MIN_STATE:
					currentLiteral += c;
					if (c >= LOGGING_TEXT('0') && c <= LOGGING_TEXT('9')) {
						formattingInfo.minLen = formattingInfo.minLen * 10 + (c - LOGGING_TEXT('0'));
					}
					else if (c == LOGGING_TEXT('.')) {
						state = DOT_STATE;
					}
					else {
						finalizeConverter(c);
					}
					break;

				case DOT_STATE:
					currentLiteral += c;
					if (c == LOGGING_TEXT('-'))
						formattingInfo.trimStart = false;
					else if (c >= LOGGING_TEXT('0') && c <= LOGGING_TEXT('9')) {
						formattingInfo.maxLen = c - LOGGING_TEXT('0');
						state = MAX_STATE;
					}
					else {
						tostringstream buf;
						buf << LOGGING_TEXT("Error occured in position ")
							<< pos
							<< LOGGING_TEXT(".\n Was expecting digit, instead got char \"")
							<< c
							<< LOGGING_TEXT("\".");
						helpers::getLogLog().error(buf.str());
						state = LITERAL_STATE;
					}
					break;

				case MAX_STATE:
					currentLiteral += c;
					if (c >= LOGGING_TEXT('0') && c <= LOGGING_TEXT('9'))
						formattingInfo.maxLen = formattingInfo.maxLen * 10 + (c - LOGGING_TEXT('0'));
					else {
						finalizeConverter(c);
						state = LITERAL_STATE;
					}
					break;
				} // end switch
			} // end while

			if (!currentLiteral.empty()) {
				list.push_back(
					std::unique_ptr<PatternConverter>(
						new LiteralPatternConverter(currentLiteral)));
				//getLogLog().debug("Parsed LITERAL converter: \""+currentLiteral+"\".");
			}

			return std::move(list);
		}



		void
			PatternParser::finalizeConverter(tchar c)
		{
			PatternConverter* pc = nullptr;
			switch (c) {
			case LOGGING_TEXT('b'):
				pc = new BasicPatternConverter
				(formattingInfo,
					BasicPatternConverter::BASENAME_CONVERTER);
				//getLogLog().debug("BASENAME converter.");
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('c'):
				pc = new LoggerPatternConverter(formattingInfo,
					extractPrecisionOption());
				//getLogLog().debug( LOGGING_TEXT("LOGGER converter.") );
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('d'):
			case LOGGING_TEXT('D'):
			{
				tstring dOpt = extractOption();
				if (dOpt.empty()) {
					dOpt = LOGGING_TEXT("%Y-%m-%d %H:%M:%S");
				}
				bool use_gmtime = c == LOGGING_TEXT('d');
				pc = new DatePatternConverter(formattingInfo, dOpt, use_gmtime);
				//if(use_gmtime) {
				//    getLogLog().debug("GMT DATE converter.");
				//}
				//else {
				//    getLogLog().debug("LOCAL DATE converter.");
				//}
				//formattingInfo.dump(getLogLog());
			}
			break;

			case LOGGING_TEXT('E'):
				pc = new EnvPatternConverter(formattingInfo, extractOption());
				//getLogLog().debug("Environment converter.");
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('F'):
				pc = new BasicPatternConverter
				(formattingInfo,
					BasicPatternConverter::FILE_CONVERTER);
				//getLogLog().debug("FILE NAME converter.");
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('h'):
			case LOGGING_TEXT('H'):
			{
				bool fqdn = (c == LOGGING_TEXT('H'));
				pc = new HostnamePatternConverter(formattingInfo, fqdn);
				// getLogLog().debug( LOGGING_TEXT("HOSTNAME converter.") );
				// formattingInfo.dump(getLogLog());
			}
			break;

			case LOGGING_TEXT('i'):
				pc = new BasicPatternConverter
				(formattingInfo,
					BasicPatternConverter::PROCESS_CONVERTER);
				//getLogLog().debug("PROCESS_CONVERTER converter.");
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('l'):
				pc = new BasicPatternConverter
				(formattingInfo,
					BasicPatternConverter::FULL_LOCATION_CONVERTER);
				//getLogLog().debug("FULL LOCATION converter.");
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('L'):
				pc = new BasicPatternConverter
				(formattingInfo,
					BasicPatternConverter::LINE_CONVERTER);
				//getLogLog().debug("LINE NUMBER converter.");
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('m'):
				pc = new BasicPatternConverter
				(formattingInfo,
					BasicPatternConverter::MESSAGE_CONVERTER);
				//getLogLog().debug("MESSAGE converter.");
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('M'):
				pc = new BasicPatternConverter(
					formattingInfo, BasicPatternConverter::FUNCTION_CONVERTER);
				//getLogLog().debug("METHOD (function name) converter.");
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('n'):
				pc = new BasicPatternConverter
				(formattingInfo,
					BasicPatternConverter::NEWLINE_CONVERTER);
				//getLogLog().debug("MESSAGE converter.");
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('p'):
				pc = new BasicPatternConverter
				(formattingInfo,
					BasicPatternConverter::LOGLEVEL_CONVERTER);
				//getLogLog().debug("LOGLEVEL converter.");
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('r'):
				pc = new RelativeTimestampConverter(formattingInfo);
				//getLogLog().debug("RELATIVE converter.");
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('t'):
				pc = new BasicPatternConverter
				(formattingInfo,
					BasicPatternConverter::THREAD_CONVERTER);
				//getLogLog().debug("THREAD converter.");
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('T'):
				pc = new BasicPatternConverter
				(formattingInfo,
					BasicPatternConverter::THREAD2_CONVERTER);
				//getLogLog().debug("THREAD2 converter.");
				//formattingInfo.dump(getLogLog());
				break;

			case LOGGING_TEXT('x'):
				pc = new NDCPatternConverter(formattingInfo, ndcMaxDepth);
				//getLogLog().debug("NDC converter.");
				break;

			case LOGGING_TEXT('X'):
				pc = new MDCPatternConverter(formattingInfo, extractOption());
				//getLogLog().debug("MDC converter.");
				break;

			default:
				tostringstream buf;
				buf << LOGGING_TEXT("Unexpected char [")
					<< c
					<< LOGGING_TEXT("] at position ")
					<< pos
					<< LOGGING_TEXT(" in conversion patterrn.");
				helpers::getLogLog().error(buf.str());
				pc = new LiteralPatternConverter(currentLiteral);
			}

			list.push_back(std::unique_ptr<PatternConverter>(pc));
			currentLiteral.resize(0);
			state = LITERAL_STATE;
			formattingInfo.reset();
		}


	} // namespace pattern


	typedef pattern::PatternConverterList PatternConverterList;


	////////////////////////////////////////////////
	// PatternLayout methods:
	////////////////////////////////////////////////

	PatternLayout::PatternLayout(const tstring& pattern_)
	{
		init(pattern_, 0);
	}


	PatternLayout::PatternLayout(const helpers::Properties& properties)
	{
		unsigned ndcMaxDepth = 0;
		properties.getUInt(ndcMaxDepth, LOGGING_TEXT("NDCMaxDepth"));

		bool hasPattern = properties.exists(LOGGING_TEXT("Pattern"));
		bool hasConversionPattern = properties.exists(LOGGING_TEXT("ConversionPattern"));

		if (hasPattern) {
			helpers::getLogLog().warn(
				LOGGING_TEXT("PatternLayout- the \"Pattern\" property has been")
				LOGGING_TEXT(" deprecated.  Use \"ConversionPattern\" instead."));
		}

		if (hasConversionPattern) {
			init(properties.getProperty(LOGGING_TEXT("ConversionPattern")),
				ndcMaxDepth);
		}
		else if (hasPattern) {
			init(properties.getProperty(LOGGING_TEXT("Pattern")), ndcMaxDepth);
		}
		else {
			helpers::getLogLog().error(
				LOGGING_TEXT("ConversionPattern not specified in properties"),
				true);
		}

	}


	void
		PatternLayout::init(const tstring& pattern_, unsigned ndcMaxDepth)
	{
		pattern = pattern_;
		parsedPattern = pattern::PatternParser(pattern, ndcMaxDepth).parse();

		// Let's validate that our parser didn't give us any NULLs.  If it did,
		// we will convert them to a valid PatternConverter that does nothing so
		// at least we don't core.
		for (auto & pc : parsedPattern)
		{
			if (!pc)
			{
				helpers::getLogLog().error(
					LOGGING_TEXT("Parsed Pattern created a NULL PatternConverter"));
				pc.reset(new pattern::LiteralPatternConverter);
			}
		}

		if (parsedPattern.empty())
		{
			helpers::getLogLog().warn(
				LOGGING_TEXT("PatternLayout pattern is empty.  Using default..."));
			parsedPattern.push_back(
				std::unique_ptr<pattern::PatternConverter>(
					new pattern::BasicPatternConverter(pattern::FormattingInfo(),
						pattern::BasicPatternConverter::MESSAGE_CONVERTER)));
		}
	}



	PatternLayout::~PatternLayout()
	{ }



	void
		PatternLayout::formatAndAppend(tostream& output,
			const spi::InternalLoggingEvent& event)
	{
		for (auto const & pc : parsedPattern)
		{
			pc->formatAndAppend(output, event);
		}
	}

#if defined (LOGGING_WITH_UNIT_TESTS)
	CATCH_TEST_CASE("PatternLayout", "[patternlayout]")
	{
		CATCH_SECTION("get_basename")
		{
			CATCH_REQUIRE(::get_basename(LOGGING_TEXT("/a/b")) == LOGGING_TEXT("b"));
#ifdef _WIN32
			CATCH_REQUIRE(::get_basename(LOGGING_TEXT("C:/a/b")) == LOGGING_TEXT("b"));
			CATCH_REQUIRE(::get_basename(LOGGING_TEXT("C:\\a\\b")) == LOGGING_TEXT("b"));
#endif
		}
	}

#endif

} // namespace logging
