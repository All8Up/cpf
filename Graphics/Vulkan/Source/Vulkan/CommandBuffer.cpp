//////////////////////////////////////////////////////////////////////////
#include "Adapters/Vulkan/CommandBuffer.hpp"
#include "Adapters/Vulkan/CommandPool.hpp"
#include "Adapters/Vulkan/Device.hpp"
#include "Adapters/Vulkan/SwapChain.hpp"

using namespace Cpf;
using namespace Adapters;
using namespace Vulkan;

CommandBuffer::CommandBuffer(Graphics::Driver::iDevice* device, Graphics::Driver::iCommandPool* pool)
	: mpDevice(static_cast<Device*>(device))
	, mpCommandPool(static_cast<CommandPool*>(pool))
	, mpCommandBuffer(nullptr)
{
	CommandPool* vulkanPool = static_cast<CommandPool*>(pool);
	VkCommandBufferAllocateInfo allocInfo =
	{
		VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		nullptr,
		vulkanPool->GetPool(),
		VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		1
	};
	vkAllocateCommandBuffers(mpDevice->GetDevice(), &allocInfo, &mpCommandBuffer);
}

CommandBuffer::~CommandBuffer()
{
	vkFreeCommandBuffers(mpDevice->GetDevice(), mpCommandPool->GetPool(), 1, &mpCommandBuffer);
}

void CommandBuffer::Begin()
{
	VkCommandBufferBeginInfo cmd_buffer_begin_info =
	{
		VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		nullptr,
		VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
		nullptr
	};
	vkBeginCommandBuffer(mpCommandBuffer, &cmd_buffer_begin_info);
}

void CommandBuffer::End()
{
	vkEndCommandBuffer(mpCommandBuffer);
}

void CommandBuffer::Reset(Graphics::Driver::iCommandPool* pool)
{
	(void)pool;
	vkResetCommandBuffer(mpCommandBuffer, 0);
}


