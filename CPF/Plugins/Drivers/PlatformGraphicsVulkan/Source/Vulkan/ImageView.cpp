//////////////////////////////////////////////////////////////////////////
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/Device.hpp"

using namespace CPF;
using namespace Vulkan;

GOM::Result ImageView::Initialize(Device* device, Graphics::iImage* image, VkFormat format, bool depth)
{
	if (image)
	{
		Image* vulkanImage = static_cast<Image*>(image);
		VkImage vkImage = vulkanImage->GetVkImage();

		VkImageViewCreateInfo imageViewCreateInfo;
		imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageViewCreateInfo.pNext = nullptr;
		imageViewCreateInfo.flags = 0;
		imageViewCreateInfo.image = vkImage;
		imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		imageViewCreateInfo.format = format;
		imageViewCreateInfo.components = { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY };

		// TODO: This is likely incorrect, just a placeholder for now.
		imageViewCreateInfo.subresourceRange.aspectMask = depth ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
		imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
		imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
		imageViewCreateInfo.subresourceRange.layerCount = 1;
		imageViewCreateInfo.subresourceRange.levelCount = 1;

		if (vkCreateImageView(device->GetDevice(), &imageViewCreateInfo, nullptr, &mImageView) == VK_SUCCESS)
			return GOM::kOK;
		return GOM::kError;
	}
	return GOM::kInvalidParameter;
}
