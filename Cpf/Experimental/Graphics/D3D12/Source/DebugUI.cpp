//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"
#include "Time/Time.hpp"

using namespace Cpf;
using namespace Platform;

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
	{
		static constexpr int kHistorySize = 50;
		static Time::Value history[kHistorySize];
		static Time::Value accumulation;
		static int historyIndex = 0;

		accumulation -= history[historyIndex];
		history[historyIndex++] = mDeltaTime;
		accumulation += mDeltaTime;
		if (historyIndex >= kHistorySize)
			historyIndex = 0;

		Time::Value averageTicks = accumulation / float(kHistorySize);
		float average = float(Time::Seconds(averageTicks));

		static bool sShowPerformance = true;
		mDebugUI.Begin("Performance", &sShowPerformance);
		mDebugUI.Text("FPS: %f", 1.0f / average);
		if (mDebugUI.Slider("Thread Count", &mThreadCount, 1, mScheduler.ThreadCount()))
			mThreadCountChanged = true;
		mDebugUI.End();
	}
	mDebugUI.EndFrame(threadData.mpDebugUIBuffer[mCurrentBackbuffer]);

	threadData.mpDebugUIBuffer[mCurrentBackbuffer]->End();
	mpScheduledBuffers[Atomic::Inc(mCurrentScheduledBuffer) - 1] = threadData.mpDebugUIBuffer[mCurrentBackbuffer];
}