void CommandBuffer::ToBePorted(Graphics::Driver::iDevice* device, Graphics::Driver::iSwapChain* swapChain)
{
	Device* vulkanDevice = static_cast<Device*>(device);
	SwapChain* vulkanSwapChain = static_cast<SwapChain*>(swapChain);

	//////////////////////////////////////////////////////////////////////////
	uint32_t image_index = vulkanSwapChain->GetNextBackBufferIndex();
	VkImage backBuffer = vulkanSwapChain->GetBackBuffer(image_index);
	VkImageView backBufferView = vulkanSwapChain->GetImageView(image_index);

	//////////////////////////////////////////////////////////////////////////
	VkAttachmentDescription descs[] =
	{
		{
			0,										// VkAttachmentDescriptionFlags    flags;
			vulkanSwapChain->GetFormat().format,	// VkFormat                        format;
			VK_SAMPLE_COUNT_1_BIT,					// VkSampleCountFlagBits           samples;
			VK_ATTACHMENT_LOAD_OP_CLEAR,			// VkAttachmentLoadOp              loadOp;
			VK_ATTACHMENT_STORE_OP_STORE,			// VkAttachmentStoreOp             storeOp;
			VK_ATTACHMENT_LOAD_OP_DONT_CARE,		// VkAttachmentLoadOp              stencilLoadOp;
			VK_ATTACHMENT_STORE_OP_DONT_CARE,		// VkAttachmentStoreOp             stencilStoreOp;
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,		// VkImageLayout                   initialLayout;
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR			// VkImageLayout                   finalLayout;
		}
	};
	VkAttachmentReference colorAttachments[] =
	{
		{
			0,										// uint32_t         attachment;
			VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL// VkImageLayout    layout;
		}
	};

	VkSubpassDescription subpassDescriptions[] =
	{
		{
			0,										// VkSubpassDescriptionFlags       flags;
			VK_PIPELINE_BIND_POINT_GRAPHICS,		// VkPipelineBindPoint             pipelineBindPoint;
			0,										// uint32_t                        inputAttachmentCount;
			nullptr,								// const VkAttachmentReference*    pInputAttachments;
			CPF_COUNTOF(colorAttachments),			// uint32_t                        colorAttachmentCount;
			colorAttachments,						// const VkAttachmentReference*    pColorAttachments;
			nullptr,								// const VkAttachmentReference*    pResolveAttachments;
			nullptr,								// const VkAttachmentReference*    pDepthStencilAttachment;
			0,										// uint32_t                        preserveAttachmentCount;
			nullptr									// const uint32_t*                 pPreserveAttachments;
		}
	};

	VkRenderPassCreateInfo renderPassInfo =
	{
		VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,	// VkStructureType                   sType;
		nullptr,									// const void*                       pNext;
		0,											// VkRenderPassCreateFlags           flags;
		1,											// uint32_t                          attachmentCount;
		descs,										// const VkAttachmentDescription*    pAttachments;
		1,											// uint32_t                          subpassCount;
		subpassDescriptions,						// const VkSubpassDescription*       pSubpasses;
		0,											// uint32_t                          dependencyCount;
		nullptr										// const VkSubpassDependency*        pDependencies;
	};

	VkRenderPass renderPass = VK_NULL_HANDLE;
	vkCreateRenderPass(vulkanDevice->GetDevice(), &renderPassInfo, nullptr, &renderPass);

	VkFramebufferCreateInfo framebufferInfo =
	{
		VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,	// VkStructureType             sType;
		nullptr,									// const void*                 pNext;
		0,											// VkFramebufferCreateFlags    flags;
		renderPass,									// VkRenderPass                renderPass;
		1,											// uint32_t                    attachmentCount;
		&backBufferView,							// const VkImageView*          pAttachments;
		vulkanSwapChain->GetWidth(),				// uint32_t                    width;
		vulkanSwapChain->GetHeight(),				// uint32_t                    height;
		1,											// uint32_t                    layers;
	};
	VkFramebuffer framebuffer = VK_NULL_HANDLE;
	vkCreateFramebuffer(vulkanDevice->GetDevice(), &framebufferInfo, nullptr, &framebuffer);

	//////////////////////////////////////////////////////////////////////////
	// Build the command buffer.
	static float c = 0.0f;
	c += 0.0001f;
	if (c > 1.0f)
		c = 0.0f;
	VkClearColorValue clear_color = {
		{ c, c, c, 1.0f }
	};

	//////////////////////////////////////////////////////////////////////////
	VkImageSubresourceRange image_subresource_range = {
		VK_IMAGE_ASPECT_COLOR_BIT,
		0,
		1,
		0,
		1
	};

	Begin();
	{
		VkImageMemoryBarrier barrier_from_present_to_clear =
		{
			VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
			nullptr,
			VK_ACCESS_MEMORY_READ_BIT,
			VK_ACCESS_TRANSFER_WRITE_BIT,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			VK_QUEUE_FAMILY_IGNORED,
			VK_QUEUE_FAMILY_IGNORED,
			backBuffer,
			image_subresource_range
		};
		vkCmdPipelineBarrier(mpCommandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier_from_present_to_clear);
		vkCmdClearColorImage(mpCommandBuffer, backBuffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clear_color, 1, &image_subresource_range);
	}

	{
		VkImageMemoryBarrier barrier_from_clear_to_present =
		{
			VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
			nullptr,
			VK_ACCESS_TRANSFER_WRITE_BIT,
			VK_ACCESS_MEMORY_READ_BIT,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
			VK_QUEUE_FAMILY_IGNORED,
			VK_QUEUE_FAMILY_IGNORED,
			backBuffer,
			image_subresource_range
		};
		vkCmdPipelineBarrier(mpCommandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier_from_clear_to_present);
	}

	//////////////////////////////////////////////////////////////////////////
	End();
	//////////////////////////////////////////////////////////////////////////
	{
		VkPipelineStageFlags wait_dst_stage_mask = VK_PIPELINE_STAGE_TRANSFER_BIT;
		VkSubmitInfo submit_info =
		{
			VK_STRUCTURE_TYPE_SUBMIT_INFO,
			nullptr,
			1,
			&vulkanSwapChain->GetImageAvailableSemaphore(),
			&wait_dst_stage_mask,
			1,
			&mpCommandBuffer,
			1,
			&vulkanSwapChain->GetRenderingFinishedSemaphore()
		};

		if (vkQueueSubmit(vulkanDevice->GetPresentQueue(), 1, &submit_info, VK_NULL_HANDLE) != VK_SUCCESS) {
			return;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	{
		VkPresentInfoKHR present_info =
		{
			VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
			nullptr,
			1,
			&vulkanSwapChain->GetRenderingFinishedSemaphore(),
			1,
			&vulkanSwapChain->GetSwapChain(),
			&image_index,
			nullptr
		};

		VkResult result = vkQueuePresentKHR(vulkanDevice->GetPresentQueue(), &present_info);
		switch (result)
		{
		case VK_SUCCESS:
			break;
		case VK_ERROR_OUT_OF_DATE_KHR:
		case VK_SUBOPTIMAL_KHR:
			vulkanSwapChain->OnWindowSizeChanged();
			return;
		default:
			return;
		}
	}
}
