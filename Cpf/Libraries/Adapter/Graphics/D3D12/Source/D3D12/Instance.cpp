//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/D3D12Utils.hpp"
#include "Adapter/D3D12/Instance.hpp"
#include "Adapter/D3D12/Adapter.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Adapter/D3D12/SwapChain.hpp"
#include "IntrusivePtr.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

//////////////////////////////////////////////////////////////////////////
void* Instance::Create()
{
	return new Instance();
}

Instance::Instance()
{
	UINT flags = 0;
#if _DEBUG
	flags = DXGI_CREATE_FACTORY_DEBUG;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(mpDebugController.AsTypePP()))))
	{
		mpDebugController->EnableDebugLayer();
	}
#endif
	CreateDXGIFactory2(flags, IID_PPV_ARGS(mpDXGIFactory2.AsTypePP()));

	CPF_LOG(D3D12, Info) << "Created instance: " << intptr_t(this) << " - " << intptr_t(mpDXGIFactory2.Ptr());
}

Instance::~Instance()
{
	CPF_LOG(D3D12, Info) << "Destroyed instance: " << intptr_t(this) << " - " << intptr_t(mpDXGIFactory2.Ptr());
}

bool Instance::EnumerateAdapters(int& count, Graphics::iAdapter** adapters)
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
							Graphics::iAdapter* d3dAdapter = new Adapter(adapter2);
							adapters[i] = d3dAdapter;
						}
						else
							return false;
					}
				}
				else
					return false;
			}
			return true;
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
		return true;
	}

	return false;
}


bool Instance::CreateDevice(Adapter::iAdapter* adapter, Graphics::iDevice** device)
{
	Graphics::iDevice* result = new Device(adapter);
	if (result && result->Initialize())
	{
		*device = result;
		return true;
	}

	return false;
}
