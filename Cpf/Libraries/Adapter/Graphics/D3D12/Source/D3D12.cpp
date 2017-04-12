//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12.hpp"
#include "Graphics.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Adapter/D3D12/Plugin.hpp"
#include "Adapter/D3D12/Instance.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;

//////////////////////////////////////////////////////////////////////////
class D3D12Class : public tRefCounted<Plugin::iClassInstance>
{
public:
	COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**)
	{
		return COM::kNotImplemented;
	}

	COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown*, COM::iUnknown** outIface) override
	{
		if (outIface)
		{
			*outIface = new D3D12::Instance();
			if (*outIface)
			{
				return COM::kOK;
			}
			return COM::kOutOfMemory;
		}
		return COM::kInvalidParameter;
	}

	COM::Result CPF_STDCALL GetInterfaces(int32_t* count, COM::InterfaceID* iidList) override
	{
		if (count)
		{
			if (iidList)
			{
				if (*count < 1)
					return COM::kNotEnoughSpace;
				*count = 1;
				iidList[0] = Graphics::iInstance::kIID;
				return COM::kOK;
			}
			else
			{
				*count = 1;
				return COM::kOK;
			}
		}
		return COM::kInvalidParameter;
	}

	COM::Result CPF_STDCALL GetClasses(COM::InterfaceID iid, int32_t* count, COM::ClassID* cidList) override
	{
		if (count)
		{
			if (cidList)
			{
				if (iid == Graphics::iInstance::kIID)
				{
					*count = 1;
					cidList[0] = D3D12::kD3D12InstanceCID;
					return COM::kOK;
				}
				*count = 0;
				return COM::kOK;
			}
			else
			{
				if (iid == Graphics::iInstance::kIID)
				{
					*count = 1;
					return COM::kOK;
				}
				*count = 0;
				return COM::kOK;
			}
		}
		return COM::kInvalidParameter;
	}
};

//////////////////////////////////////////////////////////////////////////

int D3D12Initializer::Install(Plugin::iRegistry* regy)
{
	if (D3D12::gContext.AddRef() == 1)
	{
		CPF_ASSERT(regy != nullptr);
		D3D12::gContext.SetRegistry(regy);
		CPF_INIT_LOG(D3D12);

		regy->Install(D3D12::kD3D12InstanceCID, new D3D12Class());
	}
	return D3D12::gContext.GetRefCount();
}

int D3D12Initializer::Remove()
{
	if (D3D12::gContext.Release() == 0)
	{
		D3D12::gContext.GetRegistry()->Remove(D3D12::kD3D12InstanceCID);
		CPF_DROP_LOG(D3D12);

		D3D12::gContext.SetRegistry(nullptr);
	}
	return D3D12::gContext.GetRefCount();
}


//////////////////////////////////////////////////////////////////////////
extern "C"
COM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return D3D12Initializer::Install(registry) > 0 ? COM::kOK : COM::kInitializationFailure;
	}
	return COM::kInvalidParameter;
}

extern "C"
COM::Result CPF_EXPORT CanUnload()
{
	return (D3D12::gContext.GetRefCount() == 0) ? COM::kOK : COM::kInUse;
}

extern "C"
COM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		D3D12Initializer::Remove();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}
