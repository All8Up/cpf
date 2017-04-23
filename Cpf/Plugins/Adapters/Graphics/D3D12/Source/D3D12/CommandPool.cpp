//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/CommandPool.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

CommandPool::CommandPool()
{
}

CommandPool::~CommandPool()
{
	CPF_LOG(D3D12, Info) << "Destroyed command pool: " << intptr_t(this) << " - " << intptr_t(mpCommandPool.Ptr());
}

COM::Result CPF_STDCALL CommandPool::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iCommandPool::kIID.GetID():
			*outIface = static_cast<iCommandPool*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL CommandPool::Initialize(Device* device)
{
	device->GetD3DDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(mpCommandPool.AsTypePP()));
	CPF_LOG(D3D12, Info) << "Created command pool: " << intptr_t(this) << " - " << intptr_t(mpCommandPool.Ptr());
	return COM::kOK;
}

void CommandPool::Reset()
{
	mpCommandPool->Reset();
}
