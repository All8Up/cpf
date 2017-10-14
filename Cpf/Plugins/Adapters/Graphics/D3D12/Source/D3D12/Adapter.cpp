//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/Adapter.hpp"
#include "Adapter/D3D12/SwapChain.hpp"
#include "Adapter/D3D12/Output.hpp"
#include "IntrusivePtr.hpp"
#include <d3d12.h>
#include "CPF/Logging.hpp"

using namespace CPF;
using namespace Adapter;

//////////////////////////////////////////////////////////////////////////
D3D12::Adapter::Adapter(Plugin::iRegistry*, GOM::iUnknown*)
	: mpAdapter(nullptr)
{
}

D3D12::Adapter::~Adapter()
{
	CPF_LOG(D3D12, Info) << "Destroyed adapter: " << intptr_t(this) << " - " << intptr_t(mpAdapter.Ptr());
}

GOM::Result D3D12::Adapter::Initialize(IDXGIAdapter2* adapter)
{
	mpAdapter.Adopt(adapter);
	mpAdapter->AddRef();
	mpAdapter->GetDesc2(&mDesc);

	::memset(mDescription, 0, sizeof(mDescription));
	for (int i = 0; i < sizeof(mDesc.Description) && mDesc.Description[i] != 0; ++i)
		mDescription[i] = char(mDesc.Description[i]);

	CPF_LOG(D3D12, Info) << "Created adapter: " << intptr_t(this) << " - " << intptr_t(mpAdapter.Ptr());
	return GOM::kOK;
}

GOM::Result CPF_STDCALL D3D12::Adapter::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;
		case Graphics::iAdapter::kIID.GetID():
			*outIface = static_cast<Graphics::iAdapter*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}


const char* CPF_STDCALL D3D12::Adapter::GetDescription() const
{
	return mDescription;
}

size_t CPF_STDCALL D3D12::Adapter::GetVideoMemory() const
{
	return mDesc.DedicatedVideoMemory;
}

size_t CPF_STDCALL D3D12::Adapter::GetSystemMemory() const
{
	return mDesc.DedicatedSystemMemory;
}

size_t CPF_STDCALL D3D12::Adapter::GetSharedMemory() const
{
	return mDesc.SharedSystemMemory;
}

bool CPF_STDCALL D3D12::Adapter::IsSoftware() const
{
	return (mDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) != 0;
}

bool CPF_STDCALL D3D12::Adapter::IsRemote() const
{
	return (mDesc.Flags & DXGI_ADAPTER_FLAG_REMOTE) != 0;
}

GOM::Result CPF_STDCALL D3D12::Adapter::EnumerateOutputs(int32_t* count, Graphics::iOutput** outputs) const
{
	if (outputs && count && *count != 0)
	{
		UINT index = 0;
		for (IDXGIOutput* output = nullptr; SUCCEEDED(mpAdapter->EnumOutputs(index, &output)); ++index)
		{
			IDXGIOutput4* output4 = nullptr;
			if (SUCCEEDED(output->QueryInterface(IID_PPV_ARGS(&output4))))
			{
				outputs[index] = new Output(output4);
				output->Release();
			}
			else
				output->Release();
		}
		return GOM::kOK;
	}
	else
	{
		if (count)
		{
			*count = 0;
			UINT index = 0;
			for (IDXGIOutput* output = nullptr; SUCCEEDED(mpAdapter->EnumOutputs(index, &output)); ++index)
				output->Release();
			*count = int32_t(index);
			return GOM::kOK;
		}
	}
	return GOM::kInvalidParameter;
}
