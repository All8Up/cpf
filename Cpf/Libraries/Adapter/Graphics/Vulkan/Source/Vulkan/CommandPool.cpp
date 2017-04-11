//////////////////////////////////////////////////////////////////////////
#include "Adapter/Vulkan/CommandPool.hpp"
#include "Adapter/Vulkan/Device.hpp"

using namespace Cpf;
using namespace Adapters;
using namespace Vulkan;

CommandPool::CommandPool(Device* device)
	: mpDevice(device)
	, mpCommandPool(nullptr)
{
	VkCommandPoolCreateInfo info =
	{
		VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		nullptr,
		VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		device->GetGraphicsQueueIndex()
	};
	vkCreateCommandPool(device->GetDevice(), &info, nullptr, &mpCommandPool);
}

CommandPool::~CommandPool()
{
	vkDestroyCommandPool(mpDevice->GetDevice(), mpCommandPool, nullptr);
}

void CommandPool::Reset()
{
	vkResetCommandPool(mpDevice->GetDevice(), mpCommandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
}
