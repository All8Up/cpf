//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Plugin
	{
		struct iRegistry;

		struct IID_CID
		{
			COM::InterfaceID mIID;
			COM::ClassID mCID;
		};

		/** @brief The class instance interface.  Added to iRegistry to create component instances. */
		struct iClassInstance : COM::iUnknown
		{
			virtual COM::Result CPF_STDCALL CreateInstance(iRegistry*, COM::iUnknown*, COM::iUnknown**) = 0;
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

			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }
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

			COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown* outer, COM::iUnknown** outIface) override
			{
				if (outIface)
				{
					*outIface = new TYPE(outer);
					if (*outIface)
					{
						if (mExternalRef)
							++*mExternalRef;
						return COM::kOK;
					}
					return COM::kOutOfMemory;
				}
				return COM::kInvalidParameter;
			}

		private:
			int32_t mRefCount;
			int32_t* mExternalRef;
		};
	}
}

#define CPF_CLASSINSTANCE_ACCESS(name) friend struct Cpf::Plugin::tClassInstance<name>;
