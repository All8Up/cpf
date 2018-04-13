//////////////////////////////////////////////////////////////////////////
#include "Vulkan/CommandBuffer.hpp"
#include "Vulkan/Device.hpp"
#include "Vulkan/CommandPool.hpp"
#include "Vulkan/RenderPass.hpp"
#include "Vulkan/FrameBuffer.hpp"
#include "CPF/Platform/Graphics/RenderPassBeginDesc.hpp"

using namespace CPF;
using namespace Vulkan;

//////////////////////////////////////////////////////////////////////////
GOM::Result CommandBuffer::Initialize(Device* device, CommandPool* pool, Graphics::CommandBufferType type)
{
	mpDevice = device;

	VkCommandBufferAllocateInfo commandBufferAllocInfo;
	commandBufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferAllocInfo.pNext = nullptr;
	commandBufferAllocInfo.commandPool = pool->GetVkCommandPool();
	commandBufferAllocInfo.commandBufferCount = 1;
	commandBufferAllocInfo.level = type == Graphics::CommandBufferType::ePrimary ? VK_COMMAND_BUFFER_LEVEL_PRIMARY : VK_COMMAND_BUFFER_LEVEL_SECONDARY;
	if (vkAllocateCommandBuffers(device->GetDevice(), &commandBufferAllocInfo, &mCommandBuffer) == VK_SUCCESS)
		return GOM::kOK;
	return GOM::kError;
}


//////////////////////////////////////////////////////////////////////////
void CPF_STDCALL CommandBuffer::Begin(iCommandBuffer* primary)
{
	VkCommandBufferBeginInfo commandBufferBeginInfo;
	commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	commandBufferBeginInfo.pNext = nullptr;
	commandBufferBeginInfo.flags = 0;
	commandBufferBeginInfo.pInheritanceInfo = nullptr;
	vkBeginCommandBuffer(mCommandBuffer, &commandBufferBeginInfo);
}

void CPF_STDCALL CommandBuffer::End()
{
	vkEndCommandBuffer(mCommandBuffer);
}

void CPF_STDCALL CommandBuffer::Reset(Graphics::iCommandPool* pool)
{
	vkResetCommandBuffer(mCommandBuffer, 0);
}

void CPF_STDCALL CommandBuffer::UpdateSubResource(Graphics::iResource* src, Graphics::iResource* dst, const Graphics::ResourceData* data)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::CopyResource(Graphics::iResource* src, Graphics::iResource* dst)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::ResourceBarrier(Graphics::iResource* resource, Graphics::ResourceState startStart, Graphics::ResourceState endState)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::ImageTransition(Graphics::iImage* image, Graphics::ResourceState startState, Graphics::ResourceState endState, Graphics::SubResource subResources)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::SetResourceBinding(Graphics::iResourceBinding* binding)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::SetPipeline(Graphics::iPipeline* pipeline)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::SetViewports(int32_t count, const Graphics::Viewport* rects)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::SetScissorRects(int32_t count, const Math::Rectanglei* rects)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::SetTopology(Graphics::PrimitiveTopology topology)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::SetVertexBuffers(int32_t startSlot, int32_t viewCount, Graphics::iVertexBuffer** outVB)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::SetIndexBuffer(Graphics::iIndexBuffer* ib)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::SetConstantBuffer(int32_t index, Graphics::iConstantBuffer* cb)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::SetConstants(int32_t index, int32_t count, const void* data, int32_t offset)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::SetSampler(int32_t index, Graphics::iSampler* sampler)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::SetImage(int32_t index, Graphics::iImage* image)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::DrawInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t startInstance)
{
	CPF_ASSERT_ALWAYS;
}

void CPF_STDCALL CommandBuffer::DrawIndexedInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t offset, int32_t startInstance)
{
	CPF_ASSERT_ALWAYS;
}

GOM::Result CPF_STDCALL CommandBuffer::BeginRenderPass(Graphics::RenderPassBeginDesc* rpbd)
{
	VkRenderPassBeginInfo beginInfo;
	beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	beginInfo.pNext = nullptr;
	beginInfo.renderPass = static_cast<RenderPass*>(rpbd->mpRenderPass)->GetVkRenderPass();
	beginInfo.framebuffer = static_cast<FrameBuffer*>(rpbd->mpFrameBuffer)->GetVkFrameBuffer();
	beginInfo.renderArea.offset = { int32_t(rpbd->mClipRect.Left()), int32_t(rpbd->mClipRect.Top()) };
	beginInfo.renderArea.extent = { uint32_t(rpbd->mClipRect.Right() - rpbd->mClipRect.Left()), uint32_t(rpbd->mClipRect.Bottom() - rpbd->mClipRect.Top()) };

	STD::Vector<VkClearValue> clearValues(rpbd->mClearValueCount);
	for (int i = 0; i < rpbd->mClearValueCount; ++i)
	{
		clearValues[i].color = {
			rpbd->mpClearValues[i].mData.mColor.mColor[0],
			rpbd->mpClearValues[i].mData.mColor.mColor[1],
			rpbd->mpClearValues[i].mData.mColor.mColor[2],
			rpbd->mpClearValues[i].mData.mColor.mColor[3]
		};
	}
	beginInfo.clearValueCount = rpbd->mClearValueCount;
	beginInfo.pClearValues = clearValues.data();

	vkCmdBeginRenderPass(mCommandBuffer, &beginInfo, VK_SUBPASS_CONTENTS_INLINE);
	return GOM::kOK;
}

GOM::Result CPF_STDCALL CommandBuffer::NextSubPass()
{
	CPF_ASSERT_ALWAYS;
	return GOM::kNotImplemented;
}

GOM::Result CPF_STDCALL CommandBuffer::EndRenderPass()
{
	vkCmdEndRenderPass(mCommandBuffer);
	return GOM::kOK;
}

GOM::Result CPF_STDCALL CommandBuffer::Insert(int32_t count, iCommandBuffer* const * icb)
{
	CPF_ASSERT_ALWAYS;
	return GOM::kNotImplemented;
}
