#include <logging/config.hxx>

#if defined (LOGGING_HAVE_SYS_TYPES_H)
#include <sys/types.h>
#endif
#if defined (LOGGING_HAVE_SYS_STAT_H)
#include <sys/stat.h>
#endif
#if defined (LOGGING_HAVE_SYS_FILE_H)
#include <sys/file.h>
#endif
#if defined (LOGGING_HAVE_UNISTD_H)
#include <unistd.h>
#endif
#if defined (LOGGING_HAVE_FCNTL_H)
#include <fcntl.h>
#endif
#if defined (LOGGING_HAVE_IO_H)
#include <io.h>
#endif
#if defined (_WIN32)
#include <tchar.h>
#include <share.h>
#endif
#include <logging/config/windowsh-inc.h>

#include <stdexcept>
#include <cerrno>
#include <limits>
#include <cstring>

#include <logging/helpers/lockfile.h>
#include <logging/helpers/stringhelper.h>
#include <logging/helpers/loglog.h>
#include <logging/internal/env.h>

#if defined (_WIN32)
#  define LOGGING_USE_WIN32_LOCKFILEEX
#else
#  if defined (O_EXLOCK)
#    define LOGGING_USE_O_EXLOCK
#  elif defined (LOGGING_HAVE_FCNTL) && defined (F_SETLKW)
#    define LOGGING_USE_SETLKW
#  elif defined (LOGGING_HAVE_LOCKF)
#    define LOGGING_USE_LOCKF
#  elif defined (LOGGING_HAVE_FLOCK)
#    define LOGGING_USE_FLOCK
#  endif
#  if defined (LOGGING_USE_O_EXLOCK) || defined (LOGGING_USE_SETLKW) \
    || defined (LOGGING_USE_LOCKF) || defined (LOGGING_USE_FLOCK)
#    define LOGGING_USE_POSIX_LOCKING
#  endif
#endif

#if ! defined (LOGGING_USE_POSIX_LOCKING) && ! defined (_WIN32)
#error "no usable file locking"
#endif

namespace logging {
	namespace helpers {


#if defined (_WIN32)
#if defined (__BORLANDC__)
		int const OPEN_FLAGS = O_RDWR | O_CREAT | O_NOINHERIT;
		int const OPEN_SHFLAGS = SH_DENYNO;
		int const OPEN_MODE = S_IREAD | S_IWRITE;
#else
		int const OPEN_FLAGS = _O_RDWR | _O_CREAT /*| _O_TEMPORARY*/ | _O_NOINHERIT;
		int const OPEN_SHFLAGS = _SH_DENYNO;
		int const OPEN_MODE = _S_IREAD | _S_IWRITE;
#endif

		namespace
		{

			static
				HANDLE
				get_os_HANDLE(int fd)
			{
				HANDLE fh = reinterpret_cast<HANDLE>(_get_osfhandle(fd));
				if (fh == INVALID_HANDLE_VALUE)
					getLogLog().error(tstring(LOGGING_TEXT("_get_osfhandle() failed: "))
						+ convertIntegerToString(errno), true);

				return fh;
			}

		} // namespace

#elif defined (LOGGING_USE_POSIX_LOCKING)
		int const OPEN_FLAGS = O_RDWR | O_CREAT
#if defined (O_CLOEXEC)
			| O_CLOEXEC
#endif
			;

		mode_t const OPEN_MODE = (S_IRWXU ^ S_IXUSR)
			| (S_IRWXG ^ S_IXGRP)
			| (S_IRWXO ^ S_IXOTH);

#endif


		//! Helper function that sets FD_CLOEXEC on descriptor on platforms
		//! that support it.
		LOGGING_PRIVATE
			bool
			trySetCloseOnExec(int fd)
		{
#if defined (WIN32)
			int ret = SetHandleInformation(get_os_HANDLE(fd), HANDLE_FLAG_INHERIT, 0);
			if (!ret)
			{
				DWORD eno = GetLastError();
				getLogLog().warn(
					tstring(
						LOGGING_TEXT("could not unset HANDLE_FLAG_INHERIT on fd: "))
					+ convertIntegerToString(fd)
					+ LOGGING_TEXT(", errno: ")
					+ convertIntegerToString(eno));
				return false;
			}

#elif defined (FD_CLOEXEC)
			int ret = fcntl(fd, F_SETFD, FD_CLOEXEC);
			if (ret == -1)
			{
				int eno = errno;
				getLogLog().warn(
					tstring(LOGGING_TEXT("could not set FD_CLOEXEC on fd: "))
					+ convertIntegerToString(fd)
					+ LOGGING_TEXT(", errno: ")
					+ convertIntegerToString(eno));
				return false;
			}
#else
			return false;

#endif

			return true;
		}


		//
		//
		//

		struct LockFile::Impl
		{
#if defined (LOGGING_USE_POSIX_LOCKING) \
    || defined (_WIN32)
			int fd;

#endif
		};


		//
		//
		//

		LockFile::LockFile(tstring const & lf, bool create_dirs_)
			: lock_file_name(lf)
			, data(new LockFile::Impl)
			, create_dirs(create_dirs_)
		{
#if defined (LOGGING_USE_O_EXLOCK)
			data->fd = -1;

#else
			open(OPEN_FLAGS);

#endif
		}


		LockFile::~LockFile()
		{
			close();
			delete data;
		}


