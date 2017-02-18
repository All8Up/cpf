//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"

using namespace Cpf;

void ExperimentalD3D12::_DebugUI(Concurrency::ThreadContext& tc)
{
	// Open the command buffer.
	ThreadData& threadData = *reinterpret_cast<ThreadData*>(tc.GetUserData());

	threadData.mpDebugUIPool[mCurrentBackbuffer]->Reset();
	threadData.mpDebugUIBuffer[mCurrentBackbuffer]->Reset(threadData.mpDebugUIPool[mCurrentBackbuffer]);
	threadData.mpDebugUIBuffer[mCurrentBackbuffer]->Begin();

	int32_t backBuffer = Atomic::Load(mCurrentBackbuffer);
	Graphics::iImageView* imageViews[] = { mpSwapChain->GetImageView(backBuffer) };
	threadData.mpDebugUIBuffer[mCurrentBackbuffer]->SetRenderTargets(1, imageViews, mpDepthBufferImageViews[backBuffer]);

	mDebugUI.BeginFrame(threadData.mpDebugUIBuffer[mCurrentBackbuffer], Platform::Time::Seconds(mDeltaTime));
	mDebugUI.EndFrame(threadData.mpDebugUIBuffer[mCurrentBackbuffer]);

	threadData.mpDebugUIBuffer[mCurrentBackbuffer]->End();
	mpScheduledBuffers[Atomic::Inc(mCurrentScheduledBuffer) - 1] = threadData.mpDebugUIBuffer[mCurrentBackbuffer];
}
