//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Plugin
	{
		struct iRegistry;

		struct iClassInstance : COM::iUnknown
		{
			virtual COM::Result CPF_STDCALL CreateInstance(iRegistry*, COM::iUnknown*, COM::iUnknown**) = 0;
			virtual int32_t CPF_STDCALL GetImplementsCount() = 0;
			virtual COM::Result CPF_STDCALL GetImplements(int32_t, COM::InterfaceID*, COM::ClassID*) = 0;
		};

		template <typename TYPE>
		struct tSimpleClassInstance : public iClassInstance
		{
			tSimpleClassInstance(int32_t* externalRef = nullptr) : mRefCount(1), mExternalRef(externalRef) {}

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

			COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown*, COM::iUnknown** outIface) override
			{
				if (outIface)
				{
					*outIface = new TYPE();
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

			int32_t CPF_STDCALL GetImplementsCount() override { return 0; }
			COM::Result CPF_STDCALL GetImplements(int32_t, COM::InterfaceID*, COM::ClassID*) override { return COM::kOutOfRange; }

		private:
			int32_t mRefCount;
			int32_t* mExternalRef;
		};
	}
}

#define CPF_CLASSINSTANCE_ACCESS(name) friend struct Cpf::Plugin::tSimpleClassInstance<name>;
