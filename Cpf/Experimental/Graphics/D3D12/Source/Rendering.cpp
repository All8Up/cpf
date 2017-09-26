//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"
#include "Atomic/Atomic.hpp"
#include "Graphics/TopologyType.hpp"
#include "Graphics/Viewport.hpp"
#include "Graphics/ResourceState.hpp"
#include "Graphics/SubResource.hpp"
#include "Graphics/DepthStencilClearFlag.hpp"
#include "Graphics/PrimitiveTopology.hpp"
#include "Graphics/iImageView.hpp"
#include "Graphics/Format.hpp"
#include "Graphics/RenderPassBeginDesc.hpp"
#include "Application/iWindow.hpp"
#include "Concurrency/WorkContext.hpp"
#include "Math/Vector4v.hpp"

using namespace CPF;
using namespace Math;
using namespace Graphics;


void ExperimentalD3D12::_BeginFrame(const Concurrency::WorkContext*)
{
	// Issue on the shared command buffers.
	mpPreCommandPool[mCurrentBackbuffer]->Reset();
	mpPreCommandBuffer[mCurrentBackbuffer]->Reset(mpPreCommandPool[mCurrentBackbuffer]);
	mpPreCommandBuffer[mCurrentBackbuffer]->Begin(nullptr);

	int32_t width, height;
	mpWindow->GetClientAreaSize(&width, &height);

	RenderPassBeginDesc beginDesc;
	beginDesc.mpRenderPass = mpRenderPass;
	beginDesc.mpFrameBuffer = mpFrameBuffers[mCurrentBackbuffer];
	beginDesc.mClipRect = { 0, width, 0, height };

	ClearValue clearValue[2];
	clearValue[0].mFormat = Format::eRGBA8un;
	clearValue[0].mValue.mColor[0] = 0.0f;
	clearValue[0].mValue.mColor[1] = 0.0f;
	clearValue[0].mValue.mColor[2] = 0.0f;
	clearValue[0].mValue.mColor[3] = 1.0f;
	clearValue[1].mFormat = Format::eD32f;
	clearValue[1].mValue.mDepthStencil.mDepth = 1.0f;
	clearValue[1].mValue.mDepthStencil.mStencil = 0;

	beginDesc.mClearValueCount = 2;
	beginDesc.mpClearValues = clearValue;
	mpPreCommandBuffer[mCurrentBackbuffer]->BeginRenderPass(&beginDesc);

	// Always the first to issue.
	mpScheduledBuffers[0] = mpPreCommandBuffer[mCurrentBackbuffer];
}

void ExperimentalD3D12::_Draw(const Concurrency::WorkContext* tc)
{
	ThreadData& threadData = *reinterpret_cast<ThreadData*>(tc->mpUserData);

	// Start issuing commands.
	threadData.mpCommandPool[mCurrentBackbuffer]->Reset();
	threadData.mpCommandBuffer[mCurrentBackbuffer]->Reset(threadData.mpCommandPool[mCurrentBackbuffer]);
	threadData.mpCommandBuffer[mCurrentBackbuffer]->Begin(mpPreCommandBuffer[mCurrentBackbuffer]);

	//////////////////////////////////////////////////////////////////////////
	/* Do some drawing...
	*/
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetResourceBinding(mpResourceBinding);
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetPipeline(mpPipeline);

	int32_t w, h;
	mpWindow->GetClientAreaSize(&w, &h);
	Viewport viewport{
		0.0f, 0.0f,
		float(w), float(h),
		0.0f, 1.0f
	};
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetViewports(1, &viewport);
	Rectanglei scissor(0, w, 0, h);
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetScissorRects(1, &scissor);
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetTopology(PrimitiveTopology::eTriangleList);

	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetConstantBuffer(0, mpViewProj);
	iVertexBuffer* vbs[2] = { mpVertexBuffer, mpInstanceBuffer[mCurrentBackbuffer] };
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetVertexBuffers(0, 2, vbs);
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetIndexBuffer(mpIndexBuffer);

	threadData.mpCommandBuffer[mCurrentBackbuffer]->DrawIndexedInstanced(36, kInstanceCount, 0, 0, 0);

	// End the command buffer prior to submission.
	threadData.mpCommandBuffer[mCurrentBackbuffer]->End();
	mpScheduledBuffers[Atomic::Inc(mCurrentScheduledBuffer) - 1] = threadData.mpCommandBuffer[mCurrentBackbuffer];
}

//#define DISABLE_RENDERING
void ExperimentalD3D12::_EndFrame(const Concurrency::WorkContext*)
{
	// Insert the drawing buffers.
	mpPreCommandBuffer[mCurrentBackbuffer]->Insert(mCurrentScheduledBuffer - 1, &mpScheduledBuffers[1]);

	// End the render pass.
	mpPreCommandBuffer[mCurrentBackbuffer]->EndRenderPass();

	// End the command buffer prior to submission.
	mpPreCommandBuffer[mCurrentBackbuffer]->End();

#ifndef DISABLE_RENDERING
	// Submit the command buffers.
	iCommandBuffer* buffers[1] = {mpPreCommandBuffer[mCurrentBackbuffer]};
	mpDevice->Submit(1, buffers);

	// Present the back buffer.
	mpSwapChain->Present();

	// Wait for completion.
	auto fenceToWaitFor = Atomic::Inc(mFenceTarget);
	mpDevice->Signal(mpFence, fenceToWaitFor);

	// TODO: This sure seems like a race condition but it is how all the examples seem to work.
	if (mpFence->GetValue() < fenceToWaitFor)
		mpFence->WaitFor(fenceToWaitFor);
#endif
}
