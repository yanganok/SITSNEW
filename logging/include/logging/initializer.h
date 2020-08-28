#ifndef LOGGING_INITIALIZER_HXX
#define LOGGING_INITIALIZER_HXX

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <memory>


namespace logging
{

	/**
	   This class helps with initialization and shutdown of logging. Its
	   constructor calls `logging::initialize()` and its destructor calls
	   `logging::Logger::shutdown()`. Use this class as the first thing in your
	   `main()`. It will ensure shutdown of logging at the end of
	   `main()`. This is particularly important on Windows, where shutdown of
	   standard threads outside `main()` is impossible.
	 */
	class LOGGING_EXPORT Initializer
	{
	public:
		Initializer();
		~Initializer();

		Initializer(Initializer const &) = delete;
		Initializer(Initializer &&) = delete;
		Initializer & operator = (Initializer const &) = delete;
		Initializer & operator = (Initializer &&) = delete;
	};

} // namespace logging


#endif // LOGGING_INITIALIZER_HXX
