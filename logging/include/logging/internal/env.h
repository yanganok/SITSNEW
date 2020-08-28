#ifndef LOGGING_INTERNAL_ENV_H
#define LOGGING_INTERNAL_ENV_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <vector>
#include <logging/tstring.h>

#if defined (_WIN32)
#include <logging/config/windowsh-inc.h>
#endif
#ifdef LOGGING_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef LOGGING_HAVE_UNISTD_H
#include <unistd.h>
#endif


namespace logging {
	namespace internal {


		//! Get environment variable value.
		bool get_env_var(tstring & value, tstring const & name);

		//! Parse a string as a boolean value.
		bool parse_bool(bool & val, tstring const & str);

		//! Parse a path into path components.
		bool split_path(std::vector<tstring> & components, std::size_t & special,
			tstring const & path);

		//! Makes directories leading to file.
		void make_dirs(tstring const & file_path);

		inline
#if defined (_WIN32)
			DWORD
			get_process_id()
		{
			return GetCurrentProcessId();
		}

#elif defined (LOGGING_HAVE_GETPID)
			pid_t
			get_process_id()
		{
			return getpid();
		}

#else
			int
			get_process_id()
		{
			return 0;
		}

#endif


	}
} // namespace logging { namespace internal {


#endif // LOGGING_INTERNAL_ENV_H
