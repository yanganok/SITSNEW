#include <logging/ndc.h>
#include <logging/internal/internal.h>
#include <utility>
#include <algorithm>

#if defined (LOGGING_WITH_UNIT_TESTS)
#include <logging/catch.hpp>
#endif


namespace logging
{



	///////////////////////////////////////////////////////////////////////////////
	// logging::DiagnosticContext ctors
	///////////////////////////////////////////////////////////////////////////////


	namespace
	{


		static
			void
			init_full_message(logging::tstring & fullMessage,
				logging::tstring const & message, DiagnosticContext const * parent)
		{
			if (parent)
			{
				fullMessage.reserve(parent->fullMessage.size() + 1
					+ message.size());
				fullMessage = parent->fullMessage;
				fullMessage += LOGGING_TEXT(" ");
				fullMessage += message;
			}
			else
				fullMessage = message;
		}


	} // namespace


	DiagnosticContext::DiagnosticContext(const logging::tstring& message_,
		DiagnosticContext const * parent)
		: message(message_)
		, fullMessage()
	{
		init_full_message(fullMessage, message, parent);
	}


	DiagnosticContext::DiagnosticContext(tchar const * message_,
		DiagnosticContext const * parent)
		: message(message_)
		, fullMessage()
	{
		init_full_message(fullMessage, message, parent);
	}


	DiagnosticContext::DiagnosticContext(const logging::tstring& message_)
		: message(message_)
		, fullMessage(message)
	{
	}


	DiagnosticContext::DiagnosticContext(tchar const * message_)
		: message(message_)
		, fullMessage(message)
	{
	}


	DiagnosticContext::DiagnosticContext(DiagnosticContext const & other)
		: message(other.message)
		, fullMessage(other.fullMessage)
	{ }


	DiagnosticContext & DiagnosticContext::operator = (
		DiagnosticContext const & other)
	{
		DiagnosticContext(other).swap(*this);
		return *this;
	}


	DiagnosticContext::DiagnosticContext(DiagnosticContext && other)
		: message(std::move(other.message))
		, fullMessage(std::move(other.fullMessage))
	{ }


	DiagnosticContext &
		DiagnosticContext::operator = (DiagnosticContext && other)
	{
		DiagnosticContext(std::move(other)).swap(*this);
		return *this;
	}


	void
		DiagnosticContext::swap(DiagnosticContext & other)
	{
		using std::swap;
		swap(message, other.message);
		swap(fullMessage, other.fullMessage);
	}

	///////////////////////////////////////////////////////////////////////////////
	// logging::NDC ctor and dtor
	///////////////////////////////////////////////////////////////////////////////

	NDC::NDC()
	{ }


	NDC::~NDC()
	{ }



	///////////////////////////////////////////////////////////////////////////////
	// logging::NDC public methods
	///////////////////////////////////////////////////////////////////////////////

	void
		NDC::clear()
	{
		DiagnosticContextStack* ptr = getPtr();
		DiagnosticContextStack().swap(*ptr);
	}


	void
		NDC::remove()
	{
		clear();
	}


	DiagnosticContextStack
		NDC::cloneStack() const
	{
		DiagnosticContextStack* ptr = getPtr();
		return DiagnosticContextStack(*ptr);
	}


	void
		NDC::inherit(const DiagnosticContextStack& stack)
	{
		DiagnosticContextStack* ptr = getPtr();
		DiagnosticContextStack(stack).swap(*ptr);
	}


	logging::tstring const &
		NDC::get() const
	{
		DiagnosticContextStack* ptr = getPtr();
		if (!ptr->empty())
			return ptr->back().fullMessage;
		else
			return internal::empty_str;
	}


	std::size_t
		NDC::getDepth() const
	{
		DiagnosticContextStack* ptr = getPtr();
		return ptr->size();
	}


	logging::tstring
		NDC::pop()
	{
		DiagnosticContextStack* ptr = getPtr();
		if (!ptr->empty())
		{
			tstring message;
			message.swap(ptr->back().message);
			ptr->pop_back();
			return message;
		}
		else
			return logging::tstring();
	}


