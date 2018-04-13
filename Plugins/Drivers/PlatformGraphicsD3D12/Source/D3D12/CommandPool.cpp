//////////////////////////////////////////////////////////////////////////
#include "Driver/D3D12/CommandPool.hpp"
#include "Driver/D3D12/Device.hpp"
#include "CPF/Logging.hpp"
#include "CPF/GOM/ResultCodes.hpp"

using namespace CPF;
using namespace Driver;
using namespace D3D12;

CommandPool::CommandPool()
{
}

CommandPool::~CommandPool()
{
	CPF_LOG(D3D12, Info) << "Destroyed command pool: " << intptr_t(this) << " - " << intptr_t(mpCommandPool.Ptr());
}

GOM::Result CPF_STDCALL CommandPool::Initialize(Device* device)
{
	device->GetD3DDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(mpCommandPool.AsTypePP()));
	CPF_LOG(D3D12, Info) << "Created command pool: " << intptr_t(this) << " - " << intptr_t(mpCommandPool.Ptr());
	return GOM::kOK;
}

void CommandPool::Reset()
{
	mpCommandPool->Reset();
}
