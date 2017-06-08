//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12.hpp"
#include "Graphics/Driver.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Adapter/D3D12/Plugin.hpp"
#include "Adapter/D3D12/Instance.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;

//////////////////////////////////////////////////////////////////////////
static Plugin::IID_CID sImplementations[] =
{
	{ Graphics::iInstance::kIID.GetID(), D3D12::kD3D12InstanceCID.GetID() }
};

//////////////////////////////////////////////////////////////////////////

int D3D12Initializer::Install(Plugin::iRegistry* regy)
{
	if (D3D12::gContext.AddRef() == 1)
	{
		CPF_ASSERT(regy != nullptr);
		D3D12::gContext.SetRegistry(regy);
		CPF_INIT_LOG(D3D12);

		regy->Install(D3D12::kD3D12InstanceCID.GetID(), new Plugin::tClassInstance<D3D12::Instance>());
		regy->ClassInstall(sizeof(sImplementations) / sizeof(Plugin::IID_CID), sImplementations);
	}
	return D3D12::gContext.GetRefCount();
}

int D3D12Initializer::Remove()
{
	if (D3D12::gContext.Release() == 0)
	{
		D3D12::gContext.GetRegistry()->ClassRemove(sizeof(sImplementations) / sizeof(Plugin::IID_CID), sImplementations);
		D3D12::gContext.GetRegistry()->Remove(D3D12::kD3D12InstanceCID.GetID());
		CPF_DROP_LOG(D3D12);

		D3D12::gContext.SetRegistry(nullptr);
	}
	return D3D12::gContext.GetRefCount();
}


//////////////////////////////////////////////////////////////////////////
extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return D3D12Initializer::Install(registry) > 0 ? GOM::kOK : GOM::kInitializationFailure;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT CanUnload()
{
	return (D3D12::gContext.GetRefCount() == 0) ? GOM::kOK : GOM::kInUse;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		D3D12Initializer::Remove();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
