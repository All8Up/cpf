//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/CommandBuffer.hpp"
#include "Adapter/D3D12/CommandPool.hpp"
#include "Adapter/D3D12/Device.hpp"
#include "Adapter/D3D12/SwapChain.hpp"
#include "Adapter/D3D12/Image.hpp"
#include "Adapter/D3D12/Fence.hpp"
#include "Adapter/D3D12/D3D12Utils.hpp"
#include "Adapter/D3D12/Resource.hpp"
#include "Adapter/D3D12/ResourceBinding.hpp"
#include "Adapter/D3D12/Pipeline.hpp"
#include "Adapter/D3D12/IndexBuffer.hpp"
#include "Adapter/D3D12/VertexBuffer.hpp"
#include "Adapter/D3D12/ConstantBuffer.hpp"
#include "Graphics/ResourceData.hpp"
#include "Logging/Logging.hpp"
#include "Adapter/D3D12/Sampler.hpp"
#include "Graphics/DepthStencilClearFlag.hpp"

using namespace Cpf;
using namespace Adapter;
using namespace D3D12;

CommandBuffer::CommandBuffer(Graphics::iDevice* device, Graphics::iCommandPool* pool CPF_GFX_DEBUG_PARAM_DEF)
	: mpDevice(static_cast<Device*>(device))
	, mHeapsDirty(false)
{
	Device* d3dDevice = static_cast<Device*>(device);
	CommandPool* d3dPool = static_cast<CommandPool*>(pool);
	d3dDevice->GetD3DDevice()->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		d3dPool->GetCommandAllocator(),
		nullptr,
		IID_PPV_ARGS(mpCommandList.AsTypePP()));
	mpCommandList->Close();

	CPF_LOG(D3D12, Info) << "Created command buffer: " << intptr_t(this) << " - " << intptr_t(mpCommandList.Ptr());

#ifdef CPF_GFX_TRACKING
	if (dbgFilename)
	{
		std::wstringstream str;
		str << dbgFilename << " : " << dbgLineNumber;
		mpCommandList->SetName(str.str().c_str());
	}
#endif
}

CommandBuffer::~CommandBuffer()
{
	CPF_LOG(D3D12, Info) << "Destroyed command buffer: " << intptr_t(this) << " - " << intptr_t(mpCommandList.Ptr());
}

void CommandBuffer::Begin()
{}

void CommandBuffer::End()
{
	mpCommandList->Close();
}

void CommandBuffer::Reset(Graphics::iCommandPool* pool)
{
	// TODO: Consider if the pipeline can/should be passed in.  Probably would not work in Vulkan and/or Metal though.
	CommandPool* d3dPool = static_cast<CommandPool*>(pool);
	mpCommandList->Reset(d3dPool->GetCommandAllocator(), nullptr);
	mHeaps.clear();
}

void CommandBuffer::UpdateSubResource(Graphics::iResource* src, Graphics::iResource* dst, const Graphics::ResourceData* data)
{
	D3D12_SUBRESOURCE_DATA resData = { data->mpData, LONG_PTR(data->mPitch), LONG_PTR(data->mSlicePitch) };
	UpdateSubresources<1>(
		mpCommandList,
		static_cast<Resource*>(dst)->GetResource(),
		static_cast<Resource*>(src)->GetResource(),
		0, 0, 1, &resData);
}

void CommandBuffer::ResourceBarrier(Graphics::iResource* resource, Graphics::ResourceState startState, Graphics::ResourceState endState)
{
	Resource* res = static_cast<Resource*>(resource);
	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(res->GetResource(), D3D12_RESOURCE_STATES(startState), D3D12_RESOURCE_STATES(endState));
	mpCommandList->ResourceBarrier(1, &barrier);
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
	mpCommandList->ResourceBarrier(1, &barrier);
}

void CommandBuffer::SetResourceBinding(Graphics::iResourceBinding* binding)
{
	ResourceBinding* resBinding = static_cast<ResourceBinding*>(binding);
	mpCommandList->SetGraphicsRootSignature(resBinding->GetSignature());
}

void CommandBuffer::SetPipeline(Graphics::iPipeline* pipeline)
{
	Pipeline* pipe = static_cast<Pipeline*>(pipeline);
	mpCommandList->SetPipelineState(pipe->GetPipelineState());
}

void CommandBuffer::SetViewports(int32_t count, const Graphics::Viewport* rects)
{
	mpCommandList->RSSetViewports(count, reinterpret_cast<const D3D12_VIEWPORT*>(rects));
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
	mpCommandList->RSSetScissorRects(UINT(count), r);
}

void CommandBuffer::SetTopology(Graphics::PrimitiveTopology topology)
{
	mpCommandList->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY(topology));
}

void CommandBuffer::SetVertexBuffers(int32_t startSlot, int32_t viewCount, Graphics::iVertexBuffer** inViews)
{
	D3D12_VERTEX_BUFFER_VIEW views[16];
	for (int i = 0; i < viewCount; ++i)
		views[i] = *static_cast<VertexBuffer*>(inViews[i])->GetView();
	mpCommandList->IASetVertexBuffers(UINT(startSlot), UINT(viewCount), views);
}

void CommandBuffer::SetIndexBuffer(Graphics::iIndexBuffer* ib)
{
	mpCommandList->IASetIndexBuffer(static_cast<IndexBuffer*>(ib)->GetView());
}

void CommandBuffer::SetConstantBuffer(int32_t index, Graphics::iConstantBuffer* cb)
{
	ConstantBuffer* cbuffer = static_cast<ConstantBuffer*>(cb);
	mpCommandList->SetGraphicsRootConstantBufferView(UINT(index), cbuffer->GetGPUAddress());
}

void CommandBuffer::SetConstants(int32_t index, int32_t count, const void* data, int32_t offset)
{
	mpCommandList->SetGraphicsRoot32BitConstants(UINT(index), UINT(count), data, UINT(offset));
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
	mpCommandList->SetDescriptorHeaps(i, heaps);
	mpCommandList->SetGraphicsRootDescriptorTable(index, d3d12Sampler->GetDescriptor());
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
	mpCommandList->SetDescriptorHeaps(i, heaps);
	mpCommandList->SetGraphicsRootDescriptorTable(index, d3d12Image->GetDescriptor());
}

void CommandBuffer::DrawInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t startInstance)
{
	mpCommandList->DrawInstanced(UINT(vertsPerInstance), UINT(instances), UINT(startVert), UINT(startInstance));
}

void CommandBuffer::DrawIndexedInstanced(int32_t vertsPerInstance, int32_t instances, int32_t startVert, int32_t offset, int32_t startInstance)
{
	mpCommandList->DrawIndexedInstanced(UINT(vertsPerInstance), UINT(instances), UINT(startVert), UINT(offset), UINT(startInstance));
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
		mpCommandList->OMSetRenderTargets(imageCount, imageDescs, FALSE, &depthViewHandle);
	}
	else
		mpCommandList->OMSetRenderTargets(imageCount, imageDescs, FALSE, nullptr);
}

void CommandBuffer::ClearRenderTargetView(Graphics::iImageView* view, Math::Vector4fv& color, int32_t count, const Math::Rectanglei* rects)
{
	// TODO: Clean up the casts and validate that the rects are the same style.
	mpCommandList->ClearRenderTargetView(
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
	mpCommandList->ClearDepthStencilView(
		static_cast<ImageView*>(view)->GetDescriptor(),
		d3dFlags,
		depth,
		stencil,
		count,
		reinterpret_cast<const D3D12_RECT*>(rects)
	);
}
