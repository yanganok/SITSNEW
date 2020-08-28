#ifndef LOGGING_HELPERS_PROPERTY_HEADER_
#define LOGGING_HELPERS_PROPERTY_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/streams.h>
#include <logging/tstring.h>
#include <map>
#include <vector>


namespace logging {
	namespace helpers {

		//! \sa logging::PropertyConfigurator
		class LOGGING_EXPORT Properties {
		public:
			enum PFlags
			{
				// These encoding related options occupy 2 bits of the flags
				// and are mutually exclusive. These flags are synchronized
				// with PCFlags in PropertyConfigurator.

				fEncodingShift = 3
				, fEncodingMask = 0x3
				, fUnspecEncoding = (0 << fEncodingShift)
#if defined (LOGGING_HAVE_CODECVT_UTF8_FACET) && defined (UNICODE)
				, fUTF8 = (1 << fEncodingShift)
#endif
#if (defined (LOGGING_HAVE_CODECVT_UTF16_FACET) || defined (_WIN32)) \
    && defined (UNICODE)
				, fUTF16 = (2 << fEncodingShift)
#endif
#if defined (LOGGING_HAVE_CODECVT_UTF32_FACET) && defined (UNICODE)
				, fUTF32 = (3 << fEncodingShift)
#endif
			};

			Properties();
			explicit Properties(logging::tistream& input);
			explicit Properties(const logging::tstring& inputFile, unsigned flags = 0);
			virtual ~Properties();

			// constants
			static const tchar PROPERTIES_COMMENT_CHAR;

			// methods
			  /**
			   * Tests to see if <code>key</code> can be found in this map.
			   */
			bool exists(const logging::tstring& key) const;
			bool exists(tchar const * key) const;

			/**
			 * Returns the number of entries in this map.
			 */
			std::size_t size() const
			{
				return data.size();
			}

			/**
			 * Searches for the property with the specified key in this property
			 * list. If the key is not found in this property list, the default
			 * property list, and its defaults, recursively, are then checked.
			 * The method returns <code>null</code> if the property is not found.
			 */
			logging::tstring const & getProperty(const logging::tstring& key) const;
			logging::tstring const & getProperty(tchar const * key) const;

			/**
			 * Searches for the property with the specified key in this property
			 * list. If the key is not found in this property list, the default
			 * property list, and its defaults, recursively, are then checked.
			 * The method returns the default value argument if the property is
			 * not found.
			 */
			logging::tstring getProperty(const logging::tstring& key,
				const logging::tstring& defaultVal) const;

			/**
			 * Returns all the keys in this property list.
			 */
			std::vector<logging::tstring> propertyNames() const;

			/**
			 * Inserts <code>value</code> into this map indexed by <code>key</code>.
			 */
			void setProperty(const logging::tstring& key, const logging::tstring& value);

			/**
			 * Removed the property index by <code>key</code> from this map.
			 */
			bool removeProperty(const logging::tstring& key);

			/**
			 * Returns a subset of the "properties" whose keys start with
			 * "prefix".  The returned "properties" have "prefix" trimmed from
			 * their keys.
			 */
			Properties getPropertySubset(const logging::tstring& prefix) const;

			bool getInt(int & val, logging::tstring const & key) const;
			bool getUInt(unsigned & val, logging::tstring const & key) const;
			bool getLong(long & val, logging::tstring const & key) const;
			bool getULong(unsigned long & val, logging::tstring const & key) const;
			bool getBool(bool & val, logging::tstring const & key) const;
			bool getString(logging::tstring & val, logging::tstring const & key) const;

		protected:
			// Types
			typedef std::map<logging::tstring, logging::tstring> StringMap;

			// Methods
			void init(logging::tistream& input);

			// Data
			StringMap data;
			unsigned flags;

		private:
			template <typename StringType>
			logging::tstring const & get_property_worker(
				StringType const & key) const;

			template <typename ValType>
			bool get_type_val_worker(ValType & val,
				logging::tstring const & key) const;
		};
	} // end namespace helpers

}


#endif // LOGGING_HELPERS_PROPERTY_HEADER_
