//////////////////////////////////////////////////////////////////////////
#include "Adapter/Vulkan/Device.hpp"
#include "Adapter/Vulkan/Adapter.hpp"
#include "Adapter/VUlkan/Instance.hpp"
#include "Adapter/Vulkan/CommandPool.hpp"
#include "Adapter/Vulkan/CommandBuffer.hpp"

using namespace Cpf;
using namespace Adapters;
using namespace Vulkan;

//////////////////////////////////////////////////////////////////////////
Device::Device(Graphics::Driver::iAdapter* adapter)
	: mpAdapter(adapter)
{
	Adapter* vulkanAdapter = static_cast<Adapter*>(adapter);
	Instance* vulkanInstance = static_cast<Instance*>(vulkanAdapter->GetInstance());

	uint32_t num_devices = 0;
	if ((vkEnumeratePhysicalDevices(vulkanInstance->GetInstance(), &num_devices, nullptr) != VK_SUCCESS) || (num_devices == 0))
	{
		CPF_ASSERT_ALWAYS;
		return;
	}

	mDevices.resize(num_devices);
	if (vkEnumeratePhysicalDevices(vulkanInstance->GetInstance(), &num_devices, &mDevices[0]) != VK_SUCCESS)
	{
		CPF_ASSERT_ALWAYS;
		return;
	}
}

Device::~Device()
{}


bool Device::CreateCommandPool(Graphics::Driver::iCommandPool** pool)
{
	CommandPool* result = new CommandPool(this);
	if (result)
	{
		*pool = result;
		return true;
	}
	return false;
}

bool Device::CreateCommandBuffer(Graphics::Driver::iCommandPool* pool, Graphics::Driver::iCommandBuffer** buffer)
{
	CommandBuffer* result = new CommandBuffer(this, pool);
	if (result)
	{
		*buffer = result;
		return true;
	}
	return false;
}