		void
			LockFile::open(int open_flags) const
		{
			if (create_dirs)
				internal::make_dirs(lock_file_name);

#if defined (_WIN32)
#  if defined (LOGGING_HAVE__TSOPEN_S) && defined (_tsopen_s)
			errno_t eno = _tsopen_s(&data->fd, lock_file_name.c_str(), open_flags,
				OPEN_SHFLAGS, OPEN_MODE);
			if (eno != 0)
#  elif defined (LOGGING_HAVE__TSOPEN) && defined (_tsopen)
			data->fd = _tsopen(lock_file_name.c_str(), open_flags, OPEN_SHFLAGS,
				OPEN_MODE);
			if (data->fd == -1)
#  else
#    error "Neither _tsopen_s() nor _tsopen() is available."
#  endif
			getLogLog().error(tstring(LOGGING_TEXT("could not open or create file "))
				+ lock_file_name, true);

#elif defined (LOGGING_USE_POSIX_LOCKING)
			data->fd = ::open(LOGGING_TSTRING_TO_STRING(lock_file_name).c_str(),
				open_flags, OPEN_MODE);
			if (data->fd == -1)
				getLogLog().error(
					tstring(LOGGING_TEXT("could not open or create file "))
					+ lock_file_name, true);

#if ! defined (O_CLOEXEC)
			if (!trySetCloseOnExec(data->fd))
				getLogLog().warn(
					tstring(LOGGING_TEXT("could not set FD_CLOEXEC on file "))
					+ lock_file_name);

#endif
#endif
		}


		void
			LockFile::close() const
		{
#if defined (_WIN32)
			if (data->fd >= 0)
				_close(data->fd);

			data->fd = -1;

#elif defined (LOGGING_USE_POSIX_LOCKING)
			if (data->fd >= 0)
				::close(data->fd);

			data->fd = -1;

#endif
		}


		void
			LockFile::lock() const
		{
			LogLog & loglog = getLogLog();
			int ret = 0;
			(void)loglog;
			(void)ret;

#if defined (LOGGING_USE_WIN32_LOCKFILEEX)
			HANDLE fh = get_os_HANDLE(data->fd);

			OVERLAPPED overlapped;
			std::memset(&overlapped, 0, sizeof(overlapped));
			overlapped.hEvent = 0;

			ret = LockFileEx(fh, LOCKFILE_EXCLUSIVE_LOCK, 0,
				(std::numeric_limits<DWORD>::max) (),
				(std::numeric_limits<DWORD>::max) (), &overlapped);
			if (!ret)
				getLogLog().error(tstring(LOGGING_TEXT("LockFileEx() failed: "))
					+ convertIntegerToString(GetLastError()), true);

#elif defined (LOGGING_USE_O_EXLOCK)
			open(OPEN_FLAGS | O_EXLOCK);

#elif defined (LOGGING_USE_SETLKW)
			do
			{
				struct flock fl;
				fl.l_type = F_WRLCK;
				fl.l_whence = SEEK_SET;
				fl.l_start = 0;
				fl.l_len = 0;
				ret = fcntl(data->fd, F_SETLKW, &fl);
				if (ret == -1 && errno != EINTR)
					getLogLog().error(tstring(LOGGING_TEXT("fcntl(F_SETLKW) failed: "))
						+ convertIntegerToString(errno), true);
			} while (ret == -1);

#elif defined (LOGGING_USE_LOCKF)
			do
			{
				ret = lockf(data->fd, F_LOCK, 0);
				if (ret == -1 && errno != EINTR)
					getLogLog().error(tstring(LOGGING_TEXT("lockf() failed: "))
						+ convertIntegerToString(errno), true);
			} while (ret == -1);

#elif defined (LOGGING_USE_FLOCK)
			do
			{
				ret = flock(data->fd, LOCK_EX);
				if (ret == -1 && errno != EINTR)
					getLogLog().error(tstring(LOGGING_TEXT("flock() failed: "))
						+ convertIntegerToString(errno), true);
			} while (ret == -1);

#endif
		}


		void LockFile::unlock() const
		{
			int ret = 0;

#if defined (LOGGING_USE_WIN32_LOCKFILEEX)
			HANDLE fh = get_os_HANDLE(data->fd);

			ret = UnlockFile(fh, 0, 0, (std::numeric_limits<DWORD>::max) (),
				(std::numeric_limits<DWORD>::max) ());
			if (!ret)
				getLogLog().error(tstring(LOGGING_TEXT("UnlockFile() failed: "))
					+ convertIntegerToString(GetLastError()), true);

#elif defined (LOGGING_USE_O_EXLOCK)
			close();

#elif defined (LOGGING_USE_SETLKW)
			struct flock fl;
			fl.l_type = F_UNLCK;
			fl.l_whence = SEEK_SET;
			fl.l_start = 0;
			fl.l_len = 0;
			ret = fcntl(data->fd, F_SETLKW, &fl);
			if (ret != 0)
				getLogLog().error(tstring(LOGGING_TEXT("fcntl(F_SETLKW) failed: "))
					+ convertIntegerToString(errno), true);

#elif defined (LOGGING_USE_LOCKF)
			ret = lockf(data->fd, F_ULOCK, 0);
			if (ret != 0)
				getLogLog().error(tstring(LOGGING_TEXT("lockf() failed: "))
					+ convertIntegerToString(errno), true);

#elif defined (LOGGING_USE_FLOCK)
			ret = flock(data->fd, LOCK_UN);
			if (ret != 0)
				getLogLog().error(tstring(LOGGING_TEXT("flock() failed: "))
					+ convertIntegerToString(errno), true);

#endif

		}



	}
} // namespace logging { namespace helpers {
