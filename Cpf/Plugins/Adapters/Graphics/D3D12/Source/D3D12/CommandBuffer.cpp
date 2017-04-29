//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/CommandBuffer.hpp"
#include "Adapter/D3D12/CommandPool.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Adapter/D3D12/SwapChain.hpp"
#include "Adapter/D3D12/Image.hpp"
#include "Adapter/D3D12/ImageView.hpp"
#include "Adapter/D3D12/D3D12Utils.hpp"
#include "Adapter/D3D12/Resource.hpp"
#include "Adapter/D3D12/ResourceBinding.hpp"
#include "Adapter/D3D12/Pipeline.hpp"
#include "Adapter/D3D12/IndexBuffer.hpp"
#include "Adapter/D3D12/VertexBuffer.hpp"
#include "Adapter/D3D12/ConstantBuffer.hpp"
#include "Adapter/D3D12/RenderPass.hpp"
#include "Adapter/D3D12/FrameBuffer.hpp"
#include "Graphics/DepthStencilClearFlag.hpp"
#include "Graphics/RenderPassBeginDesc.hpp"
#include "Graphics/ResourceData.hpp"
#include "Graphics/iRenderPass.hpp"
#include "Graphics/iFrameBuffer.hpp"
#include "Graphics/ResourceState.hpp"
#include "Graphics/SubResource.hpp"
#include "Logging/Logging.hpp"
#include "Adapter/D3D12/Sampler.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

//////////////////////////////////////////////////////////////////////////

CommandBuffer::CommandBuffer(COM::iUnknown*)
	: mpDevice(nullptr)
	, mpAllocator(nullptr)
	, mCurrent(-1)
	, mType(Graphics::CommandBufferType::kPrimary)
	, mRenderPass{0}
{
}

CommandBuffer::~CommandBuffer()
{
	for (auto& clv : mCommandLists)
		clv[0]->Release();
	CPF_LOG(D3D12, Info) << "Destroyed command buffer: " << intptr_t(this);
}

