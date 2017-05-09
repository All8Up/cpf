//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "Concurrency/iFence.hpp"
#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Threading/Thread.hpp"
#include "Atomic/Atomic.hpp"
#include "Atomic/Fence.hpp"
#include "Vector.hpp"

TEST_F(ConcurrencyTest, AllFenced_Opcode)
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Cpf;
	using namespace Concurrency;

	//////////////////////////////////////////////////////////////////////////
	IntrusivePtr<iScheduler> pScheduler;
	EXPECT_TRUE(COM::Succeeded(GetRegistry()->Create(nullptr, kSchedulerCID, iScheduler::kIID, pScheduler.AsVoidPP())));
	EXPECT_TRUE(COM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

	IntrusivePtr<iFence> pFence;
	EXPECT_TRUE(COM::Succeeded(GetRegistry()->Create(nullptr, kFenceCID, iFence::kIID, pFence.AsVoidPP())));

	IntrusivePtr<iWorkBuffer> pWorkBuffer;
	EXPECT_TRUE(COM::Succeeded(GetRegistry()->Create(nullptr, kWorkBufferCID, iWorkBuffer::kIID, pWorkBuffer.AsVoidPP())));

	//////////////////////////////////////////////////////////////////////////
	const int hardwareThreads = Threading::Thread::GetHardwareThreadCount();
	EXPECT_TRUE(pScheduler->GetMaxThreads() >= 4);

	const int threadCount = 8 > hardwareThreads ? hardwareThreads : 8;
	pScheduler->SetActiveThreads(threadCount);
	{
		static const int testCount = 100;
		static const int loopCount = 200;

		for (int i = 0; i < testCount; ++i)
		{
			//////////////////////////////////////////////////////////////////////////
			int hitCount = 0;
			struct TestData
			{
				int* mpCounter;
				int mExpected;
			};
			Vector<TestData> testData;
			testData.clear();
			testData.reserve(loopCount);

			for (int j = 0; j < loopCount; ++j)
			{
				testData.push_back({ &hitCount, (j + 1) * threadCount });

				pWorkBuffer->AllBarrier([](const WorkContext*, void* context)
				{
					Atomic::Inc(*reinterpret_cast<int*>(context));
				},
					&hitCount);

				pWorkBuffer->FirstOneBarrier([](const WorkContext*, void* context)
				{
					auto testData = reinterpret_cast<TestData*>(context);
					EXPECT_EQ(Atomic::Load(*testData->mpCounter), testData->mExpected);
				},
					&testData[j]);
			}
			pScheduler->Execute(pWorkBuffer);
			pScheduler->Submit(pFence);
			pFence->Wait();
			EXPECT_EQ(threadCount * loopCount, hitCount);
		}
	}
	pScheduler->Shutdown();
}
