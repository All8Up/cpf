//////////////////////////////////////////////////////////////////////////
#include "Adapters/D3D12/Adapter.hpp"
#include "Adapters/D3D12/SwapChain.hpp"
#include "IntrusivePtr.hpp"
#include <d3d12.h>
#include "Adapters/D3D12/Output.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapters;
using namespace D3D12;

//////////////////////////////////////////////////////////////////////////
Adapter::Adapter(IDXGIAdapter2* adapter)
	: mpAdapter(adapter)
{
	mpAdapter->AddRef();
	mpAdapter->GetDesc2(&mDesc);

	::memset(mDescription, 0, sizeof(mDescription));
	for (int i = 0; i < sizeof(mDesc.Description) && mDesc.Description[i] != 0; ++i)
		mDescription[i] = char(mDesc.Description[i]);

	CPF_LOG(D3D12, Info) << "Created adapter: " << intptr_t(this) << " - " << intptr_t(mpAdapter.Ptr());
}

Adapter::~Adapter()
{
	CPF_LOG(D3D12, Info) << "Destroyed adapter: " << intptr_t(this) << " - " << intptr_t(mpAdapter.Ptr());
}

const char* Adapter::GetDescription() const
{
	return mDescription;
}

size_t Adapter::GetVideoMemory() const
{
	return mDesc.DedicatedVideoMemory;
}

size_t Adapter::GetSystemMemory() const
{
	return mDesc.DedicatedSystemMemory;
}

size_t Adapter::GetSharedMemory() const
{
	return mDesc.SharedSystemMemory;
}

bool Adapter::IsSoftware() const
{
	return (mDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) != 0;
}

bool Adapter::IsRemote() const
{
	return (mDesc.Flags & DXGI_ADAPTER_FLAG_REMOTE) != 0;
}

bool Adapter::EnumerateOutputs(int32_t& count, Graphics::iOutput** outputs) const
{
	if (outputs && count != 0)
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
	}
	else
	{
		count = 0;
		UINT index = 0;
		for (IDXGIOutput* output = nullptr; SUCCEEDED(mpAdapter->EnumOutputs(index, &output)); ++index)
			output->Release();
		count = int32_t(index);
		return true;
	}
	return false;
}
