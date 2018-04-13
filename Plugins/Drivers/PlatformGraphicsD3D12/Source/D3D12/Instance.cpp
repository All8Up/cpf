//////////////////////////////////////////////////////////////////////////
#include "Driver/D3D12/Instance.hpp"
#include "CPF/Plugin/iClassFactory.hpp"

#include "Driver/D3D12/D3D12Utils.hpp"
#include "Driver/D3D12/SwapChain.hpp"

#include "Driver/D3D12/Adapter.hpp"
#include "Driver/D3D12/Device.hpp"
#include "Driver/D3D12/CommandBuffer.hpp"
#include "Driver/D3D12/RenderPass.hpp"
#include "Driver/D3D12/FrameBuffer.hpp"

#include "CPF/IntrusivePtr.hpp"
#include "Driver/D3D12/Plugin.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/Logging.hpp"

using namespace CPF;
using namespace Driver;
using namespace D3D12;

//////////////////////////////////////////////////////////////////////////
Instance::Instance(Plugin::iRegistry* registry, GOM::iUnknown*)
	: mpRegistry(registry)
{
}

Instance::~Instance()
{
	CPF_LOG(D3D12, Info) << "Destroyed instance: " << intptr_t(this) << " - " << intptr_t(mpDXGIFactory2.Ptr());
}

GOM::Result CPF_STDCALL Instance::Initialize(const Graphics::InstanceDesc* desc)
{
	UINT flags = 0;
	if (desc->mEnableDebugLayer)
	{
		flags = DXGI_CREATE_FACTORY_DEBUG;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(mpDebugController.AsTypePP()))))
		{
			mpDebugController->EnableDebugLayer();
		}
	}
	CreateDXGIFactory2(flags, IID_PPV_ARGS(mpDXGIFactory2.AsTypePP()));

	//////////////////////////////////////////////////////////////////////////
	CPF_LOG(D3D12, Info) << "Created instance: " << intptr_t(this) << " - " << intptr_t(mpDXGIFactory2.Ptr());

	if (mpRegistry->Install(kAdapterCID, new Plugin::tClassFactory<Adapter>()) &&
		mpRegistry->Install(kDeviceCID, new Plugin::tClassFactory<Device>()) &&
		mpRegistry->Install(kCommandBufferCID, new Plugin::tClassFactory<CommandBuffer>()) &&
		mpRegistry->Install(kRenderPassCID, new Plugin::tClassFactory<RenderPass>()) &&
		mpRegistry->Install(kFrameBufferCID, new Plugin::tClassFactory<FrameBuffer>()))
		return GOM::kOK;
	return GOM::kInitializationFailure;
}

GOM::Result Instance::EnumerateAdapters(int* count, Graphics::iAdapter** adapters)
{
	if (count == nullptr)
		return GOM::kInvalidParameter;

	if (mpDXGIFactory2)
	{
		if (adapters)
		{
			for (int i = 0; i < *count; ++i)
			{
				IntrusivePtr<IDXGIAdapter1> adapter;
				if (SUCCEEDED(mpDXGIFactory2->EnumAdapters1(i, adapter.AsTypePP())))
				{
					IntrusivePtr<IDXGIAdapter2> adapter2;
					if (SUCCEEDED(adapter->QueryInterface(IID_PPV_ARGS(adapter2.AsTypePP()))))
					{
						DXGI_ADAPTER_DESC2 desc2;
						if (SUCCEEDED(adapter2->GetDesc2(&desc2)))
						{
							Graphics::iAdapter* adapterIface;
							if (GOM::Succeeded(mpRegistry->Create(nullptr, kAdapterCID, Graphics::iAdapter::kIID, reinterpret_cast<void**>(&adapterIface))))
							{
								D3D12::Adapter* d3dAdapter = static_cast<D3D12::Adapter*>(adapterIface);
								d3dAdapter->Initialize(adapter2);
								adapters[i] = d3dAdapter;
							}
						}
						else
							return GOM::kUnknownInterface;
					}
				}
				else
					return GOM::kUnknownInterface;
			}
			return GOM::kOK;
		}

		for (int i = 0;; ++i)
		{
			IntrusivePtr<IDXGIAdapter1> adapter;
			if (!SUCCEEDED(mpDXGIFactory2->EnumAdapters1(i, adapter.AsTypePP())))
			{
				*count = i;
				break;
			}
		}
		return GOM::kOK;
	}

	return GOM::kNotInitialized;
}


GOM::Result Instance::CreateDevice(D3D12::Adapter::iAdapter* adapter, Graphics::iDevice** device)
{
	if (adapter && device)
	{
		if (GOM::Succeeded(mpRegistry->Create(nullptr, kDeviceCID, Graphics::iDevice::kIID, reinterpret_cast<void**>(device))))
		{
			Device* dev = static_cast<Device*>(*device);
			if (GOM::Succeeded(dev->Initialize(mpRegistry, adapter)) &&
				GOM::Succeeded(dev->Initialize()))
				return GOM::kOK;
			(*device)->Release();
			*device = nullptr;
			return GOM::kInitializationFailure;
		}
		return GOM::kOutOfMemory;
	}
	return GOM::kInvalidParameter;
}
