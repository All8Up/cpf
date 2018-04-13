//////////////////////////////////////////////////////////////////////////
#include "Vulkan/FrameBuffer.hpp"
#include "CPF/Platform/Graphics/FrameBufferDesc.hpp"
#include "Vulkan/Device.hpp"
#include "Vulkan/RenderPass.hpp"
#include "Vulkan/ImageView.hpp"

using namespace CPF;
using namespace Vulkan;

GOM::Result FrameBuffer::Initialize(Device* device, const Graphics::FrameBufferDesc* desc)
{
	VkFramebufferCreateInfo frameBufferCreateInfo;
	frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	frameBufferCreateInfo.pNext = nullptr;
	frameBufferCreateInfo.flags = 0;
	frameBufferCreateInfo.renderPass = static_cast<RenderPass*>(desc->mpRenderPass)->GetVkRenderPass();
	frameBufferCreateInfo.attachmentCount = uint32_t(desc->mAttachmentCount);
	frameBufferCreateInfo.width = uint32_t(desc->mWidth);
	frameBufferCreateInfo.height = uint32_t(desc->mHeight);
	frameBufferCreateInfo.layers = uint32_t(desc->mLayers);

	STD::Vector<VkImageView> attachments(desc->mAttachmentCount);
	for (int32_t i = 0; i < desc->mAttachmentCount; ++i)
	{
		attachments[i] = static_cast<ImageView*>(desc->mpAttachments[i].mpImageView)->GetVkImageView();
	}
	frameBufferCreateInfo.pAttachments = attachments.data();

	if (vkCreateFramebuffer(device->GetDevice(), &frameBufferCreateInfo, nullptr, &mFrameBuffer) == VK_SUCCESS)
		return GOM::kOK;

	return GOM::kError;
}
