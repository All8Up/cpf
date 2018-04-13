//////////////////////////////////////////////////////////////////////////
#include "Driver/D3D12.hpp"
#include "CPF/Platform/Graphics.hpp"
#include "CPF/Plugin/tClassFactory.hpp"
#include "Driver/D3D12/Plugin.hpp"
#include "Driver/D3D12/Instance.hpp"
#include "CPF/Logging.hpp"
#include "CPF/Plugin.hpp"

using namespace CPF;
using namespace Driver;

//////////////////////////////////////////////////////////////////////////
static Plugin::IID_CID sImplementations[] =
{
	{ Graphics::iInstance::kIID, D3D12::kD3D12InstanceCID }
};

//////////////////////////////////////////////////////////////////////////
static GOM::Result CPF_STDCALL Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		CPF_INIT_LOG(D3D12);
		registry->Install(D3D12::kD3D12InstanceCID, new Plugin::tClassFactory<D3D12::Instance>());
		registry->ClassInstall(sizeof(sImplementations) / sizeof(Plugin::IID_CID), sImplementations);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

static GOM::Result CPF_STDCALL Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->ClassRemove(sizeof(sImplementations) / sizeof(Plugin::IID_CID), sImplementations);
		registry->Remove(D3D12::kD3D12InstanceCID);
		CPF_DROP_LOG(D3D12);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

CPF_REGISTER_PLUGIN(PlatformGraphicsD3D12)
	&Install,
	&Remove
};
