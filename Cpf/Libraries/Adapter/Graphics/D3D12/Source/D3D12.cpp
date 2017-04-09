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

int D3D12Initializer::Install(Plugin::iRegistry* regy)
{
	if (D3D12::gContext.AddRef() == 1)
	{
		CPF_ASSERT(regy != nullptr);
		D3D12::gContext.SetRegistry(regy);
		CPF_INIT_LOG(D3D12);

		regy->Install(kD3D12InstanceCID, new Plugin::tSimpleClassInstance<D3D12::Instance>());
	}
	return D3D12::gContext.GetRefCount();
}

int D3D12Initializer::Remove()
{
	if (D3D12::gContext.Release() == 0)
	{
		D3D12::gContext.GetRegistry()->Remove(kD3D12InstanceCID);
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
