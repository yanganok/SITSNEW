#ifndef LOGGING_INTERNAL_INTERNAL_HEADER_
#define LOGGING_INTERNAL_INTERNAL_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#if ! defined (INSIDE_LOGGING)
#  error "This header must not be be used outside logging' implementation files."
#endif

#include <memory>
#include <vector>
#include <sstream>
#include <cstdio>
#include <logging/tstring.h>
#include <logging/streams.h>
#include <logging/ndc.h>
#include <logging/mdc.h>
#include <logging/spi/loggingevent.h>
#include <logging/thread/impl/tls.h>
#include <logging/helpers/snprintf.h>


namespace logging {

	namespace internal {


		//! Canonical empty string. It is used when the need to return empty string
		//! by reference arises.
		extern logging::tstring const empty_str;


		struct gft_scratch_pad
		{
			gft_scratch_pad();
			~gft_scratch_pad();

			void
				reset()
			{
				uc_q_str_valid = false;
				q_str_valid = false;
				s_str_valid = false;
				ret.clear();
			}

			logging::tstring q_str;
			logging::tstring uc_q_str;
			logging::tstring s_str;
			logging::tstring ret;
			logging::tstring fmt;
			logging::tstring tmp;
			std::vector<tchar> buffer;
			bool uc_q_str_valid;
			bool q_str_valid;
			bool s_str_valid;
		};


		struct appender_sratch_pad
		{
			appender_sratch_pad();
			~appender_sratch_pad();

			tostringstream oss;
			tstring str;
			std::string chstr;
		};


		//! Per thread data.
		struct per_thread_data
		{
			per_thread_data();
			~per_thread_data();

			tstring macros_str;
			tostringstream macros_oss;
			tostringstream layout_oss;
			DiagnosticContextStack ndc_dcs;
			MappedDiagnosticContextMap mdc_map;
			logging::tstring thread_name;
			logging::tstring thread_name2;
			gft_scratch_pad gft_sp;
			appender_sratch_pad appender_sp;
			logging::tstring faa_str;
			logging::tstring ll_str;
			spi::InternalLoggingEvent forced_log_ev;
			std::FILE * fnull;
			logging::helpers::snprintf_buf snprintf_buf;
		};


		per_thread_data * alloc_ptd();

		// TLS key whose value is pointer struct per_thread_data.
		extern logging::thread::impl::tls_key_type tls_storage_key;


#if ! defined (LOGGING_SINGLE_THREADED) \
    && defined (LOGGING_THREAD_LOCAL_VAR)

		extern LOGGING_THREAD_LOCAL_VAR per_thread_data * ptd;


		inline
			void
			set_ptd(per_thread_data * p)
		{
			ptd = p;
		}


		inline
			per_thread_data *
			get_ptd(bool alloc = true)
		{
			if (LOGGING_UNLIKELY(!ptd && alloc))
				return alloc_ptd();

			// The assert() does not belong here. get_ptd() might be called by
			// cleanup code that can handle the returned NULL pointer.
			//assert (ptd);

			return ptd;
		}


#else // defined (LOGGING_THREAD_LOCAL_VAR)


		inline
			void
			set_ptd(per_thread_data * p)
		{
			thread::impl::tls_set_value(tls_storage_key, p);
		}


		inline
			per_thread_data *
			get_ptd(bool alloc = true)
		{
			per_thread_data * ptd
				= reinterpret_cast<per_thread_data *>(
					thread::impl::tls_get_value(tls_storage_key));

			if (LOGGING_UNLIKELY(!ptd && alloc))
				return alloc_ptd();

			return ptd;
		}


#endif // defined (LOGGING_THREAD_LOCAL_VAR)


		inline
			tstring &
			get_thread_name_str()
		{
			return get_ptd()->thread_name;
		}


		inline
			tstring &
			get_thread_name2_str()
		{
			return get_ptd()->thread_name2;
		}


		inline
			gft_scratch_pad &
			get_gft_scratch_pad()
		{
			return get_ptd()->gft_sp;
		}


		inline
			appender_sratch_pad &
			get_appender_sp()
		{
			return get_ptd()->appender_sp;
		}


	} // namespace internal {


	namespace detail
	{

		LOGGING_EXPORT void clear_tostringstream(tostringstream &);

	} // namespace detail


} // namespace logging { 


#endif // LOGGING_INTERNAL_INTERNAL_HEADER_
