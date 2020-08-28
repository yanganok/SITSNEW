#include <logging/spi/objectregistry.h>
#include <logging/thread/syncprims-pub-impl.h>
#include <logging/thread/threads.h>


namespace logging {
	namespace spi {


		///////////////////////////////////////////////////////////////////////////////
		// ObjectRegistryBase ctor and dtor
		///////////////////////////////////////////////////////////////////////////////

		ObjectRegistryBase::ObjectRegistryBase()
			: locking(true)
		{ }


		ObjectRegistryBase::~ObjectRegistryBase()
		{ }



		///////////////////////////////////////////////////////////////////////////////
		// ObjectRegistryBase public methods
		///////////////////////////////////////////////////////////////////////////////

		bool
			ObjectRegistryBase::exists(const tstring& name) const
		{
			thread::MutexGuard guard(mutex);

			return data.find(name) != data.end();
		}


		std::vector<tstring>
			ObjectRegistryBase::getAllNames() const
		{
			std::vector<tstring> tmp;

			{
				thread::MutexGuard guard(mutex);
				tmp.reserve(data.size());
				for (auto const & kv : data)
					tmp.emplace_back(kv.first);
			}

			return tmp;
		}



		///////////////////////////////////////////////////////////////////////////////
		// ObjectRegistryBase protected methods
		///////////////////////////////////////////////////////////////////////////////

		bool
			ObjectRegistryBase::putVal(const tstring& name, void* object)
		{
			ObjectMap::value_type value(name, object);
			std::pair<ObjectMap::iterator, bool> ret;

			{
				thread::MutexGuard guard;
				if (locking)
					guard.attach_and_lock(mutex);

				ret = data.insert(std::move(value));
			}

			if (!ret.second)
				deleteObject(value.second);

			return ret.second;
		}


		void*
			ObjectRegistryBase::getVal(const tstring& name) const
		{
			thread::MutexGuard guard(mutex);

			ObjectMap::const_iterator it(data.find(name));
			if (it != data.end())
				return it->second;
			else
				return nullptr;
		}




		void
			ObjectRegistryBase::clear()
		{
			thread::MutexGuard guard(mutex);

			for (auto const & kv : data)
				deleteObject(kv.second);
		}


		void
			ObjectRegistryBase::_enableLocking(bool enable)
		{
			locking = enable;
		}


	}
} // namespace logging { namespace spi {
