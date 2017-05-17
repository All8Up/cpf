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

GOM::Result CPF_STDCALL Fence::QueryInterface(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;
		case iFence::kIID.GetID():
			*outIface = static_cast<iFence*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
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
