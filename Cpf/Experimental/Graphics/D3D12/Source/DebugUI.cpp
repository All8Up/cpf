//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"
#include "Std/Std.hpp"

using namespace Cpf;
using namespace Platform;

void ExperimentalD3D12::_UpdateStageList()
{
	{
		if (mpStageList)
		{
			for (int i = 0; i < mStageListCount; ++i)
			{
				delete[] mpStageList[i];
			}
			delete[] mpStageList;
		}

		mStageListCount = int(mpMultiCore->GetStages().size());
		mpStageList = new char*[mStageListCount];
		int i = 0;
		for (auto& stage : mpMultiCore->GetStages())
		{
			if (stage)
			{
				size_t stringSize = stage->GetSystem()->GetName().size() + stage->GetName().size() + 4;
				mpStageList[i] = new char[stringSize];
				strcpy(mpStageList[i], stage->GetSystem()->GetName().c_str());
				strcat(mpStageList[i], " - ");
				strcat(mpStageList[i++], stage->GetName().c_str());
			}
			else
			{
				static const String barrier("-- barrier --");
				mpStageList[i] = new char[barrier.size() + 1];
				strcpy(mpStageList[i++], barrier.c_str());
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	{
		if (mpInstructionList)
		{
			for (int i = 0; i < mInstructionCount; ++i)
			{
				delete[] mpInstructionList[i];
			}
			delete[] mpInstructionList;
		}

		auto instructions = mQueue.Dissassemble();
		mInstructionCount = int(instructions.size());

		mpInstructionList = new char*[mInstructionCount];
		int i = 0;
		for (auto& instruction : instructions)
		{
			String description = mQueue.GetOpName(instruction.mOp);
			description += " : " + std::to_string(intptr_t(instruction.mpPayload)) + " : " + std::to_string(intptr_t(instruction.mpContext));
			mpInstructionList[i] = new char[description.size() + 1];
			strcpy(mpInstructionList[i++], description.c_str());
		}
	}
}

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

	mDebugUI.BeginFrame(threadData.mpDebugUIBuffer[mCurrentBackbuffer], Time::Seconds(mDeltaTime));
	{
		static constexpr int kHistorySize = 50;
		static float history[kHistorySize];
		static float accumulation;
		static int historyIndex = 0;

		accumulation -= history[historyIndex];
		history[historyIndex++] = 1.0f / float(Time::Seconds(mDeltaTime));
		accumulation += 1.0f / float(Time::Seconds(mDeltaTime));
		if (historyIndex >= kHistorySize)
			historyIndex = 0;
		float lowFPS = 1000000, highFPS = 0;
		for (auto fps : history)
		{
			lowFPS = Min(lowFPS, fps);
			highFPS = Max(highFPS, fps);
		}

		float averageTicks = accumulation / float(kHistorySize);
		float average = float(Time::Seconds(averageTicks));

		static bool sShowPerformance = true;
		mDebugUI.Begin("Performance", &sShowPerformance);
		mDebugUI.PushItemWidth(300);
		mDebugUI.Text("Instance Count: %d", kInstanceCount);
		mDebugUI.Separator();
		mDebugUI.Text("FPS: %d LOW: %d HIGH: %d", int(average), int(lowFPS), int(highFPS));
		if (mDebugUI.Slider("Thread Count", &mThreadCount, 1, mScheduler.ThreadCount()))
			mThreadCountChanged = true;
		mDebugUI.Histogram("FPS Histogram", history, kHistorySize, 0, nullptr, lowFPS, highFPS);

//		if (mGOService.GetStagesChanged())
		{}
		mDebugUI.ListBox("Stages", &mSelectedStage, const_cast<const char**>(mpStageList), mStageListCount);
		mDebugUI.ListBox("Instructions", &mSelectedInstruction, const_cast<const char**>(mpInstructionList), mInstructionCount);

		mDebugUI.Separator();
		static bool movementEnabled = true;
		if (mDebugUI.CheckBox("Enable Movement", &movementEnabled))
		{
			mpMoverSystem->EnableMovement(movementEnabled);
		}
		static bool usingEBus = false;
		if (mDebugUI.CheckBox("Use EBus Approx", &usingEBus))
		{
			mpMoverSystem->UseEBus(usingEBus);
		}

		mDebugUI.End();
	}
	mDebugUI.EndFrame(threadData.mpDebugUIBuffer[mCurrentBackbuffer]);

	threadData.mpDebugUIBuffer[mCurrentBackbuffer]->End();
	mpScheduledBuffers[Atomic::Inc(mCurrentScheduledBuffer) - 1] = threadData.mpDebugUIBuffer[mCurrentBackbuffer];
}
