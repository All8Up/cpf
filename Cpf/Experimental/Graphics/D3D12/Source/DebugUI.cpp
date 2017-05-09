//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"
#include "Graphics/iImageView.hpp"
#include "Concurrency/WorkContext.hpp"
#include "Atomic/Atomic.hpp"
#include "Std/Std.hpp"

using namespace Cpf;
using namespace Platform;

void ExperimentalD3D12::_UpdatePipelineDisplay()
{
	if (mpInstructionList)
	{
		for (int i = 0; i < mInstructionCount; ++i)
		{
			delete[] mpInstructionList[i];
		}
		delete[] mpInstructionList;
	}

	const char* tempString = nullptr;
	Vector<String> queueInfo;
	for (int index = 0; mpMultiCore->GetQueueInfo(index, &tempString) == COM::kOK; ++index)
		queueInfo.push_back(tempString);
	mInstructionCount = int(queueInfo.size());

	mpInstructionList = new char*[mInstructionCount];
	int i = 0;
	for (const auto& string : queueInfo)
	{
		mpInstructionList[i] = new char[string.size() + 1];
		strcpy(mpInstructionList[i++], string.c_str());
	}
}

void ExperimentalD3D12::_DebugUI(const Concurrency::WorkContext* tc)
{
	// Open the command buffer.
	ThreadData& threadData = *reinterpret_cast<ThreadData*>(tc->mpUserData);

	threadData.mpDebugUIPool[mCurrentBackbuffer]->Reset();
	threadData.mpDebugUIBuffer[mCurrentBackbuffer]->Reset(threadData.mpDebugUIPool[mCurrentBackbuffer]);
	threadData.mpDebugUIBuffer[mCurrentBackbuffer]->Begin(mpPreCommandBuffer[mCurrentBackbuffer]);

	mpDebugUI->BeginFrame(threadData.mpDebugUIBuffer[mCurrentBackbuffer], float(Time::Seconds(mDeltaTime)));
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
		mpDebugUI->Begin("Performance", &sShowPerformance);
		mpDebugUI->PushItemWidth(300);
		mpDebugUI->Text("Instance Count: %d", kInstanceCount);
		mpDebugUI->Separator();
		mpDebugUI->Text("FPS: %d LOW: %d HIGH: %d", int(average), int(lowFPS), int(highFPS));
		if (mpDebugUI->Slider("Thread Count", &mThreadCount, 1, mpScheduler->GetMaxThreads()))
			mThreadCountChanged = true;
		mpDebugUI->Histogram("FPS Histogram", history, kHistorySize, 0, nullptr, lowFPS, highFPS);

//		if (mGOService.GetStagesChanged())
		{}
		mpDebugUI->ListBox("Thread Pipeline", &mSelectedInstruction, const_cast<const char**>(mpInstructionList), mInstructionCount);

		mpDebugUI->Separator();
		static bool movementEnabled = true;
		if (mpDebugUI->CheckBox("Enable Movement", &movementEnabled))
		{
			mpMoverSystem->EnableMovement(movementEnabled);
		}

		mpDebugUI->End();
	}
	mpDebugUI->EndFrame(threadData.mpDebugUIBuffer[mCurrentBackbuffer]);

	threadData.mpDebugUIBuffer[mCurrentBackbuffer]->End();
	mpScheduledBuffers[Atomic::Inc(mCurrentScheduledBuffer) - 1] = threadData.mpDebugUIBuffer[mCurrentBackbuffer];
}
