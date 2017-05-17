//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace Cpf
{
	namespace Plugin
	{
		struct iRegistry;

		struct IID_CID
		{
			GOM::InterfaceID mIID;
			GOM::ClassID mCID;
		};

		/** @brief The class instance interface.  Added to iRegistry to create component instances. */
		struct iClassInstance : GOM::iUnknown
		{
			virtual GOM::Result CPF_STDCALL CreateInstance(iRegistry*, GOM::iUnknown*, GOM::iUnknown**) = 0;
		};

		/**
		 * @brief A helper to create class instances.
		 * @tparam TYPE Type of instance to create.
		 */
		template <typename TYPE>
		struct tClassInstance : public iClassInstance
		{
			tClassInstance(int32_t* externalRef = nullptr) : mRefCount(1), mExternalRef(externalRef) {}
			virtual ~tClassInstance() {}

			GOM::Result CPF_STDCALL QueryInterface(GOM::InterfaceID, void**) override { return GOM::kNotImplemented; }
			int32_t CPF_STDCALL AddRef() override { return ++mRefCount; }
			int32_t CPF_STDCALL Release() override
			{
				if (--mRefCount == 0)
				{
					delete this;
					return 0;
				}
				return mRefCount;
			}

			GOM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, GOM::iUnknown* outer, GOM::iUnknown** outIface) override
			{
				if (outIface)
				{
					*outIface = new TYPE(outer);
					if (*outIface)
					{
						if (mExternalRef)
							++*mExternalRef;
						return GOM::kOK;
					}
					return GOM::kOutOfMemory;
				}
				return GOM::kInvalidParameter;
			}

		private:
			int32_t mRefCount;
			int32_t* mExternalRef;
		};
	}
}

#define CPF_CLASSINSTANCE_ACCESS(name) friend struct Cpf::Plugin::tClassInstance<name>;
