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

CPF_EXPORT_ADAPTER_D3D12 int D3D12Initializer::Install(Plugin::iRegistry* regy)
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

CPF_EXPORT_ADAPTER_D3D12 int D3D12Initializer::Remove()
{
	if (D3D12::gContext.Release() == 0)
	{
		D3D12::gContext.GetRegistry()->Remove(kD3D12InstanceCID);
		CPF_DROP_LOG(D3D12);

		D3D12::gContext.SetRegistry(nullptr);
	}
	return D3D12::gContext.GetRefCount();
}
