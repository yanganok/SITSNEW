#include <logging/layout.h>
#include <logging/helpers/stringhelper.h>
#include <logging/helpers/timehelper.h>
#include <logging/spi/loggingevent.h>
#include <logging/helpers/property.h>
#include <logging/internal/internal.h>
#include <ostream>
#include <iomanip>


namespace logging
{

	void
		formatRelativeTimestamp(logging::tostream & output,
			logging::spi::InternalLoggingEvent const & event)
	{
		auto const duration
			= event.getTimestamp() - getTTCCLayoutTimeBase();
		output << helpers::chrono::duration_cast<
			helpers::chrono::duration<long long, std::milli>>(
				duration).count();
	}

	//
	//
	//


	Layout::Layout()
		: llmCache(getLogLevelManager())
	{ }


	Layout::Layout(const logging::helpers::Properties&)
		: llmCache(getLogLevelManager())
	{ }


	Layout::~Layout()
	{ }


	///////////////////////////////////////////////////////////////////////////////
	// logging::SimpleLayout public methods
	///////////////////////////////////////////////////////////////////////////////

	SimpleLayout::SimpleLayout()
	{ }


	SimpleLayout::SimpleLayout(const helpers::Properties& properties)
		: Layout(properties)
	{ }


	SimpleLayout::~SimpleLayout()
	{ }


	void
		SimpleLayout::formatAndAppend(logging::tostream& output,
			const logging::spi::InternalLoggingEvent& event)
	{
		output << llmCache.toString(event.getLogLevel())
			<< LOGGING_TEXT(" - ")
			<< event.getMessage()
			<< LOGGING_TEXT("\n");
	}



	///////////////////////////////////////////////////////////////////////////////
	// logging::TTCCLayout ctors and dtor
	///////////////////////////////////////////////////////////////////////////////

	TTCCLayout::TTCCLayout(bool use_gmtime_, bool thread_printing_,
		bool category_prefixing_, bool context_printing_)
		: dateFormat()
		, use_gmtime(use_gmtime_)
		, thread_printing(thread_printing_)
		, category_prefixing(category_prefixing_)
		, context_printing(context_printing_)
	{
	}


	TTCCLayout::TTCCLayout(const logging::helpers::Properties& properties)
		: Layout(properties)
		, dateFormat(properties.getProperty(LOGGING_TEXT("DateFormat"),
			internal::empty_str))
	{
		properties.getBool(use_gmtime, LOGGING_TEXT("Use_gmtime"));
		properties.getBool(thread_printing, LOGGING_TEXT("ThreadPrinting"));
		properties.getBool(category_prefixing, LOGGING_TEXT("CategoryPrefixing"));
		properties.getBool(context_printing, LOGGING_TEXT("ContextPrinting"));
	}


	TTCCLayout::~TTCCLayout()
	{ }



	///////////////////////////////////////////////////////////////////////////////
	// logging::TTCCLayout public methods
	///////////////////////////////////////////////////////////////////////////////

	void
		TTCCLayout::formatAndAppend(logging::tostream& output,
			const logging::spi::InternalLoggingEvent& event)
	{
		if (dateFormat.empty())
			formatRelativeTimestamp(output, event);
		else
			output << helpers::getFormattedTime(dateFormat, event.getTimestamp(),
				use_gmtime);

		if (getThreadPrinting())
			output << LOGGING_TEXT(" [")
			<< event.getThread()
			<< LOGGING_TEXT("] ");
		else
			output << LOGGING_TEXT(' ');

		output << llmCache.toString(event.getLogLevel())
			<< LOGGING_TEXT(' ');

		if (getCategoryPrefixing())
			output << event.getLoggerName()
			<< LOGGING_TEXT(' ');

		if (getContextPrinting())
			output << LOGGING_TEXT("<")
			<< event.getNDC()
			<< LOGGING_TEXT("> ");

		output << LOGGING_TEXT("- ")
			<< event.getMessage()
			<< LOGGING_TEXT("\n");
	}


	bool
		TTCCLayout::getThreadPrinting() const
	{
		return thread_printing;
	}


	void
		TTCCLayout::setThreadPrinting(bool thread_printing_)
	{
		thread_printing = thread_printing_;
	}


	bool
		TTCCLayout::getCategoryPrefixing() const
	{
		return category_prefixing;
	}


	void
		TTCCLayout::setCategoryPrefixing(bool category_prefixing_)
	{
		category_prefixing = category_prefixing_;
	}


	bool
		TTCCLayout::getContextPrinting() const
	{
		return context_printing;
	}


	void
		TTCCLayout::setContextPrinting(bool context_printing_)
	{
		context_printing = context_printing_;
	}


} // namespace logging
