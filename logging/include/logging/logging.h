#ifndef LOGGING_LOGGING_HXX
#define LOGGING_LOGGING_HXX

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/version.h>
#include <logging/loglevel.h>
#include <logging/logger.h>
#include <logging/layout.h>
#include <logging/hierarchy.h>
#include <logging/loggingmacros.h>
#include <logging/tracelogger.h>
#include <logging/configurator.h>
#include <logging/appender.h>
#include <logging/mdc.h>
#include <logging/ndc.h>
#include <logging/initializer.h>
#include <logging/helpers/property.h>
#include <logging/spi/factory.h>
#include <logging/spi/filter.h>
#include <logging/spi/loggingevent.h>

#include <logging/asyncappender.h>
#include <logging/consoleappender.h>
#include <logging/fileappender.h>
#include <logging/socketappender.h>
#include <logging/syslogappender.h>
#include <logging/nullappender.h>

namespace logging
{
#if defined (LOGGING_WITH_UNIT_TESTS)
	LOGGING_EXPORT int unit_tests_main(int argc, char* argv[]);
#endif
	LOGGING_EXPORT Logger create(const logging::tstring& filename,
		long maxFileSize = 10 * 1024 * 1024,	// Size = 10 MB
		int maxBackupIndex = 10);				// Backup = 10		
}

#endif




// Tips for Getting Started: 
//   1. create Visual C++ Console App project: sample
//   2. [Properties] -> [Configuration Manager...] -> Platform: x64
//   3. [Properties] -> [C/C++] -> [General] -> Additional Include Directories: ..\..\include
//   4. [Properties] -> [Linker] -> [General] -> Additional Library Directories: ..\..\packages
//   5. [Properties] -> [Linker] -> [Input] -> Additional Dependencies: logging.lib
//   6. [Build Events] -> [Pro-Build Event] -> Command Line: 
//      set FromDir=$(SolutionDir)packages\
//      set ToDir=$(SolutionDir)$(Platform)\$(Configuration)\
//      if exist %ToDir% (rmdir %ToDir% /S /Q )
//      if not exist %ToDir% (mkdir %ToDir% )
//      if exist %ToDir% (xcopy %FromDir%logging.* %ToDir% /S /E /Y /I /C )