COM::Result CPF_STDCALL CommandBuffer::Initialize(Graphics::iDevice* device, Graphics::CommandBufferType type, Graphics::iCommandPool* pool)
{
	if (device && pool)
	{
		mpDevice = static_cast<Device*>(device);
		mpAllocator = static_cast<CommandPool*>(pool)->GetCommandAllocator();
		mType = type;

		COM::Result result = _AddCommandList();
		if (Succeeded(result))
		{
			CPF_LOG(D3D12, Info) << "Created command buffer: " << intptr_t(this);
			return COM::kOK;
		}
		return result;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL CommandBuffer::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iCommandBuffer::kIID.GetID():
			*outIface = static_cast<iCommandBuffer*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

void CommandBuffer::Begin()
{}

void CommandBuffer::End()
{
	_Current()->Close();
}

void CommandBuffer::Reset(Graphics::iCommandPool* pool)
{
	// TODO: Consider if the pipeline can/should be passed in.  Probably would not work in Vulkan and/or Metal though.
	CommandPool* d3dPool = static_cast<CommandPool*>(pool);
	_Current()->Reset(d3dPool->GetCommandAllocator(), nullptr);
	mHeaps.clear();

	// Remove inserted references to other command lists but do not free the owned items.
	for (CommandListVector& clv : mCommandLists)
	{
		clv.resize(1);
	}
}

void CommandBuffer::UpdateSubResource(Graphics::iResource* src, Graphics::iResource* dst, const Graphics::ResourceData* data)
{
	D3D12_SUBRESOURCE_DATA resData = { data->mpData, LONG_PTR(data->mPitch), LONG_PTR(data->mSlicePitch) };
	UpdateSubresources<1>(
		_Current(),
		static_cast<Resource*>(dst)->GetResource(),
		static_cast<Resource*>(src)->GetResource(),
		0, 0, 1, &resData);
}

void CommandBuffer::ResourceBarrier(Graphics::iResource* resource, Graphics::ResourceState startState, Graphics::ResourceState endState)
{
	Resource* res = static_cast<Resource*>(resource);
	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(res->GetResource(), D3D12_RESOURCE_STATES(startState), D3D12_RESOURCE_STATES(endState));
	_Current()->ResourceBarrier(1, &barrier);
}

void CommandBuffer::ImageTransition(
	Graphics::iImage* image,
	Graphics::ResourceState startState,
	Graphics::ResourceState endState,
	Graphics::SubResource subResources)
{
	D3D12_RESOURCE_BARRIER barrier;
	ZeroMemory(&barrier, sizeof(barrier));

	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = static_cast<Image*>(image)->GetResource();
	barrier.Transition.StateBefore = Convert(startState);
	barrier.Transition.StateAfter = Convert(endState);
	barrier.Transition.Subresource = Convert(subResources);
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	_Current()->ResourceBarrier(1, &barrier);
}

void CommandBuffer::SetResourceBinding(Graphics::iResourceBinding* binding)
{
	ResourceBinding* resBinding = static_cast<ResourceBinding*>(binding);
	_Current()->SetGraphicsRootSignature(resBinding->GetSignature());
}

void CommandBuffer::SetPipeline(Graphics::iPipeline* pipeline)
{
	Pipeline* pipe = static_cast<Pipeline*>(pipeline);
	_Current()->SetPipelineState(pipe->GetPipelineState());
}

void CommandBuffer::SetViewports(int32_t count, const Graphics::Viewport* rects)
{
	_Current()->RSSetViewports(count, reinterpret_cast<const D3D12_VIEWPORT*>(rects));
}

void CommandBuffer::SetScissorRects(int32_t count, const Math::Rectanglei* rects)
{
	D3D12_RECT r[8];
	for (int i = 0; i < count; ++i)
	{
		r[i].left = rects[i].Left();
		r[i].right = rects[i].Right();
		r[i].top = rects[i].Top();
		r[i].bottom = rects[i].Bottom();
	}
	_Current()->RSSetScissorRects(UINT(count), r);
}

void CommandBuffer::SetTopology(Graphics::PrimitiveTopology topology)
{
	_Current()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY(topology));
}

void CommandBuffer::SetVertexBuffers(int32_t startSlot, int32_t viewCount, Graphics::iVertexBuffer** inViews)
{
	D3D12_VERTEX_BUFFER_VIEW views[16];
	for (int i = 0; i < viewCount; ++i)
		views[i] = *static_cast<VertexBuffer*>(inViews[i])->GetView();
	_Current()->IASetVertexBuffers(UINT(startSlot), UINT(viewCount), views);
}

void CommandBuffer::SetIndexBuffer(Graphics::iIndexBuffer* ib)
{
	_Current()->IASetIndexBuffer(static_cast<IndexBuffer*>(ib)->GetView());
}

void CommandBuffer::SetConstantBuffer(int32_t index, Graphics::iConstantBuffer* cb)
{
	ConstantBuffer* cbuffer = static_cast<ConstantBuffer*>(cb);
	_Current()->SetGraphicsRootConstantBufferView(UINT(index), cbuffer->GetGPUAddress());
}

void CommandBuffer::SetConstants(int32_t index, int32_t count, const void* data, int32_t offset)
{
	_Current()->SetGraphicsRoot32BitConstants(UINT(index), UINT(count), data, UINT(offset));
}

void CommandBuffer::SetSampler(int32_t index, Graphics::iSampler* sampler)
{
	Sampler* d3d12Sampler = static_cast<Sampler*>(sampler);
	if (mHeaps.find(d3d12Sampler->GetDescriptor().GetManager()->GetHeap()) == mHeaps.end())
		mHeaps.insert(d3d12Sampler->GetDescriptor().GetManager()->GetHeap());
	ID3D12DescriptorHeap* heaps[8];
	int i = 0;
	for (auto heap : mHeaps)
		heaps[i++] = heap;
	_Current()->SetDescriptorHeaps(i, heaps);
	_Current()->SetGraphicsRootDescriptorTable(index, d3d12Sampler->GetDescriptor());
}

void CommandBuffer::SetImage(int32_t index, Graphics::iImage* image)
{
	Image* d3d12Image = static_cast<Image*>(image);
	if (mHeaps.find(d3d12Image->GetDescriptor().GetManager()->GetHeap()) == mHeaps.end())
		mHeaps.insert(d3d12Image->GetDescriptor().GetManager()->GetHeap());
	ID3D12DescriptorHeap* heaps[8];
	int i = 0;
	for (auto heap : mHeaps)
		heaps[i++] = heap;
	_Current()->SetDescriptorHeaps(i, heaps);
	_Current()->SetGraphicsRootDescriptorTable(index, d3d12Image->GetDescriptor());
}

void CommandBuffer::DrawInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t startInstance)
{
	_Current()->DrawInstanced(UINT(vertsPerInstance), UINT(instances), UINT(startVert), UINT(startInstance));
}

void CommandBuffer::DrawIndexedInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t offset, int32_t startInstance)
{
	_Current()->DrawIndexedInstanced(UINT(vertsPerInstance), UINT(instances), UINT(startVert), UINT(offset), UINT(startInstance));
}

