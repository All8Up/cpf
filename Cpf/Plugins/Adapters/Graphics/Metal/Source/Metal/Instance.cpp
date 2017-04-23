//////////////////////////////////////////////////////////////////////////
#include "Adapters/Metal/MetalUtils.hpp"
#include "Adapters/Metal/Instance.hpp"
#include "Adapters/Metal/Adapter.hpp"
#include "Adapters/Metal/Device.hpp"
#include "Adapters/Metal/SwapChain.hpp"
#include "IntrusivePtr.hpp"

using namespace Cpf;
using namespace Adapters;
using namespace Metal;

//////////////////////////////////////////////////////////////////////////
CPF_DEFINE_RTTI(Instance);

void* Instance::Create()
{
	return new Instance();
}

Instance::Instance()
{
}

Instance::~Instance()
{
}

bool Instance::EnumerateAdapters(int& count, Graphics::Driver::iAdapter** adapters)
{
	return false;
}


bool Instance::CreateDevice(Adapter::iAdapter* adapter, Graphics::Driver::iDevice** device)
{
	Graphics::Driver::iDevice* result = new Device(adapter);
	if (result)
	{
		*device = result;
		return true;
	}

	return false;
}

bool Instance::CreateSwapChain(Graphics::Driver::iDevice* device, iWindow* window, const Graphics::Driver::SwapChainDesc& desc, Graphics::Driver::iSwapChain** swapChain)
{
	Graphics::Driver::iSwapChain* result = new SwapChain(this, device, window, desc);
	if (result)
	{
		*swapChain = result;
		return true;
	}
	return false;
}
