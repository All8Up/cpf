//////////////////////////////////////////////////////////////////////////
#include "Vulkan/RenderPass.hpp"
#include "Vulkan/Device.hpp"
#include "CPF/Std/Vector.hpp"
#include "CPF/Platform/Graphics/RenderPassDesc.hpp"
#include "CPF/Platform/Graphics/AttachmentDesc.hpp"
#include "CPF/Platform/Graphics/SubPassDesc.hpp"
#include "Vulkan.hpp"

using namespace CPF;
using namespace Vulkan;

RenderPass::RenderPass()
{
}


GOM::Result RenderPass::Initialize(Device* device, const Graphics::RenderPassDesc* desc)
{
	if (desc)
	{
		VkRenderPassCreateInfo renderPassCreateInfo;
		renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassCreateInfo.pNext = nullptr;
		renderPassCreateInfo.flags = 0;
		renderPassCreateInfo.attachmentCount = uint32_t(desc->mAttachmentCount);
		renderPassCreateInfo.subpassCount = uint32_t(desc->mSubPassCount);
		renderPassCreateInfo.dependencyCount = uint32_t(desc->mDependencyCount);

		STD::Vector<VkAttachmentDescription> attachments(renderPassCreateInfo.attachmentCount);
		for (uint32_t i = 0; i < renderPassCreateInfo.attachmentCount; ++i)
		{
			const auto& src = desc->mpAttachments[i];
			auto& dst = attachments[i];
			dst.flags = 0;
			dst.format = ToVKFormat(src.mFormat);

			dst.samples = VkSampleCountFlagBits(src.mSamples.mCount >= 1 ? src.mSamples.mCount : 1);
			dst.loadOp = VkAttachmentLoadOp(src.mLoadOp);
			dst.storeOp = VkAttachmentStoreOp(src.mStoreOp);
			dst.stencilLoadOp = VkAttachmentLoadOp(src.mStencilLoadOp);
			dst.stencilStoreOp = VkAttachmentStoreOp(src.mStencilStoreOp);
			dst.initialLayout = ToVkImageLayout(src.mStartState);
			dst.finalLayout = ToVkImageLayout(src.mFinalState);
		}
		renderPassCreateInfo.pAttachments = attachments.data();

		STD::Vector<VkSubpassDescription> subPasses(renderPassCreateInfo.subpassCount);
		STD::Vector<STD::Vector<VkAttachmentReference>> inputAttachments(renderPassCreateInfo.subpassCount);
		STD::Vector<STD::Vector<VkAttachmentReference>> colorAttachments(renderPassCreateInfo.subpassCount);
		STD::Vector<STD::Vector<VkAttachmentReference>> resolveAttachments(renderPassCreateInfo.subpassCount);
		STD::Vector<VkAttachmentReference> depthStencilAttachments(renderPassCreateInfo.subpassCount);
		STD::Vector<STD::Vector<VkAttachmentReference>> preserveAttachments(renderPassCreateInfo.subpassCount);
		for (uint32_t i = 0; i < renderPassCreateInfo.subpassCount; ++i)
		{
			const auto& src = desc->mpSubPasses[i];
			auto& dst = subPasses[i];
			dst.flags = 0;
			dst.pipelineBindPoint = ToVkPipelineBindPoint(src.mBindPoint);
			dst.inputAttachmentCount = uint32_t(src.mInputCount);

			for (uint32_t j = 0; j < dst.inputAttachmentCount; ++j)
			{
				VkAttachmentReference ref;
				ref.attachment = uint32_t(src.mpInputAttachments[j].mIndex);
				ref.layout = ToVkImageLayout(src.mpInputAttachments[j].mState);
				inputAttachments[i].push_back(ref);
			}
			dst.pInputAttachments = inputAttachments[i].data();

			// TODO: Ignore the states for the moment.
			dst.colorAttachmentCount = uint32_t(src.mAttachmentCount);
			for (uint32_t j = 0; j < dst.colorAttachmentCount; ++j)
			{
				VkAttachmentReference ref;
				ref.attachment = uint32_t(src.mpColorAttachments[j].mIndex);
				ref.layout = ToVkImageLayout(src.mpColorAttachments[j].mState);
				colorAttachments[i].push_back(ref);

				if (src.mpResolveAttachments)
				{
					ref.attachment = uint32_t(src.mpResolveAttachments[j].mIndex);
					ref.layout = ToVkImageLayout(src.mpResolveAttachments[j].mState);
					resolveAttachments[i].push_back(ref);
				}
			}

			if (src.mpDepthStencilAttachment)
			{
				VkAttachmentReference ref;
				ref.attachment = uint32_t(src.mpDepthStencilAttachment->mIndex);
				ref.layout = ToVkImageLayout(src.mpDepthStencilAttachment->mState);
				depthStencilAttachments[i] = ref;
				dst.pDepthStencilAttachment = &depthStencilAttachments[i];
			}
			else
				dst.pResolveAttachments = nullptr;

			dst.pColorAttachments = colorAttachments[i].data();
			if (src.mpResolveAttachments)
				dst.pResolveAttachments = resolveAttachments[i].data();
			else
				dst.pResolveAttachments = nullptr;

			dst.preserveAttachmentCount = uint32_t(src.mPreserveCount);
			for (uint32_t j = 0; j < dst.preserveAttachmentCount; ++j)
			{
				VkAttachmentReference ref;
				ref.attachment = uint32_t(src.mpPreserveAttachments[j].mIndex);
				ref.layout = ToVkImageLayout(src.mpPreserveAttachments[j].mState);
				preserveAttachments[i].push_back(ref);
			}
		}
		renderPassCreateInfo.pSubpasses = subPasses.data();

		// TODO: Handle dependencies correctly.
		/*
		STD::Vector<VkSubpassDependency> dependencies(renderPassCreateInfo.dependencyCount);
		for (uint32_t i = 0; i < renderPassCreateInfo.dependencyCount; ++i)
		{

		}
		renderPassCreateInfo.pDependencies = dependencies.data();
		*/
		renderPassCreateInfo.dependencyCount = 0;
		renderPassCreateInfo.pDependencies = nullptr;

		if (vkCreateRenderPass(device->GetDevice(), &renderPassCreateInfo, nullptr, &mRenderPass) == VK_SUCCESS)
			return GOM::kOK;
		return GOM::kError;
	}
	return GOM::kInvalidParameter;
}
