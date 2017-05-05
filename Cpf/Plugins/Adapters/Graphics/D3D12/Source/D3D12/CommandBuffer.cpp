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
#include "Graphics/FrameBufferDesc.hpp"
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
	, mSubPass(0)
	, mType(Graphics::CommandBufferType::kPrimary)
	, mRenderPass{0}
	, mColorViewCount(0)
	, mpDepthBufferView(nullptr)
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
			End();
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

void CPF_STDCALL CommandBuffer::Begin(iCommandBuffer* primary)
{
	if (primary)
	{
		CommandBuffer* p = static_cast<CommandBuffer*>(primary);
		SetRenderTargets(p->mColorViewCount, p->mpColorViews, p->mpDepthBufferView);
	}
}

void CPF_STDCALL CommandBuffer::End()
{
	_Current()->Close();
}

void CPF_STDCALL CommandBuffer::Reset(Graphics::iCommandPool* pool)
{
	// TODO: Consider if the pipeline can/should be passed in.  Probably would not work in Vulkan and/or Metal though.
	CommandPool* d3dPool = static_cast<CommandPool*>(pool);
	mHeaps.clear();

	// Remove inserted references to other command lists but do not free the owned items.
	mColorViewCount = 0;
	mCurrent = 0;
	int index = 0;
	mCommandLists[0][0]->Reset(d3dPool->GetCommandAllocator(), nullptr);
	for (CommandListVector& clv : mCommandLists)
	{
		clv.resize(1);
		++index;
	}
}

void CPF_STDCALL CommandBuffer::UpdateSubResource(Graphics::iResource* src, Graphics::iResource* dst, const Graphics::ResourceData* data)
{
	D3D12_SUBRESOURCE_DATA resData = { data->mpData, LONG_PTR(data->mPitch), LONG_PTR(data->mSlicePitch) };
	UpdateSubresources<1>(
		_Current(),
		static_cast<Resource*>(dst)->GetResource(),
		static_cast<Resource*>(src)->GetResource(),
		0, 0, 1, &resData);
}

void CPF_STDCALL CommandBuffer::ResourceBarrier(Graphics::iResource* resource, Graphics::ResourceState startState, Graphics::ResourceState endState)
{
	Resource* res = static_cast<Resource*>(resource);
	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(res->GetResource(), D3D12_RESOURCE_STATES(startState), D3D12_RESOURCE_STATES(endState));
	_Current()->ResourceBarrier(1, &barrier);
}

void CPF_STDCALL CommandBuffer::ImageTransition(
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

void CPF_STDCALL CommandBuffer::SetResourceBinding(Graphics::iResourceBinding* binding)
{
	ResourceBinding* resBinding = static_cast<ResourceBinding*>(binding);
	_Current()->SetGraphicsRootSignature(resBinding->GetSignature());
}

void CPF_STDCALL CommandBuffer::SetPipeline(Graphics::iPipeline* pipeline)
{
	Pipeline* pipe = static_cast<Pipeline*>(pipeline);
	_Current()->SetPipelineState(pipe->GetPipelineState());
}

void CPF_STDCALL CommandBuffer::SetViewports(int32_t count, const Graphics::Viewport* rects)
{
	_Current()->RSSetViewports(count, reinterpret_cast<const D3D12_VIEWPORT*>(rects));
}

void CPF_STDCALL CommandBuffer::SetScissorRects(int32_t count, const Math::Rectanglei* rects)
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

void CPF_STDCALL CommandBuffer::SetTopology(Graphics::PrimitiveTopology topology)
{
	_Current()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY(topology));
}

void CPF_STDCALL CommandBuffer::SetVertexBuffers(int32_t startSlot, int32_t viewCount, Graphics::iVertexBuffer** inViews)
{
	D3D12_VERTEX_BUFFER_VIEW views[16];
	for (int i = 0; i < viewCount; ++i)
		views[i] = *static_cast<VertexBuffer*>(inViews[i])->GetView();
	_Current()->IASetVertexBuffers(UINT(startSlot), UINT(viewCount), views);
}

void CPF_STDCALL CommandBuffer::SetIndexBuffer(Graphics::iIndexBuffer* ib)
{
	_Current()->IASetIndexBuffer(static_cast<IndexBuffer*>(ib)->GetView());
}

void CPF_STDCALL CommandBuffer::SetConstantBuffer(int32_t index, Graphics::iConstantBuffer* cb)
{
	ConstantBuffer* cbuffer = static_cast<ConstantBuffer*>(cb);
	_Current()->SetGraphicsRootConstantBufferView(UINT(index), cbuffer->GetGPUAddress());
}

void CPF_STDCALL CommandBuffer::SetConstants(int32_t index, int32_t count, const void* data, int32_t offset)
{
	_Current()->SetGraphicsRoot32BitConstants(UINT(index), UINT(count), data, UINT(offset));
}

void CPF_STDCALL CommandBuffer::SetSampler(int32_t index, Graphics::iSampler* sampler)
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

void CPF_STDCALL CommandBuffer::SetImage(int32_t index, Graphics::iImage* image)
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