void CommandBuffer::SetRenderTargets(int32_t imageCount, Graphics::iImageView** images, Graphics::iImageView* depthView)
{
	CPF_ASSERT(imageCount <= 32);
	D3D12_CPU_DESCRIPTOR_HANDLE imageDescs[32];
	for (auto i = 0; i < imageCount; ++i)
		imageDescs[i] = static_cast<ImageView*>(images[i])->GetDescriptor();

	if (depthView)
	{
		// TODO: Have the descriptor return a pointer to avoid this copy.
		D3D12_CPU_DESCRIPTOR_HANDLE depthViewHandle = static_cast<ImageView*>(depthView)->GetDescriptor();
		_Current()->OMSetRenderTargets(imageCount, imageDescs, FALSE, &depthViewHandle);
	}
	else
		_Current()->OMSetRenderTargets(imageCount, imageDescs, FALSE, nullptr);
}

void CommandBuffer::ClearRenderTargetView(Graphics::iImageView* view, Math::Vector4fv& color, int32_t count, const Math::Rectanglei* rects)
{
	// TODO: Clean up the casts and validate that the rects are the same style.
	_Current()->ClearRenderTargetView(
		static_cast<ImageView*>(view)->GetDescriptor(),
		reinterpret_cast<float*>(&color),
		count,
		reinterpret_cast<const D3D12_RECT*>(rects));
}

void CommandBuffer::ClearDepthStencilView(Graphics::iImageView* view, Graphics::DepthStencilClearFlag flags, float depth, uint8_t stencil, int32_t count, const Math::Rectanglei* rects)
{
	D3D12_CLEAR_FLAGS d3dFlags = D3D12_CLEAR_FLAGS(0);
	d3dFlags |= ((flags & Graphics::DepthStencilClearFlag::eDepth) == Graphics::DepthStencilClearFlag(0) ? D3D12_CLEAR_FLAGS(0) : D3D12_CLEAR_FLAG_DEPTH);
	d3dFlags |= ((flags & Graphics::DepthStencilClearFlag::eStencil) == Graphics::DepthStencilClearFlag(0) ? D3D12_CLEAR_FLAGS(0) : D3D12_CLEAR_FLAG_STENCIL);
	_Current()->ClearDepthStencilView(
		static_cast<ImageView*>(view)->GetDescriptor(),
		d3dFlags,
		depth,
		stencil,
		count,
		reinterpret_cast<const D3D12_RECT*>(rects)
	);
}

