#if ! defined (LOGGING_HELPERS_FILEINFO_H)
#define LOGGING_HELPERS_FILEINFO_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/helpers/timehelper.h>
#ifdef LOGGING_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif


namespace logging {
	namespace helpers {

		//! FileInfo structure is OS independent abstraction of the
		//! <code>stat()</code> function.
		struct LOGGING_EXPORT FileInfo
		{
			helpers::Time mtime;
			bool is_link;
			off_t size;
		};


		//! OS independent abstraction of <code>stat()</code> function.
		LOGGING_EXPORT int getFileInfo(FileInfo * fi, tstring const & name);


	}
} // namespace logging { namespace helpers {

#endif // LOGGING_HELPERS_FILEINFO_H
