#ifndef LOGGING_SPI_OBJECT_REGISTRY_HEADER_
#define LOGGING_SPI_OBJECT_REGISTRY_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/tstring.h>
#include <logging/thread/syncprims.h>
#include <map>
#include <memory>
#include <vector>


namespace logging {
	namespace spi {

		/**
		 * This is the base class used to implement the functionality required
		 * by the ObjectRegistry template class.
		 */
		class LOGGING_EXPORT ObjectRegistryBase {
		public:
			// public methods
			  /**
			   * Tests to see whether or not an object is bound in the
			   * registry as <code>name</code>.
			   */
			bool exists(const logging::tstring& name) const;

			/**
			 * Returns the names of all registered objects.
			 */
			std::vector<logging::tstring> getAllNames() const;

			//! This function is internal implementation detail.
			//! It is related to work-around needed for initialization when
			//! using C++11 threads and mutexes.
			void _enableLocking(bool);

		protected:
			// Ctor and Dtor
			ObjectRegistryBase();
			virtual ~ObjectRegistryBase();

			// protected methods
			  /**
			   * Used to enter an object into the registry.  (The registry now
			   * owns <code>object</code>.)
			   */
			bool putVal(const logging::tstring& name, void* object);

			/**
			 * Used to retrieve an object from the registry.  (The registry
			 * owns the returned pointer.)
			 */
			void* getVal(const logging::tstring& name) const;

			/**
			 * Deletes <code>object</code>.
			 */
			virtual void deleteObject(void *object) const = 0;

			/**
			 * Deletes all objects from this registry.
			 */
			virtual void clear();

			// Types
			typedef std::map<logging::tstring, void*> ObjectMap;

			// Data
			thread::Mutex mutex;
			ObjectMap data;

		private:
			ObjectRegistryBase(ObjectRegistryBase const &);
			ObjectRegistryBase & operator = (ObjectRegistryBase const &);

			bool volatile locking;
		};

	}
}


#endif // LOGGING_SPI_OBJECT_REGISTRY_HEADER_

