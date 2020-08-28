#include <logging/mdc.h>
#include <logging/internal/internal.h>

#if defined (LOGGING_WITH_UNIT_TESTS)
#include <logging/catch.hpp>
#endif


namespace logging
{


	MDC::MDC()
	{ }


	MDC::~MDC()
	{ }


	MappedDiagnosticContextMap *
		MDC::getPtr()
	{
		return &internal::get_ptd()->mdc_map;
	}


	void
		MDC::clear()
	{
		MappedDiagnosticContextMap * const dc = getPtr();
		MappedDiagnosticContextMap().swap(*dc);
	}


	void
		MDC::put(tstring const & key, tstring const & value)
	{
		MappedDiagnosticContextMap * const dc = getPtr();
		(*dc)[key] = value;
	}


	bool
		MDC::get(tstring * value, tstring const & key) const
	{
		assert(value);

		MappedDiagnosticContextMap * const dc = getPtr();
		MappedDiagnosticContextMap::const_iterator it = dc->find(key);
		if (it != dc->end())
		{
			*value = it->second;
			return true;
		}
		else
			return false;
	}


	void
		MDC::remove(tstring const & key)
	{
		MappedDiagnosticContextMap * const dc = getPtr();
		dc->erase(key);
	}


	MappedDiagnosticContextMap const &
		MDC::getContext() const
	{
		return *getPtr();
	}


#if defined (LOGGING_WITH_UNIT_TESTS)
	CATCH_TEST_CASE("MDC", "[MDC]")
	{
		tstring str;
		MDC & mdc = getMDC();
		mdc.put(LOGGING_TEXT("key1"), LOGGING_TEXT("value1"));
		mdc.put(LOGGING_TEXT("key2"), LOGGING_TEXT("value2"));

		CATCH_SECTION("get")
		{
			CATCH_REQUIRE(mdc.get(&str, LOGGING_TEXT("key1")));
			CATCH_REQUIRE(str == LOGGING_TEXT("value1"));
			CATCH_REQUIRE(mdc.get(&str, LOGGING_TEXT("key2")));
			CATCH_REQUIRE(str == LOGGING_TEXT("value2"));
			CATCH_REQUIRE(!mdc.get(&str, LOGGING_TEXT("nonexisting")));
		}

		CATCH_SECTION("remove")
		{
			mdc.remove(LOGGING_TEXT("key1"));
			CATCH_REQUIRE(!mdc.get(&str, LOGGING_TEXT("key1")));
			CATCH_REQUIRE(mdc.get(&str, LOGGING_TEXT("key2")));
			CATCH_REQUIRE(str == LOGGING_TEXT("value2"));
		}

		CATCH_SECTION("clear")
		{
			mdc.clear();
			CATCH_REQUIRE(!mdc.get(&str, LOGGING_TEXT("key1")));
			CATCH_REQUIRE(!mdc.get(&str, LOGGING_TEXT("key2")));
		}
	}

#endif

} // namespace logging
