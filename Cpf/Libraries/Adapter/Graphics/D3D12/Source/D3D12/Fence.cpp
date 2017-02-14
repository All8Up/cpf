//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/Fence.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

Fence::Fence(Device* device, int64_t initValue)
{
	device->GetD3DDevice()->CreateFence(initValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(mpFence.AsTypePP()));
	mEvent = CreateEventEx(NULL, FALSE, FALSE, EVENT_ALL_ACCESS);

	CPF_LOG(D3D12, Info) << "Created fence: " << intptr_t(this) << " - " << intptr_t(mpFence.Ptr());
}

Fence::~Fence()
{
	CloseHandle(mEvent);
	CPF_LOG(D3D12, Info) << "Destroyed fence: " << intptr_t(this) << " - " << intptr_t(mpFence.Ptr());
}

uint64_t Fence::GetValue() const
{
	return mpFence->GetCompletedValue();
}

void Fence::WaitFor(uint64_t value)
{
	mpFence->SetEventOnCompletion(value, mEvent);
	WaitForSingleObject(mEvent, INFINITE);
}
