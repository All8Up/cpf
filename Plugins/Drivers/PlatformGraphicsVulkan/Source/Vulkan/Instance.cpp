//////////////////////////////////////////////////////////////////////////
#include "Vulkan/Instance.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/Logging.hpp"
#include "Vulkan/Adapter.hpp"
#include "Vulkan/Device.hpp"

using namespace CPF;
using namespace Vulkan;
using namespace Graphics;

Instance::Instance(Plugin::iRegistry* registry, iUnknown*)
	: mpRegistry(registry)
	, mInstance(nullptr)
{
}

Instance::~Instance()
{}

GOM::Result CPF_STDCALL Instance::Initialize(const InstanceDesc* desc)
{
	// Handle debug layer setup.
	const auto instanceLayerProps = EnumerateInstanceLayers();
	STD::Vector<const char*> requiredLayers;

	if (desc->mEnableDebugLayer)
	{
		EnableLayer("VK_LAYER_LUNARG_standard_validation", instanceLayerProps, requiredLayers);
		EnableLayer("VK_LAYER_NV_nsight", instanceLayerProps, requiredLayers);
	}

	// Handle required extensions.
	const auto extensionProps = EnumerateInstanceExtensions();
	STD::Vector<const char*> requiredExtensions = {
		"VK_KHR_surface",
#ifdef _WIN32
		"VK_KHR_win32_surface"
#else
		"VK_KHR_xlib_surface"
#endif
	};
	if (desc->mEnableDebugLayer)
	{
		requiredExtensions.push_back("VK_EXT_debug_report");
	}

	// TODO: Add support for VR extensions?
	VkApplicationInfo appInfo = {};
	appInfo.pEngineName = "CPF";
	// TODO: Should include an application wide version perhaps?
	appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
	// TODO: Will need api versioning eventually.
	appInfo.apiVersion = 0;

	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &appInfo;
	instanceCreateInfo.enabledLayerCount = uint32_t(requiredLayers.size());
	instanceCreateInfo.ppEnabledLayerNames = requiredLayers.data();
	instanceCreateInfo.enabledExtensionCount = uint32_t(requiredExtensions.size());
	instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();

	if (vkCreateInstance(&instanceCreateInfo, nullptr, &mInstance) != VK_SUCCESS)
	{
		CPF_LOG(Vulkan, Info) << "Failed to create Vulkan instance";
		return GOM::kError;
	}

	// TODO: Install a debug callback.

	return GOM::kOK;
}

GOM::Result CPF_STDCALL Instance::EnumerateAdapters(int* count, iAdapter** adapters)
{
	// In Vulkan, we are enumerating the 'physical' devices.
	if (count)
	{
		uint32_t physicalCount = 0;
		vkEnumeratePhysicalDevices(mInstance, &physicalCount, nullptr);
		if (adapters == nullptr)
		{
			*count = int(physicalCount);
			return GOM::kOK;
		}
		
		// Create adapters representing each physical device.
		STD::Vector<VkPhysicalDevice> devices(physicalCount);
		vkEnumeratePhysicalDevices(mInstance, &physicalCount, devices.data());
		size_t index = 0;
		for (const auto& device : devices)
		{
			Adapter* adapter = new Adapter(mpRegistry, nullptr);
			adapters[index++] = adapter;

			adapter->Initialize(device);
		}
		return GOM::kOK;
	}

	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Instance::CreateDevice(iAdapter* adapter, iDevice** device)
{
	Device* vulkanDevice = new Device();
	if (vulkanDevice)
	{
		const auto result = vulkanDevice->Initialize(static_cast<Adapter*>(adapter));
		if (GOM::Succeeded(result))
		{
			*device = vulkanDevice;
			return result;
		}
		vulkanDevice->Release();
		return result;
	}
	return GOM::kOutOfMemory;
}

STD::Vector<VkLayerProperties> Instance::EnumerateInstanceLayers() const
{
	uint32_t count = 0;
	vkEnumerateInstanceLayerProperties(&count, nullptr);
	STD::Vector<VkLayerProperties> result(count);
	vkEnumerateInstanceLayerProperties(&count, result.data());

	for (const VkLayerProperties& layer : result)
	{
		CPF_LOG(Vulkan, Info)
			<< "Available Layer: "
			<< std::string(layer.layerName)
			<< " - Spec Version: " << std::to_string(layer.specVersion)
			<< " - Implementation Version: " << std::to_string(layer.implementationVersion);
	}

	return result;
}

void Instance::EnableLayer(const char* layer, const STD::Vector<VkLayerProperties>& available, STD::Vector<const char*>& required) const
{
	for (const auto& availLayer : available)
	{
		if (CSTD::StrCmp(availLayer.layerName, layer) == 0)
		{
			required.push_back(availLayer.layerName);
			return;
		}
	}
	CPF_LOG(Vulkan, Info) << "Layer not found: " << layer;
}

STD::Vector<VkExtensionProperties> Instance::EnumerateInstanceExtensions() const
{
	uint32_t count = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
	STD::Vector<VkExtensionProperties> result(count);
	vkEnumerateInstanceExtensionProperties(nullptr, &count, result.data());

	for (const VkExtensionProperties& extension : result)
	{
		CPF_LOG(Vulkan, Info) <<
			"Available Extension: " + std::string(extension.extensionName) + " - Spec Version: " + std::to_string(extension.specVersion);
	}

	return result;
}
