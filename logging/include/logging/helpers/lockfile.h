#if ! defined (LOGGING_HELPERS_LOCKFILE_H)
#define LOGGING_HELPERS_LOCKFILE_H

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/tstring.h>
#include <logging/thread/syncprims.h>


namespace logging {
	namespace helpers {


		class LOGGING_EXPORT LockFile
		{
		public:
			LockFile(tstring const & lock_file, bool create_dirs = false);
			~LockFile();

			void lock() const;
			void unlock() const;

		private:
			void open(int) const;
			void close() const;

			struct Impl;

			tstring lock_file_name;
			Impl * data;
			bool create_dirs;
		};


		typedef logging::thread::SyncGuard<LockFile> LockFileGuard;


	}
} // namespace logging { namespace helpers {


#endif // LOGGING_HELPERS_LOCKFILE_H
