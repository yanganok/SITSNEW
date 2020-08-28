#ifndef LOGGING_HELPERS_TIME_HELPER_HEADER_
#define LOGGING_HELPERS_TIME_HELPER_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/tstring.h>

#if defined (LOGGING_HAVE_TIME_H)
#include <time.h>
#endif

#include <ctime>
#include <chrono>


namespace logging {

	namespace helpers {


		using std::time_t;
		using std::tm;
		namespace chrono = std::chrono;

		typedef chrono::system_clock Clock;
		typedef chrono::duration<long long, std::micro> Duration;
		typedef chrono::time_point<Clock, Duration> Time;


		template <typename FromDuration>
		inline
			Time
			time_cast(chrono::time_point<Clock, FromDuration> const & tp)
		{
			return chrono::time_point_cast<Duration, Clock> (tp);
		}


		inline
			Time
			now()
		{
			return time_cast(Clock::now());
		}


		inline
			Time
			from_time_t(time_t t_time)
		{
			return time_cast(Clock::from_time_t(t_time));
		}


		inline
			time_t
			to_time_t(Time const & the_time)
		{
			// This is based on <http://stackoverflow.com/a/17395137/341065>. It is
			// possible that to_time_t() returns rounded time and we want truncation.

			time_t time = Clock::to_time_t(the_time);
			auto const rounded_time = from_time_t(time);
			if (rounded_time > the_time)
				--time;

			return time;
		}


		LOGGING_EXPORT Time from_struct_tm(tm * t);


		inline
			Time
			truncate_fractions(Time const & the_time)
		{
			return from_time_t(to_time_t(the_time));
		}


		inline
			long
			microseconds_part(Time const & the_time)
		{
			static_assert ((std::ratio_equal<Duration::period, std::micro>::value),
				"microseconds");

			// This is based on <http://stackoverflow.com/a/17395137/341065>
			return static_cast<long>(
				(the_time - from_time_t(to_time_t(the_time))).count());
		}


		inline
			Time
			time_from_parts(time_t tv_sec, long tv_usec)
		{
			return from_time_t(tv_sec) + chrono::microseconds(tv_usec);
		}


		/**
		 * Populates <code>tm</code> using the <code>gmtime()</code>
		 * function.
		 */

		LOGGING_EXPORT
			void gmTime(tm* t, Time const &);

		/**
		 * Populates <code>tm</code> using the <code>localtime()</code>
		 * function.
		 */

		LOGGING_EXPORT
			void localTime(tm* t, Time const &);

		/**
		 * Returns a string with a "formatted time" specified by
		 * <code>fmt</code>.  It used the <code>strftime()</code>
		 * function to do this.
		 *
		 * Look at your platform's <code>strftime()</code> documentation
		 * for the formatting options available.
		 *
		 * The following additional options are provided:<br>
		 * <code>%q</code> - 3 character field that provides milliseconds
		 * <code>%Q</code> - 7 character field that provides fractional
		 * milliseconds.
		 */
		LOGGING_EXPORT
			logging::tstring getFormattedTime(logging::tstring const & fmt,
				Time const & the_time, bool use_gmtime = false);


	} // namespace helpers

} // namespace logging


#endif // LOGGING_HELPERS_TIME_HELPER_HEADER_
