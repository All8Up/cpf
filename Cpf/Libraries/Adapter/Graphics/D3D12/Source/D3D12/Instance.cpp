//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/Instance.hpp"
#include "Plugin/iClassInstance.hpp"

#include "Adapter/D3D12/D3D12Utils.hpp"
#include "Adapter/D3D12/SwapChain.hpp"

#include "Adapter/D3D12/Adapter.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Adapter/D3D12/CommandBuffer.hpp"
#include "Adapter/D3D12/RenderPass.hpp"
#include "Adapter/D3D12/FrameBuffer.hpp"

#include "IntrusivePtr.hpp"
#include "Adapter/D3D12/Plugin.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

//////////////////////////////////////////////////////////////////////////
Instance::Instance()
{
	UINT flags = 0;
#ifdef CPF_USE_D3D12_DEBUG_LAYER
	flags = DXGI_CREATE_FACTORY_DEBUG;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(mpDebugController.AsTypePP()))))
	{
		mpDebugController->EnableDebugLayer();
	}
#endif
	CreateDXGIFactory2(flags, IID_PPV_ARGS(mpDXGIFactory2.AsTypePP()));

	//////////////////////////////////////////////////////////////////////////
	// Register D3D12 class types.
	// TODO: Should likely be in the normal plugin install and not part of instance.
	gContext.GetRegistry()->Install(kAdapterCID, new Plugin::tSimpleClassInstance<Adapter>());
	gContext.GetRegistry()->Install(kDeviceCID, new Plugin::tSimpleClassInstance<Device>());
	gContext.GetRegistry()->Install(kCommandBufferCID, new Plugin::tSimpleClassInstance<CommandBuffer>());
	gContext.GetRegistry()->Install(kRenderPassCID, new Plugin::tSimpleClassInstance<RenderPass>());
	gContext.GetRegistry()->Install(kFrameBufferCID, new Plugin::tSimpleClassInstance<FrameBuffer>());
	//////////////////////////////////////////////////////////////////////////

	CPF_LOG(D3D12, Info) << "Created instance: " << intptr_t(this) << " - " << intptr_t(mpDXGIFactory2.Ptr());
}

Instance::~Instance()
{
	CPF_LOG(D3D12, Info) << "Destroyed instance: " << intptr_t(this) << " - " << intptr_t(mpDXGIFactory2.Ptr());
}

COM::Result CPF_STDCALL Instance::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iInstance::kIID.GetID():
			*outIface = static_cast<iInstance*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result Instance::EnumerateAdapters(int& count, Graphics::iAdapter** adapters)
{
	if (mpDXGIFactory2)
	{
		if (adapters)
		{
			for (int i = 0; i < count; ++i)
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
							if (Succeeded(gContext.GetRegistry()->Create(nullptr, kAdapterCID, Graphics::iAdapter::kIID, reinterpret_cast<void**>(&adapterIface))))
							{
								D3D12::Adapter* d3dAdapter = static_cast<D3D12::Adapter*>(adapterIface);
								d3dAdapter->Initialize(adapter2);
								adapters[i] = d3dAdapter;
							}
						}
						else
							return COM::kUnknownInterface;
					}
				}
				else
					return COM::kUnknownInterface;
			}
			return COM::kOK;
		}

		for (int i = 0;; ++i)
		{
			IntrusivePtr<IDXGIAdapter1> adapter;
			if (!SUCCEEDED(mpDXGIFactory2->EnumAdapters1(i, adapter.AsTypePP())))
			{
				count = i;
				break;
			}
		}
		return COM::kOK;
	}

	return COM::kNotInitialized;
}


COM::Result Instance::CreateDevice(D3D12::Adapter::iAdapter* adapter, Graphics::iDevice** device)
{
	if (adapter && device)
	{
		if (Succeeded(gContext.GetRegistry()->Create(nullptr, kDeviceCID, Graphics::iDevice::kIID, reinterpret_cast<void**>(device))))
		{
			Device* dev = static_cast<Device*>(*device);
			if (Succeeded(dev->Initialize(adapter)) && Succeeded(dev->Initialize()))
				return COM::kOK;
			(*device)->Release();
			*device = nullptr;
			return COM::kInitializationFailure;
		}
		return COM::kOutOfMemory;
	}
	return COM::kInvalidParameter;
}
