//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12.hpp"
#include "Graphics.hpp"
#include "Plugin/tClassInstance.hpp"
#include "Adapter/D3D12/Plugin.hpp"
#include "Adapter/D3D12/Instance.hpp"
#include "Logging/Logging.hpp"

using namespace CPF;
using namespace Adapter;

//////////////////////////////////////////////////////////////////////////
static Plugin::IID_CID sImplementations[] =
{
	{ Graphics::iInstance::kIID.GetID(), D3D12::kD3D12InstanceCID.GetID() }
};

//////////////////////////////////////////////////////////////////////////

int D3D12Initializer::Install(Plugin::iRegistry* regy)
{
	CPF_INIT_LOG(D3D12);

	regy->Install(D3D12::kD3D12InstanceCID.GetID(), new Plugin::tClassInstance<D3D12::Instance>());
	regy->ClassInstall(sizeof(sImplementations) / sizeof(Plugin::IID_CID), sImplementations);
	return 1;
}

int D3D12Initializer::Remove(Plugin::iRegistry* regy)
{
	regy->ClassRemove(sizeof(sImplementations) / sizeof(Plugin::IID_CID), sImplementations);
	regy->Remove(D3D12::kD3D12InstanceCID.GetID());
	CPF_DROP_LOG(D3D12);
	return 0;
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
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		D3D12Initializer::Remove(registry);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
