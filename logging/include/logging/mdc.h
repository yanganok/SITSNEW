#ifndef LOGGING_MDC_H_HEADER
#define LOGGING_MDC_H_HEADER

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/tstring.h>

#include <map>


namespace logging
{


	typedef std::map<tstring, tstring> MappedDiagnosticContextMap;


	class LOGGING_EXPORT MDC
	{
	public:
		/**
		 * Clear any nested diagnostic information if any. This method is
		 * useful in cases where the same thread can be potentially used
		 * over and over in different unrelated contexts.
		 */
		void clear();

		void put(tstring const & key, tstring const & value);
		bool get(tstring * value, tstring const & key) const;
		void remove(tstring const & key);

		MappedDiagnosticContextMap const & getContext() const;

		// Public ctor and dtor but only to be used by internal::DefaultContext.
		MDC();
		virtual ~MDC();

	private:
		LOGGING_PRIVATE static MappedDiagnosticContextMap * getPtr();
	};


	LOGGING_EXPORT MDC & getMDC();


} // namespace logging


#endif // LOGGING_MDC_H_HEADER
