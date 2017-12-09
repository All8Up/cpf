//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "Concurrency/iFence.hpp"
#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Threading/Thread.hpp"
#include "Vector.hpp"
#include <atomic>

TEST_F(ConcurrencyTest, AllFenced_Opcode)
{
	//////////////////////////////////////////////////////////////////////////
	using namespace CPF;
	using namespace Concurrency;

	//////////////////////////////////////////////////////////////////////////
	IntrusivePtr<iScheduler> pScheduler;
	EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kSchedulerCID.GetID(), iScheduler::kIID.GetID(), pScheduler.AsVoidPP())));
	EXPECT_TRUE(GOM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

	IntrusivePtr<iFence> pFence;
	EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kFenceCID.GetID(), iFence::kIID.GetID(), pFence.AsVoidPP())));

	IntrusivePtr<iWorkBuffer> pWorkBuffer;
	EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kWorkBufferCID.GetID(), iWorkBuffer::kIID.GetID(), pWorkBuffer.AsVoidPP())));

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
			std::atomic<int> hitCount = 0;
			struct TestData
			{
				std::atomic<int>* mpCounter;
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
					(*reinterpret_cast<std::atomic<int>*>(context)).fetch_add(1);
				},
					&hitCount);

				pWorkBuffer->FirstOneBarrier([](const WorkContext*, void* context)
				{
					auto testData = reinterpret_cast<TestData*>(context);
					EXPECT_EQ((*testData->mpCounter).load(), testData->mExpected);
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