	void
		NDC::pop_void()
	{
		DiagnosticContextStack* ptr = getPtr();
		if (!ptr->empty())
			ptr->pop_back();
	}


	logging::tstring const &
		NDC::peek() const
	{
		DiagnosticContextStack* ptr = getPtr();
		if (!ptr->empty())
			return ptr->back().message;
		else
			return internal::empty_str;
	}


	void
		NDC::push(const logging::tstring& message)
	{
		push_worker(message);
	}


	void
		NDC::push(tchar const * message)
	{
		push_worker(message);
	}


	template <typename StringType>
	void
		NDC::push_worker(StringType const & message)
	{
		DiagnosticContextStack* ptr = getPtr();
		if (ptr->empty())
			ptr->push_back(DiagnosticContext(message, nullptr));
		else
		{
			DiagnosticContext const & dc = ptr->back();
			ptr->push_back(DiagnosticContext(message, &dc));
		}
	}


	void
		NDC::setMaxDepth(std::size_t maxDepth)
	{
		DiagnosticContextStack* ptr = getPtr();
		while (maxDepth < ptr->size())
			ptr->pop_back();
	}


	DiagnosticContextStack* NDC::getPtr()
	{
		internal::per_thread_data * ptd = internal::get_ptd();
		return &ptd->ndc_dcs;
	}


	//
	//
	//

	NDCContextCreator::NDCContextCreator(const logging::tstring& msg)
	{
		getNDC().push(msg);
	}


	NDCContextCreator::NDCContextCreator(tchar const * msg)
	{
		getNDC().push(msg);
	}


	NDCContextCreator::~NDCContextCreator()
	{
		getNDC().pop_void();
	}


#if defined (LOGGING_WITH_UNIT_TESTS)
	CATCH_TEST_CASE("NDC", "[NDC]")
	{
		NDC & ndc = getNDC();
		ndc.clear();
		static tchar const CONTEXT1[] = LOGGING_TEXT("c1");
		static tchar const CONTEXT2[] = LOGGING_TEXT("c2");
		static tchar const CONTEXT3[] = LOGGING_TEXT("c3");
		static tstring const C1C2 = tstring(CONTEXT1)
			+ LOGGING_TEXT(' ')
			+ CONTEXT2;
		static tstring const C1C2C3 = C1C2
			+ LOGGING_TEXT(' ')
			+ CONTEXT3;

		CATCH_SECTION("basic")
		{
			CATCH_REQUIRE(ndc.get().empty());
			CATCH_REQUIRE(ndc.peek().empty());
			CATCH_REQUIRE(ndc.getDepth() == 0);
			NDCContextCreator c1(CONTEXT1);
			CATCH_REQUIRE(ndc.peek() == CONTEXT1);
			CATCH_REQUIRE(ndc.get() == CONTEXT1);
			CATCH_REQUIRE(ndc.getDepth() == 1);
			{
				NDCContextCreator c2(LOGGING_C_STR_TO_TSTRING(CONTEXT2));
				CATCH_REQUIRE(ndc.get() == C1C2);
				CATCH_REQUIRE(ndc.getDepth() == 2);
				CATCH_REQUIRE(ndc.peek() == CONTEXT2);

				ndc.push(CONTEXT3);
				CATCH_REQUIRE(ndc.get() == C1C2C3);
				CATCH_REQUIRE(ndc.peek() == CONTEXT3);
				CATCH_REQUIRE(ndc.pop() == CONTEXT3);
			}
			CATCH_REQUIRE(ndc.peek() == CONTEXT1);
			CATCH_REQUIRE(ndc.get() == CONTEXT1);
			CATCH_REQUIRE(ndc.getDepth() == 1);
		}

		CATCH_SECTION("remove")
		{
			ndc.push(CONTEXT1);
			CATCH_REQUIRE(ndc.peek() == CONTEXT1);
			CATCH_REQUIRE(ndc.get() == CONTEXT1);
			CATCH_REQUIRE(ndc.getDepth() == 1);

			ndc.remove();
			CATCH_REQUIRE(ndc.get().empty());
			CATCH_REQUIRE(ndc.peek().empty());
			CATCH_REQUIRE(ndc.getDepth() == 0);
		}
	}

#endif

} // namespace logging
