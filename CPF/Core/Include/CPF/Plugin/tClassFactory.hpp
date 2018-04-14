//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Plugin/iClassFactory.hpp"

namespace CPF
{
	namespace Plugin
	{
		/**
		* @brief A helper to create class factories.
		* @tparam TYPE Type of instance to create.
		*/
		template <typename TYPE>
		struct tClassFactory : iClassFactory
		{
		private:
			/**
			@brief Determine which constuctor signature is available.
			@tparam TYPE Type of the class being constructed.
			*/
			template <typename TYPE>
			struct ClassConstructorType
			{
				static constexpr int Variant =
					std::is_constructible<TYPE>::value ? 1 : 0 |
					std::is_constructible<TYPE, iRegistry*>::value ? 2 : 0 |
					std::is_constructible<TYPE, iRegistry*, GOM::iUnknown*>::value ? 4 : 0 |
					std::is_constructible<TYPE, GOM::iUnknown*>::value ? 8 : 0;
			};

			template <typename TYPE, int VARIANT>
			struct InstanceCreator;

		public:
			tClassFactory() : mRefCount(1) {}
			virtual ~tClassFactory() {}

			GOM::Result CPF_STDCALL QueryInterface(GOM::IID, void**) override
			{
				return GOM::kNotImplemented;
			}
			int32_t CPF_STDCALL AddRef() override
			{
				return ++mRefCount;
			}
			int32_t CPF_STDCALL Release() override
			{
				if (--mRefCount == 0)
				{
					delete this;
					return 0;
				}
				return mRefCount;
			}

			GOM::Result CPF_STDCALL CreateInstance(iRegistry* regy, iUnknown* outer, iUnknown** outIface) override
			{
				if (outIface)
				{
					return InstanceCreator<TYPE, ClassConstructorType<TYPE>::Variant>::Create(regy, outer, outIface);
				}
				return GOM::kInvalidParameter;
			}

		private:
			int32_t mRefCount;

			template <typename TYPE>
			struct InstanceCreator<TYPE, 1>
			{
				static GOM::Result Create(iRegistry*, GOM::iUnknown*, GOM::iUnknown** outIface)
				{
					*outIface = new TYPE();
					if (*outIface)
						return GOM::kOK;
					return GOM::kOutOfMemory;
				}
			};
			template <typename TYPE>
			struct InstanceCreator<TYPE, 2>
			{
				static GOM::Result Create(iRegistry* regy, GOM::iUnknown*, GOM::iUnknown** outIface)
				{
					*outIface = new TYPE(regy);
					if (*outIface)
						return GOM::kOK;
					return GOM::kOutOfMemory;
				}
			};
			template <typename TYPE>
			struct InstanceCreator<TYPE, 4>
			{
				static GOM::Result Create(iRegistry* regy, GOM::iUnknown* outer, GOM::iUnknown** outIface)
				{
					*outIface = new TYPE(regy, outer);
					if (*outIface)
						return GOM::kOK;
					return GOM::kOutOfMemory;
				}
			};
			template <typename TYPE>
			struct InstanceCreator<TYPE, 8>
			{
				static GOM::Result Create(iRegistry*, GOM::iUnknown* outer, GOM::iUnknown** outIface)
				{
					*outIface = new TYPE(outer);
					if (*outIface)
						return GOM::kOK;
					return GOM::kOutOfMemory;
				}
			};
		};
	}
}
