//////////////////////////////////////////////////////////////////////////
#include "Adapters/D3D12/CommandPool.hpp"
#include "Adapters/D3D12/Device.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapters;
using namespace D3D12;

CommandPool::CommandPool(Device* device)
{
	device->GetD3DDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(mpCommandPool.AsTypePP()));
	CPF_LOG(D3D12, Info) << "Created command pool: " << intptr_t(this) << " - " << intptr_t(mpCommandPool.Ptr());
}

CommandPool::~CommandPool()
{
	CPF_LOG(D3D12, Info) << "Destroyed command pool: " << intptr_t(this) << " - " << intptr_t(mpCommandPool.Ptr());
}

void CommandPool::Reset()
{
	mpCommandPool->Reset();
}
