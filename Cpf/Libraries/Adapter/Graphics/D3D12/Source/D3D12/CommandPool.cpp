//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/CommandPool.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

CommandPool::CommandPool(Device* device CPF_GFX_DEBUG_PARAM_DEF)
{
	device->GetD3DDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(mpCommandPool.AsTypePP()));
	CPF_LOG(D3D12, Info) << "Created command pool: " << intptr_t(this) << " - " << intptr_t(mpCommandPool.Ptr());

#ifdef CPF_GFX_TRACKING
	if (dbgFilename)
	{
		std::wstringstream str;
		str << dbgFilename << " : " << dbgLineNumber;
		mpCommandPool->SetName(str.str().c_str());
	}
#endif
}

CommandPool::~CommandPool()
{
	CPF_LOG(D3D12, Info) << "Destroyed command pool: " << intptr_t(this) << " - " << intptr_t(mpCommandPool.Ptr());
}

void CommandPool::Reset()
{
	mpCommandPool->Reset();
}
