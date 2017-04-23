//////////////////////////////////////////////////////////////////////////
#include "Adapter/Vulkan/Instance.hpp"
#include "Adapter/Vulkan/Adapter.hpp"
#include "Adapter/Vulkan/Device.hpp"
#include "Adapter/Vulkan/SwapChain.hpp"
using namespace Cpf;
using namespace Adapters;
using namespace Vulkan;

//////////////////////////////////////////////////////////////////////////
void* Instance::Create()
{
	return new Instance();
}

Instance::Instance()
{
	uint32_t extensions_count = 0;
	if ((vkEnumerateInstanceExtensionProperties(nullptr, &extensions_count, nullptr) != VK_SUCCESS) || (extensions_count == 0))
	{
		// Error
		CPF_ASSERT_ALWAYS;
	}

	std::vector<VkExtensionProperties> available_extensions(extensions_count);
	if (vkEnumerateInstanceExtensionProperties(nullptr, &extensions_count, &available_extensions[0]) != VK_SUCCESS)
	{
		// Error
		CPF_ASSERT_ALWAYS;
	}

	std::vector<const char*> extensions = {
		VK_KHR_SURFACE_EXTENSION_NAME,
#if CPF_TARGET_WINDOWS
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#elif defined(VK_USE_PLATFORM_XCB_KHR)
		VK_KHR_XCB_SURFACE_EXTENSION_NAME
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
		VK_KHR_XLIB_SURFACE_EXTENSION_NAME
#endif
	};

	for (size_t i = 0; i < extensions.size(); ++i)
	{
		if (!CheckExtensionAvailability(extensions[i], available_extensions))
		{
			// Error
			CPF_ASSERT_ALWAYS;
		}
	}

	VkApplicationInfo application_info = {
		VK_STRUCTURE_TYPE_APPLICATION_INFO,
		nullptr,
		"Cpf Vulkan Application",
		VK_MAKE_VERSION(1, 0, 0),
		"Vulkan Adapter",
		VK_MAKE_VERSION(1, 0, 0),
		VK_MAKE_VERSION(1, 0, 0)
	};

	VkInstanceCreateInfo instance_create_info = {
		VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		nullptr,
		0,
		&application_info,
		0,
		nullptr,
		static_cast<uint32_t>(extensions.size()),
		&extensions[0]
	};

	if (vkCreateInstance(&instance_create_info, nullptr, &mInstance) != VK_SUCCESS)
	{
		// Error
		CPF_ASSERT_ALWAYS;
	}
}

Instance::~Instance()
{
	vkDestroyInstance(mInstance, nullptr);
}

bool Instance::EnumerateAdapters(int& count, Graphics::Driver::iAdapter** adapters)
{
	if (adapters)
	{
		uint32_t num_devices(count);
		std::vector<VkPhysicalDevice> physical_devices(num_devices);
		if (vkEnumeratePhysicalDevices(mInstance, &num_devices, &physical_devices[0]) != VK_SUCCESS)
		{
			return false;
		}
		for (int i=0; i<count; ++i)
		{
			adapters[i] = new Adapter(this, physical_devices[i]);
		}
		return true;
	}
	else
	{
		uint32_t num_devices = 0;
		if ((vkEnumeratePhysicalDevices(mInstance, &num_devices, nullptr) != VK_SUCCESS) || (num_devices == 0))
		{
			return false;
		}
		count = int(num_devices);
		return true;
	}
}


bool Instance::CreateDevice(Adapter::iAdapter* adapter, Graphics::Driver::iDevice** device)
{
	Device* result = new Device(adapter);
	if (result)
	{
		*device = result;
		return true;
	}
	return false;
}

bool Instance::CreateSwapChain(Graphics::Driver::iDevice* device, iWindow* window, const Graphics::Driver::SwapChainDesc& desc, Graphics::Driver::iSwapChain** swapChain)
{
	Device* vulkanDevice = static_cast<Device*>(device);
	Adapter* vulkanAdapter = static_cast<Adapter*>(vulkanDevice->GetAdapter());
	Instance* vulkanInstance = static_cast<Instance*>(vulkanAdapter->GetInstance());
	SwapChain* result = new SwapChain(vulkanInstance, device, window, desc);
	if (result)
	{
		*swapChain = result;
		return true;
	}
	return false;
}
