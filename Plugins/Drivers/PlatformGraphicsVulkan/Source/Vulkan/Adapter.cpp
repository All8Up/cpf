//////////////////////////////////////////////////////////////////////////
#include "Vulkan/Adapter.hpp"
#include "CPF/Std/Vector.hpp"

using namespace CPF;
using namespace Vulkan;

Adapter::Adapter(Plugin::iRegistry* registry, iUnknown*)
	: mpRegistry(registry)
{
}

Adapter::~Adapter()
{
}

GOM::Result Adapter::Initialize(VkPhysicalDevice device)
{
	mPhysicalDevice = device;

	// Dig out the device information.
	vkGetPhysicalDeviceProperties(mPhysicalDevice, &mPhysicalDeviceProperties);

	vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &mQueueFamilyCount, nullptr);
	STD::Vector<VkQueueFamilyProperties> queueFamilyProperties(mQueueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &mQueueFamilyCount, queueFamilyProperties.data());

	for (size_t i = 0; i < queueFamilyProperties.size(); i++)
	{
		const VkQueueFlags flags = queueFamilyProperties[i].queueFlags;
		if ((flags & VK_QUEUE_GRAPHICS_BIT) != 0 && mGraphicsQueueIndex == kInvalidQueueIndex)
		{
			mGraphicsQueueIndex = uint32_t(i);
		}
		else if ((flags & VK_QUEUE_COMPUTE_BIT) != 0 && mComputeQueueIndex == kInvalidQueueIndex)
		{
			mComputeQueueIndex = uint32_t(i);
		}
		else if ((flags & VK_QUEUE_TRANSFER_BIT) != 0 && mTransferQueueIndex == kInvalidQueueIndex)
		{
			mTransferQueueIndex = uint32_t(i);
		}
		mQueuePriorities.push_back(1.0f);
	}

	return (
		(mGraphicsQueueIndex != kInvalidQueueIndex) &&
		(mComputeQueueIndex != kInvalidQueueIndex) &&
		(mTransferQueueIndex != kInvalidQueueIndex)) ?
		GOM::kOK : GOM::kInvalid;
}

const char* CPF_STDCALL Adapter::GetDescription() const
{
	CPF_ASSERT_ALWAYS;
	return nullptr;
}

size_t CPF_STDCALL Adapter::GetVideoMemory() const
{
	VkPhysicalDeviceMemoryProperties properties;
	vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &properties);

	// Get local memory size from device
	uint64_t deviceMemory = 0;
	for (uint32_t i = 0; i < properties.memoryHeapCount; i++)
	{
		if ((properties.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) > 0)
		{
			deviceMemory = properties.memoryHeaps[i].size;
			break;
		}
	}

	return deviceMemory;
}

size_t CPF_STDCALL Adapter::GetSystemMemory() const
{
	CPF_ASSERT_ALWAYS;
	return 0;
}

size_t CPF_STDCALL Adapter::GetSharedMemory() const
{
	CPF_ASSERT_ALWAYS;
	return 0;
}

bool CPF_STDCALL Adapter::IsSoftware() const
{
	return false;
}

bool CPF_STDCALL Adapter::IsRemote() const
{
	return false;
}

GOM::Result CPF_STDCALL Adapter::EnumerateOutputs(int32_t* count, Graphics::iOutput**) const
{
	CPF_ASSERT_ALWAYS;
	(void)count;
	return GOM::kNotImplemented;
}