COM::Result CPF_STDCALL CommandBuffer::BeginRenderPass(Graphics::RenderPassBeginDesc* desc)
{
	// This abstraction over render passes is preferred to the set render target approach of D3D12
	// since Vulkan is better designed for the needs of the hand held devices the system should
	// eventually run on.  Additionally, with enough work, this solution let's some automated optimization
	// of resource barriers take place.  Finally, the same basic solution is used in Metal for iOS.

	// TODO: The primary difficulty for this in D3D12 is that under Vulkan the render pass and all
	// TODO: rendering commands are expected in a single primary command buffer.  So the method it
	// TODO: would work in Vulkan is "begin -> embed secondary lists -> next subpass -> more secondary
	// TODO: -> end passes" submit single primary list.  D3D12 does not have a separation between
	// TODO: primary and secondary, the closest thing is direct and bundle but that would be misusing
	// TODO: the API in a bad manner, not to mention not all needed commands are available to bundles.
	// TODO: So, the trick seems to be that a command buffer abstraction for D3D12 will likely need
	// TODO: to be multiple direct command buffers gathered up and then issued as a single submission.
	if (desc)
	{
		if (mRenderPass.mpRenderPass)
		{
			// Error, should not be in an active render pass.
			return Graphics::kAlreadyInRenderPass;
		}

		Graphics::iRenderPass* rPass = desc->mpRenderPass;
		Graphics::iFrameBuffer* fBuffer = desc->mpFrameBuffer;
		if (rPass && fBuffer)
		{
			mRenderPass = *desc;
			// TODO: Enable when everything is in the same command buffer.
//			mRenderPass.mpRenderPass->AddRef();
//			mRenderPass.mpFrameBuffer->AddRef();

			// TODO: Starting the render pass setup.  First step, just activate the first subpass.
			const RenderPass* renderPass = static_cast<RenderPass*>(rPass);
			const FrameBuffer* frameBuffer = static_cast<FrameBuffer*>(fBuffer);
			if (renderPass->GetSubPassCount() > 0)
			{
				CPF_ASSERT(frameBuffer->GetFrameBufferDesc().mAttachmentCount == renderPass->GetAttachments().size());
				// TODO: This will be cached in the command buffer object.
				Vector<Graphics::ResourceState> states(frameBuffer->GetImages().size());
				for (int32_t i=0; i<renderPass->GetAttachments().size(); ++i)
				{
					states[i] = renderPass->GetAttachments()[i].mStartState;
				}

				const auto& subPass = renderPass->GetSubPasses()[0];
				for (int32_t i = 0; i < subPass.mColorCount; ++i)
				{
					const auto& color = subPass.mpColorAttachments;
					const Graphics::ImageAndView& target = frameBuffer->GetImages()[color->mIndex];
					ImageTransition(
						target.mpImage,
						states[color->mIndex],
						color->mState,
						Graphics::SubResource::eAll
					);
					states[color->mIndex] = color->mState;

					// D3D12 only cares about LoadOp::eClear.
					if (renderPass->GetAttachments()[color->mIndex].mLoadOp == Graphics::LoadOp::eClear)
					{
						// TODO: Check this for consistency.  I.e. why are the values in reverse order?
						// TODO: Likely it is due to how the simd vectors are stored.
						Math::Vector4fv c(
							desc->mpClearValues[color->mIndex].mColor[3],
							desc->mpClearValues[color->mIndex].mColor[2],
							desc->mpClearValues[color->mIndex].mColor[1],
							desc->mpClearValues[color->mIndex].mColor[0]);

						Graphics::iImageView* imageViews[1] = { target.mpImageView };
						SetRenderTargets(1, imageViews, nullptr);
						ClearRenderTargetView(target.mpImageView, c, 0, nullptr);
					}
				}

				for (int32_t i = 0; i < subPass.mDepthStencilCount; ++i)
				{
					const auto& depth = subPass.mpDepthStencilAttachments;
					const Graphics::ImageAndView& target = frameBuffer->GetImages()[depth->mIndex];
					ImageTransition(
						target.mpImage,
						Graphics::ResourceState::ePresent,
						depth->mState,
						Graphics::SubResource::eAll
					);
					states[depth->mIndex] = depth->mState;

					if (renderPass->GetAttachments()[depth->mIndex].mLoadOp == Graphics::LoadOp::eClear)
					{
						ClearDepthStencilView(
							target.mpImageView,
							Graphics::DepthStencilClearFlag::eDepth,
							desc->mpClearValues[depth->mIndex].mDepthStencil.mDepth,
							desc->mpClearValues[depth->mIndex].mDepthStencil.mStencil,
							0,
							nullptr);
					}
				}
			}
		}
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL CommandBuffer::NextSubPass()
{
	if (mRenderPass.mpRenderPass)
	{
		
	}
	return Graphics::kNotInRenderPass;
}

COM::Result CPF_STDCALL CommandBuffer::EndRenderPass()
{
	if (mRenderPass.mpRenderPass)
	{
		// TODO: Re-enable when everything is in a single command buffer.
//		mRenderPass.mpFrameBuffer->Release();
//		mRenderPass.mpRenderPass->Release();
		mRenderPass = { 0 };
		return COM::kOK;
	}
	return Graphics::kNotInRenderPass;
}


//////////////////////////////////////////////////////////////////////////
void CommandBuffer::Submit(ID3D12CommandQueue* queue)
{
	for (const CommandListVector& clv : mCommandLists)
	{
		queue->ExecuteCommandLists(UINT(clv.size()), reinterpret_cast<ID3D12CommandList* const*>(clv.data()));
	}
}

COM::Result CommandBuffer::_AddCommandList()
{
	// Increase the current index.
	++mCurrent;

	// Make space if needed.
	if (mCurrent >= mCommandLists.size())
	{
		mCommandLists.push_back(CommandListVector());
		mCommandLists[mCurrent].push_back(CommandListPtr());
	}

	// Is a command list already allocated?
	if (mCommandLists[mCurrent][0])
	{
		// This is already allocated.
		return COM::kOK;
	}

	// This has not been allocated as of yet.
	ID3D12GraphicsCommandList* commandList = nullptr;
	if (SUCCEEDED(mpDevice->GetD3DDevice()->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		mpAllocator,
		nullptr,
		IID_PPV_ARGS(&commandList))))
	{
		mCommandLists[mCurrent][0] = commandList;
		mCommandLists.back()[0]->Close();
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL CommandBuffer::Insert(int32_t count, iCommandBuffer* const*)
{
	// Insert the given command lists into the vector at the top of the stack.

	(void)count;
	return COM::kError;
}
