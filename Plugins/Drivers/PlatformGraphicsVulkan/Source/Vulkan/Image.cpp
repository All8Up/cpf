//////////////////////////////////////////////////////////////////////////
#include "Vulkan/Image.hpp"
#include "Vulkan/Device.hpp"

using namespace CPF;
using namespace Vulkan;

bool CPF_STDCALL Image::Map(void** buffer, const Graphics::Range* range)
{
	CPF_ASSERT_ALWAYS;
	(void)buffer; (void)range;
	return false;
}

void CPF_STDCALL Image::Unmap(const Graphics::Range* range)
{
	CPF_ASSERT_ALWAYS;
	(void)range;
}

GOM::Result CPF_STDCALL Image::GetDesc(Graphics::ImageDesc* desc) const
{
	if (desc)
	{
		*desc = mDesc;
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result Image::Initialize(VkImage image)
{
	mImage = image;
	return GOM::kOK;
}

GOM::Result Image::Create2D(Device* device, Graphics::HeapType heap, const Graphics::ClearValue* clearValue, const Graphics::ImageDesc* desc)
{
	(void)heap;
	if (device && clearValue && desc)
	{
		mDesc = *desc;

		VkImageCreateInfo imageCreateInfo;
		imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageCreateInfo.pNext = nullptr;
		imageCreateInfo.flags = 0;
		imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
		imageCreateInfo.format = ToVKFormat(desc->mFormat);
		imageCreateInfo.extent = { uint32_t(desc->mWidth), uint32_t(desc->mHeight), uint32_t(desc->mDepth) };
		imageCreateInfo.mipLevels = desc->mMipLevels;
		imageCreateInfo.arrayLayers = 1;
		imageCreateInfo.samples = VkSampleCountFlagBits(desc->mSamples.mCount);
		imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
		imageCreateInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
			((desc->mFlags & Graphics::ImageFlags::eAllowDepthStencil) == Graphics::ImageFlags::eAllowDepthStencil ?
				VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT : 0);
		imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		imageCreateInfo.queueFamilyIndexCount = 0;
		imageCreateInfo.pQueueFamilyIndices = nullptr;
		imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

		if (vkCreateImage(device->GetDevice(), &imageCreateInfo, nullptr, &mImage) != VK_SUCCESS)
			return GOM::kError;

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(device->GetDevice(), mImage, &memRequirements);

		VkMemoryAllocateInfo allocInfo;
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.pNext = nullptr;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(device, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		if (vkAllocateMemory(device->GetDevice(), &allocInfo, nullptr, &mDeviceMemory) != VK_SUCCESS)
			return GOM::kError;

		vkBindImageMemory(device->GetDevice(), mImage, mDeviceMemory, 0);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

uint32_t Image::FindMemoryType(Device* device, uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(device->GetPhysicalDevice(), &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if ((typeFilter & (1 << i)) &&
			(memProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}
	return 0;
}
