#ifndef LOGGING_WIN32CONSOLEAPPENDER_H
#define LOGGING_WIN32CONSOLEAPPENDER_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#if defined(_WIN32) && defined (LOGGING_HAVE_WIN32_CONSOLE)

#include <logging/appender.h>


namespace logging
{

	/**
	 * Prints events to Win32 console.
	 *
	 * <h3>Properties</h3>
	 * <dl>
	 * <dt><tt>AllocConsole</tt></dt>
	 * <dd>This boolean property specifies whether or not this appender
	 * will try to allocate new console using the
	 * <code>AllocConsole()</code> Win32 function.</dd>
	 *
	 * <dt><tt>logToStdErr</tt></dt>
	 * <dd>When it is set true, the output will be into
	 * <code>STD_ERROR_HANDLE</code> instead of <code>STD_OUTPUT_HANDLE</code>.
	 * </dd>
	 *
	 * <dt><tt>TextColor</tt></dt>
	 * <dd>See MSDN documentation for
	 * <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ms682088(v=vs.85).aspx#_win32_character_attributes">
	 * Character Attributes</a>.
	 * </dl>
	 */
	class LOGGING_EXPORT Win32ConsoleAppender
		: public Appender
	{
	public:
		explicit Win32ConsoleAppender(bool allocConsole = true,
			bool logToStdErr = false, unsigned int textColor = 0);
		Win32ConsoleAppender(helpers::Properties const & properties);
		virtual ~Win32ConsoleAppender();

		virtual void close();

	protected:
		virtual void append(spi::InternalLoggingEvent const &);

		void write_handle(void *, tchar const *, std::size_t);
		void write_console(void *, tchar const *, std::size_t);

		bool alloc_console;
		bool log_to_std_err;
		unsigned int text_color;

	private:
		Win32ConsoleAppender(Win32ConsoleAppender const &);
		Win32ConsoleAppender & operator = (Win32ConsoleAppender const &);
	};

} // namespace logging

#endif

#endif // LOGGING_WIN32CONSOLEAPPENDER_H