void CPF_STDCALL CommandBuffer::DrawInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t startInstance)
{
	_Current()->DrawInstanced(UINT(vertsPerInstance), UINT(instances), UINT(startVert), UINT(startInstance));
}

void CPF_STDCALL CommandBuffer::DrawIndexedInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t offset, int32_t startInstance)
{
	_Current()->DrawIndexedInstanced(UINT(vertsPerInstance), UINT(instances), UINT(startVert), UINT(offset), UINT(startInstance));
}

void CPF_STDCALL CommandBuffer::SetRenderTargets(int32_t imageCount, Graphics::iImageView** images, Graphics::iImageView* depthView)
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

void CPF_STDCALL CommandBuffer::ClearRenderTargetView(Graphics::iImageView* view, Math::Vector4fv& color, int32_t count, const Math::Rectanglei* rects)
{
	// TODO: Clean up the casts and validate that the rects are the same style.
	_Current()->ClearRenderTargetView(
		static_cast<ImageView*>(view)->GetDescriptor(),
		reinterpret_cast<float*>(&color),
		count,
		reinterpret_cast<const D3D12_RECT*>(rects));
}

void CPF_STDCALL CommandBuffer::ClearDepthStencilView(Graphics::iImageView* view, Graphics::DepthStencilClearFlag flags, float depth, uint8_t stencil, int32_t count, const Math::Rectanglei* rects)
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
			// Store the render pass information.
			mRenderPass = *desc;
			mRenderPass.mpRenderPass->AddRef();
			mRenderPass.mpFrameBuffer->AddRef();
			mSubPass = 0;

			// Initialize the attachment state array.
			const RenderPass* renderPass = static_cast<RenderPass*>(rPass);
			const auto& attachments = renderPass->GetRenderPassDesc().mAttachments;
			mAttachmentStates.resize(attachments.size());
			for (int32_t i = 0; i < attachments.size(); ++i)
				mAttachmentStates[i] = attachments[i].mStartState;

			return _StartSubPass();
		}
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL CommandBuffer::NextSubPass()
{
	if (mRenderPass.mpRenderPass)
	{
		_EndSubPass();
		_AddCommandList();
		++mSubPass;
		return _StartSubPass();
	}
	return Graphics::kNotInRenderPass;
}

COM::Result CPF_STDCALL CommandBuffer::EndRenderPass()
{
	if (mRenderPass.mpRenderPass)
	{
		// Perform final transitions.
		const RenderPass* renderPass = static_cast<RenderPass*>(mRenderPass.mpRenderPass);
		const FrameBuffer* frameBuffer = static_cast<FrameBuffer*>(mRenderPass.mpFrameBuffer);
		const Graphics::FrameBufferDesc& desc = frameBuffer->GetFrameBufferDesc();
		NextSubPass();

		// Batch setup.
		constexpr int kMaxBatch = 16;
		D3D12_RESOURCE_BARRIER barrier[kMaxBatch];

		//////////////////////////////////////////////////////////////////////////
		const auto& attachments = renderPass->GetRenderPassDesc().mAttachments;
		int currentIndex = 0;
		for (int i = 0; i < desc.mAttachmentCount; ++i)
		{
			const auto currentState = mAttachmentStates[i];
			const auto targetState = attachments[i].mFinalState;
			if (currentState != targetState)
			{
				_MakeBarrier(barrier + currentIndex, static_cast<Image*>(frameBuffer->GetImages()[i].mpImage), currentState, targetState);
				++currentIndex;
			}
		}

		// Issue the barriers.
		_Current()->ResourceBarrier(currentIndex, barrier);

		// Clear the references to the render pass.
		mRenderPass.mpFrameBuffer->Release();
		mRenderPass.mpRenderPass->Release();
		mRenderPass = { 0 };
		return COM::kOK;
	}
	return Graphics::kNotInRenderPass;
}

void CommandBuffer::Submit(ID3D12CommandQueue* queue)
{
	for (int32_t i = 0; i <= mCurrent; ++i)
	{
		const CommandListVector& clv = mCommandLists[i];
		queue->ExecuteCommandLists(UINT(clv.size()), reinterpret_cast<ID3D12CommandList* const*>(clv.data()));
	}
}

COM::Result CommandBuffer::_AddCommandList()
{
	// Close the command list in current use.
	if (mCurrent>=0)
		End();

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
		// This is already allocated, reset it.
		mCommandLists[mCurrent][0]->Reset(mpAllocator, nullptr);
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
		return COM::kOK;
	}
	return COM::kError;
}

