//////////////////////////////////////////////////////////////////////////
#include "Driver/D3D12/Fence.hpp"
#include "Driver/D3D12/Device.hpp"
#include "CPF/Logging.hpp"

using namespace CPF;
using namespace Driver;
using namespace D3D12;

Fence::Fence(Device* device, bool signaled)
	: mTarget(signaled ? 0 : 1)
{
	device->GetD3DDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(mpFence.AsTypePP()));
	mEvent = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET | (signaled ? CREATE_EVENT_INITIAL_SET : 0), EVENT_ALL_ACCESS);

	CPF_LOG(D3D12, Info) << "Created fence: " << intptr_t(this) << " - " << intptr_t(mpFence.Ptr());
}

Fence::~Fence()
{
	CloseHandle(mEvent);
	CPF_LOG(D3D12, Info) << "Destroyed fence: " << intptr_t(this) << " - " << intptr_t(mpFence.Ptr());
}

Graphics::FenceStatus Fence::GetStatus() const
{
	return mpFence->GetCompletedValue() == mTarget ? Graphics::FenceStatus::eReady : Graphics::FenceStatus::eNotReady;
}

void CPF_STDCALL Fence::Reset()
{
	++mTarget;
	ResetEvent(mEvent);
}

Graphics::FenceStatus CPF_STDCALL Fence::Wait() const
{
	mpFence->SetEventOnCompletion(mTarget, mEvent);
	const auto result = WaitForSingleObject(mEvent, INFINITE);
	return result == WAIT_OBJECT_0 ? Graphics::FenceStatus::eReady : Graphics::FenceStatus::eInvalid;
}
