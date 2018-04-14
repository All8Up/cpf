//////////////////////////////////////////////////////////////////////////
#include "Vulkan/CommandPool.hpp"
#include "Vulkan/Device.hpp"

using namespace CPF;
using namespace Vulkan;

GOM::Result CommandPool::Initialize(Device* device)
{
	mpDevice = device;

	VkCommandPoolCreateInfo commandPoolCreateInfo;
	commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolCreateInfo.pNext = nullptr;
	commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	commandPoolCreateInfo.queueFamilyIndex = 0;

	if (vkCreateCommandPool(device->GetDevice(), &commandPoolCreateInfo, nullptr, &mCommandPool) == VK_SUCCESS)
		return GOM::kOK;
	return GOM::kError;
}

void CPF_STDCALL CommandPool::Reset()
{
	vkResetCommandPool(mpDevice->GetDevice(), mCommandPool, 0);
}