COM::Result CPF_STDCALL CommandBuffer::Insert(int32_t count, iCommandBuffer* const* buffers)
{
	if (buffers)
	{
		// Insert the given command lists into the vector at the top of the stack.
		for (int i = 0; i < count; ++i)
		{
			CommandListVector& current = mCommandLists[mCurrent];
			auto buffer = static_cast<CommandBuffer*>(buffers[i])->mCommandLists[0][0];
			current.push_back(buffer);
		}
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

void CommandBuffer::_MakeBarrier(D3D12_RESOURCE_BARRIER* barrier, Image* image, Graphics::ResourceState begin, Graphics::ResourceState end)
{
	barrier->Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier->Transition.pResource = image->GetResource();
	barrier->Transition.StateBefore = Convert(begin);
	barrier->Transition.StateAfter = Convert(end);
	barrier->Transition.Subresource = Convert(Graphics::SubResource::eAll);
	barrier->Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
}

COM::Result CommandBuffer::_StartSubPass()
{
	Graphics::iRenderPass* rPass = mRenderPass.mpRenderPass;
	Graphics::iFrameBuffer* fBuffer = mRenderPass.mpFrameBuffer;
	if (rPass && fBuffer)
	{
		const RenderPass* renderPass = static_cast<RenderPass*>(rPass);
		const FrameBuffer* frameBuffer = static_cast<FrameBuffer*>(fBuffer);
		const auto& attachments = renderPass->GetRenderPassDesc().mAttachments;

		if (renderPass->GetRenderPassDesc().mSubPasses.size() > mSubPass)
		{
			const auto& subPasses = renderPass->GetRenderPassDesc().mSubPasses;
			CPF_ASSERT(!subPasses.empty());
			CPF_ASSERT(frameBuffer->GetFrameBufferDesc().mAttachmentCount == renderPass->GetRenderPassDesc().mAttachments.size());

			// Batch setup.
			constexpr int kMaxBatch = 16;
			D3D12_RESOURCE_BARRIER barrier[kMaxBatch];

			//////////////////////////////////////////////////////////////////////////
			const auto& subPass = subPasses[mSubPass];
			int currentIndex = 0;
			for (const auto& color : subPass.mColorAttachments)
			{
				const Graphics::ImageAndView& target = frameBuffer->GetImages()[color.mIndex];
				_MakeBarrier(barrier + currentIndex, static_cast<Image*>(target.mpImage), mAttachmentStates[color.mIndex], color.mState);
				++currentIndex;
				mAttachmentStates[color.mIndex] = color.mState;
			}
			
			if (subPass.mDepthStencilAttachment.mIndex != Graphics::kInvalidAttachment)
			{
				const Graphics::ImageAndView& target = frameBuffer->GetImages()[subPass.mDepthStencilAttachment.mIndex];
				_MakeBarrier(
					barrier + currentIndex,
					static_cast<Image*>(target.mpImage),
					mAttachmentStates[subPass.mDepthStencilAttachment.mIndex],
					subPass.mDepthStencilAttachment.mState);
				++currentIndex;
				mAttachmentStates[subPass.mDepthStencilAttachment.mIndex] = subPass.mDepthStencilAttachment.mState;
			}

			// Issue the barriers.
			_Current()->ResourceBarrier(currentIndex, barrier);

			//////////////////////////////////////////////////////////////////////////
			// Issue clears.
			for (const auto& color : subPass.mColorAttachments)
			{
				const Graphics::ImageAndView& target = frameBuffer->GetImages()[color.mIndex];
				if (attachments[color.mIndex].mLoadOp == Graphics::LoadOp::eClear)
				{
					Math::Vector4fv c(
						mRenderPass.mpClearValues[color.mIndex].mColor[0],
						mRenderPass.mpClearValues[color.mIndex].mColor[1],
						mRenderPass.mpClearValues[color.mIndex].mColor[2],
						mRenderPass.mpClearValues[color.mIndex].mColor[3]);

					ClearRenderTargetView(target.mpImageView, c, 0, nullptr);
				}
				mpColorViews[mColorViewCount++] = target.mpImageView;
			}
			SetRenderTargets(
				mColorViewCount,
				mpColorViews,
				subPass.mDepthStencilAttachment.mIndex != Graphics::kInvalidAttachment ?
					frameBuffer->GetImages()[subPass.mDepthStencilAttachment.mIndex].mpImageView :
					nullptr
			);
			if (subPass.mDepthStencilAttachment.mIndex != Graphics::kInvalidAttachment)
			{
				mpDepthBufferView = frameBuffer->GetImages()[subPass.mDepthStencilAttachment.mIndex].mpImageView;
				const Graphics::ImageAndView& target = frameBuffer->GetImages()[subPass.mDepthStencilAttachment.mIndex];
				if (attachments[subPass.mDepthStencilAttachment.mIndex].mLoadOp == Graphics::LoadOp::eClear)
				{
					ClearDepthStencilView(
						target.mpImageView,
						Graphics::DepthStencilClearFlag::eDepth,
						mRenderPass.mpClearValues[subPass.mDepthStencilAttachment.mIndex].mDepthStencil.mDepth,
						mRenderPass.mpClearValues[subPass.mDepthStencilAttachment.mIndex].mDepthStencil.mStencil,
						0,
						nullptr);
				}
			}

			return COM::kOK;
		}
	}
	return COM::kError;
}

COM::Result CommandBuffer::_EndSubPass()
{
	// Primarily this will run resolves.

	return COM::kOK;
}
