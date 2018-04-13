//////////////////////////////////////////////////////////////////////////
#include "Vulkan/Fence.hpp"
#include "Vulkan/Device.hpp"

using namespace CPF;
using namespace Vulkan;

GOM::Result Fence::Initialize(Device* device, bool signaled)
{
	mpDevice = device;
	VkFenceCreateInfo fenceCreateInfo;
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCreateInfo.pNext = nullptr;
	fenceCreateInfo.flags = signaled ? VK_FENCE_CREATE_SIGNALED_BIT : false;
	if (vkCreateFence(device->GetDevice(), &fenceCreateInfo, nullptr, &mFence) == VK_SUCCESS)
		return GOM::kOK;
	return GOM::kError;
}

Graphics::FenceStatus CPF_STDCALL Fence::GetStatus() const
{
	const auto result = vkGetFenceStatus(mpDevice->GetDevice(), mFence);
	switch (result)
	{
	case VkResult::VK_NOT_READY: return Graphics::FenceStatus::eNotReady;
	case VkResult::VK_SUCCESS: return Graphics::FenceStatus::eReady;
	default: return Graphics::FenceStatus::eInvalid;
	}
}

void CPF_STDCALL Fence::Reset()
{
	vkResetFences(mpDevice->GetDevice(), 1, &mFence);
}

Graphics::FenceStatus CPF_STDCALL Fence::Wait() const
{
	if (vkWaitForFences(mpDevice->GetDevice(), 1, &mFence, true, std::numeric_limits<uint64_t>::max()) == VK_SUCCESS)
		return Graphics::FenceStatus::eReady;
	return Graphics::FenceStatus::eNotReady;
}
