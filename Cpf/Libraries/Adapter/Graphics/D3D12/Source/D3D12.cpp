//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12.hpp"
#include "Graphics.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Adapter/D3D12/Instance.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;

namespace
{
	int s_RefCount = 0;
	Plugin::iRegistry* gRegistry = nullptr;
}


struct InstanceClassInstance : public Plugin::iClassInstance
{
	InstanceClassInstance(Plugin::iRegistry* regy, int32_t* externalRef)
		: mRefCount(1)
		, mExternalRef(externalRef)
	{}

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

	COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry* regy, COM::iUnknown*, COM::iUnknown** outIface) override
	{
		if (outIface)
		{
			*outIface = new Adapter::D3D12::Instance(regy);
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

//////////////////////////////////////////////////////////////////////////

CPF_EXPORT_ADAPTER_D3D12 int D3D12Initializer::Install(Plugin::iRegistry* regy)
{
	if (++s_RefCount == 1)
	{
		CPF_ASSERT(regy != nullptr);
		gRegistry = regy;
		CPF_INIT_LOG(D3D12);

		regy->Install(kD3D12InstanceCID, new InstanceClassInstance(regy, &s_RefCount));
	}
	return s_RefCount;
}

CPF_EXPORT_ADAPTER_D3D12 int D3D12Initializer::Remove()
{
	if ((--s_RefCount) == 0)
	{
		CPF_ASSERT(gRegistry != nullptr);

		gRegistry->Remove(kD3D12InstanceCID);
		CPF_DROP_LOG(D3D12);
		gRegistry = nullptr;
	}
	return s_RefCount;
}
