//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Opcodes.hpp"
#include "Atomic/Atomic.hpp"
#include "Atomic/Fence.hpp"
#include "Pair.hpp"


TEST(Concurrency, AllFenced_Opcode)
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Cpf;
	using namespace Concurrency;

	//////////////////////////////////////////////////////////////////////////
	auto scheduler = new Scheduler(nullptr);
	EXPECT_TRUE(scheduler != nullptr);
	if (scheduler)
	{
		//////////////////////////////////////////////////////////////////////////
		const int hardwareThreads = Threading::Thread::GetHardwareThreadCount();
		EXPECT_TRUE(COM::Succeeded(scheduler->Initialize(hardwareThreads, nullptr, nullptr, nullptr)));
		EXPECT_TRUE(scheduler->GetAvailableThreads() >= 4);

		const int threadCount = 8 > hardwareThreads ? hardwareThreads : 8;
		Semaphore sync;
		scheduler->SetActiveThreads(threadCount);
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

				Queue queue;
				for (int j = 0; j < loopCount; ++j)
				{
					testData.push_back({&hitCount, (j + 1) * threadCount });

					queue.AllBarrier( [](const WorkContext*, void* context)
					{
						Atomic::Inc(*reinterpret_cast<int*>(context));
					},
						&hitCount);

					queue.FirstOneBarrier( [](const WorkContext*, void* context)
					{
						auto testData = reinterpret_cast<TestData*>(context);
						EXPECT_EQ(Atomic::Load(*testData->mpCounter), testData->mExpected);
					},
						&testData[j]);
				}
				scheduler->Execute(queue);
				scheduler->Submit(&sync);
				sync.Acquire();
				EXPECT_EQ(threadCount * loopCount, hitCount);
			}
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}
