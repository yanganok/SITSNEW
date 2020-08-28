#ifndef LOGGING_SPI_FACTORY_HEADER_
#define LOGGING_SPI_FACTORY_HEADER_

#include <logging/config.hxx>

#if defined (LOGGING_HAVE_PRAGMA_ONCE)
#pragma once
#endif

#include <logging/appender.h>
#include <logging/layout.h>
#include <logging/tstring.h>
#include <logging/spi/filter.h>
#include <logging/spi/objectregistry.h>
#include <memory>
#include <vector>
#include <locale>


namespace logging {
	namespace spi {

		/**
		 * This is the base class for all factories.
		 */
		class LOGGING_EXPORT BaseFactory {
		public:
			virtual ~BaseFactory() = 0;

			/**
			 * Returns the typename of the objects this factory creates.
			 */
			virtual logging::tstring const & getTypeName() const = 0;
		};


		/**
		 * This abstract class defines the "Factory" interface to create "Appender"
		 * objects.
		 */
		class LOGGING_EXPORT AppenderFactory : public BaseFactory {
		public:
			typedef Appender ProductType;
			typedef SharedAppenderPtr ProductPtr;

			AppenderFactory();
			virtual ~AppenderFactory() = 0;

			/**
			 * Create an "Appender" object.
			 */
			virtual SharedAppenderPtr createObject(const logging::helpers::Properties& props) = 0;
		};



		/**
		 * This abstract class defines the "Factory" interface to create "Layout"
		 * objects.
		 */
		class LOGGING_EXPORT LayoutFactory : public BaseFactory {
		public:
			typedef Layout ProductType;
			typedef std::unique_ptr<Layout> ProductPtr;

			LayoutFactory();
			virtual ~LayoutFactory() = 0;

			/**
			 * Create a "Layout" object.
			 */
			virtual std::unique_ptr<Layout> createObject(const logging::helpers::Properties& props) = 0;
		};



		/**
		 * This abstract class defines the "Factory" interface to create "Appender"
		 * objects.
		 */
		class LOGGING_EXPORT FilterFactory : public BaseFactory {
		public:
			typedef Filter ProductType;
			typedef FilterPtr ProductPtr;

			FilterFactory();
			virtual ~FilterFactory() = 0;

			/**
			 * Create a "Filter" object.
			 */
			virtual FilterPtr createObject(const logging::helpers::Properties& props) = 0;
		};


		/**
		 * This abstract class defines the "Factory" interface to
		 * create std::locale instances.
		 */
		class LOGGING_EXPORT LocaleFactory
			: public BaseFactory
		{
		public:
			typedef std::locale ProductType;
			typedef std::locale ProductPtr;

			LocaleFactory();
			virtual ~LocaleFactory() = 0;

			//! \returns std::locale instance
			virtual ProductPtr createObject(
				const logging::helpers::Properties & props) = 0;
		};


		/**
		 * This template class is used as a "Factory Registry".  Objects are
		 * "entered" into the registry with a "name" using the
		 * <code>put()</code> method.  (The registry then owns the object.)
		 * These object can then be retrieved using the <code>get()</code>
		 * method.
		 *
		 * <b>Note:</b>  This class is Thread-safe.
		 */
		template<class T>
		class LOGGING_EXPORT FactoryRegistry
			: public ObjectRegistryBase
		{
		public:
			typedef T product_type;

			virtual ~FactoryRegistry() {
				clear();
			}

			// public methods
			  /**
			   * Used to enter an object into the registry.  (The registry now
			   *  owns <code>object</code>.)
			   */
			bool put(std::unique_ptr<T> object) {
				bool putValResult = putVal(object->getTypeName(), object.get());
				object.release();
				return putValResult;
			}

			/**
			 * Used to retrieve an object from the registry.  (The registry
			 * owns the returned pointer.)
			 */
			T* get(const logging::tstring& name) const {
				return static_cast<T*>(getVal(name));
			}

		protected:
			virtual void deleteObject(void *object) const {
				delete static_cast<T*>(object);
			}
		};


		typedef FactoryRegistry<AppenderFactory> AppenderFactoryRegistry;
		typedef FactoryRegistry<LayoutFactory> LayoutFactoryRegistry;
		typedef FactoryRegistry<FilterFactory> FilterFactoryRegistry;
		typedef FactoryRegistry<LocaleFactory> LocaleFactoryRegistry;


		/**
		 * Returns the "singleton" <code>AppenderFactoryRegistry</code>.
		 */
		LOGGING_EXPORT AppenderFactoryRegistry& getAppenderFactoryRegistry();

		/**
		 * Returns the "singleton" <code>LayoutFactoryRegistry</code>.
		 */
		LOGGING_EXPORT LayoutFactoryRegistry& getLayoutFactoryRegistry();

		/**
		 * Returns the "singleton" <code>FilterFactoryRegistry</code>.
		 */
		LOGGING_EXPORT FilterFactoryRegistry& getFilterFactoryRegistry();

		/**
		 * Returns the "singleton" <code>LocaleFactoryRegistry</code>.
		 */
		LOGGING_EXPORT LocaleFactoryRegistry& getLocaleFactoryRegistry();


		template <typename ProductFactoryBase>
		class LocalFactoryBase
			: public ProductFactoryBase
		{
		public:
			LocalFactoryBase(tchar const * n)
				: name(n)
			{ }

			virtual logging::tstring const & getTypeName() const
			{
				return name;
			}

		private:
			logging::tstring name;
		};


		template <typename LocalProduct, typename ProductFactoryBase>
		class FactoryTempl
			: public LocalFactoryBase<ProductFactoryBase>
		{
		public:
			typedef typename ProductFactoryBase::ProductPtr ProductPtr;

			FactoryTempl(tchar const * n)
				: LocalFactoryBase<ProductFactoryBase>(n)
			{ }

			virtual ProductPtr createObject(helpers::Properties const & props)
			{
				return ProductPtr(new LocalProduct(props));
			}
		};


#define LOGGING_REG_PRODUCT(reg, productprefix, productname, productns, productfact) \
        reg.put (																               \
            std::unique_ptr<productfact> (                                                     \
                    new logging::spi::FactoryTempl<productns productname, productfact> (     \
                    LOGGING_TEXT(productprefix)                                              \
                    LOGGING_TEXT(#productname))))

#define LOGGING_REG_APPENDER(reg, appendername)                             \
        LOGGING_REG_PRODUCT (reg, "logging::", appendername, logging::,         \
            logging::spi::AppenderFactory)

#define LOGGING_REG_LAYOUT(reg, layoutname)                                 \
        LOGGING_REG_PRODUCT (reg, "logging::", layoutname, logging::,           \
            logging::spi::LayoutFactory)

#define LOGGING_REG_FILTER(reg, filtername)                                 \
        LOGGING_REG_PRODUCT (reg, "logging::spi::", filtername, logging::spi::, \
            logging::spi::FilterFactory)

#define LOGGING_REG_LOCALE(reg, name, factory)            \
            reg.put (std::unique_ptr<logging::spi::LocaleFactory> ( \
                    new factory (name)))
	} // namespace spi
}


#endif // LOGGING_SPI_FACTORY_HEADER_
