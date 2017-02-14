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
	ScopedInitializer<Platform::TimeInitializer> timeInit;

	//////////////////////////////////////////////////////////////////////////
	auto scheduler = new Scheduler;
	EXPECT_TRUE(scheduler != nullptr);
	if (scheduler)
	{
		//////////////////////////////////////////////////////////////////////////
		const int hardwareThreads = Platform::Threading::Thread::GetHardwareThreadCount();
		Platform::Threading::Thread::Group threads(hardwareThreads);
		EXPECT_TRUE(scheduler->Initialize(std::move(threads)));
		EXPECT_TRUE(scheduler->ThreadCount() >= 4);

		const int threadCount = 8 > hardwareThreads ? hardwareThreads : 8;
		Scheduler::Semaphore sync;
		auto activeQueue = scheduler->CreateQueue();
		activeQueue.ActiveThreads(threadCount);
		activeQueue.Submit(sync);
		activeQueue.Execute();
		sync.Acquire();
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

				Scheduler::Queue queue = scheduler->CreateQueue();
				for (int j = 0; j < loopCount; ++j)
				{
					testData.push_back({&hitCount, (j + 1) * threadCount });

					queue.AllBarrier( [](Scheduler::ThreadContext&, void* context)
					{
						Atomic::Inc(*reinterpret_cast<int*>(context));
					},
						&hitCount);

					queue.FirstOneBarrier( [](Scheduler::ThreadContext&, void* context)
					{
						auto testData = reinterpret_cast<TestData*>(context);
						EXPECT_EQ(Atomic::Load(*testData->mpCounter), testData->mExpected);
					},
						&testData[j]);
				}
				queue.Submit(sync);
				queue.Execute();
				sync.Acquire();
				EXPECT_EQ(threadCount * loopCount, hitCount);
			}
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}
