#include <logging/config.hxx>
#include <logging/helpers/fileinfo.h>

#ifdef LOGGING_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef LOGGING_HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif

#if defined (_WIN32)
#include <tchar.h>
#include <logging/config/windowsh-inc.h>
#endif


namespace logging {
	namespace helpers {


		int
			getFileInfo(FileInfo * fi, tstring const & name)
		{
#if defined (_WIN32)
			struct _stat fileStatus;
			if (_tstat(name.c_str(), &fileStatus) == -1)
				return -1;

			fi->mtime = helpers::from_time_t(fileStatus.st_mtime);
			fi->is_link = false;
			fi->size = fileStatus.st_size;

#else
			struct stat fileStatus;
			if (stat(LOGGING_TSTRING_TO_STRING(name).c_str(),
				&fileStatus) == -1)
				return -1;

			fi->mtime = helpers::from_time_t(fileStatus.st_mtime);
			fi->is_link = S_ISLNK(fileStatus.st_mode);
			fi->size = fileStatus.st_size;

#endif

			return 0;
		}

	}
} // namespace logging { namespace helpers {
