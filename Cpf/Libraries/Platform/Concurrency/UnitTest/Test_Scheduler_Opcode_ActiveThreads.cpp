//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Opcodes.hpp"
#include "Atomic/Atomic.hpp"


namespace ConcurrencyTest
{
	struct CPF_ALIGN(16) TestData
	{
		int32_t HitCount;
		Cpf::Threading::Semaphore Complete;
	};
}


TEST(Concurrency, ActiveChange)
{
	using namespace Cpf;
	using namespace Concurrency;
	using namespace ConcurrencyTest;

	srand(int(Time::Value::Now().GetTicks()));

	static const auto loopCount = 1000;
	static const auto innerLoopCount = 1000;

	{
		TestData* testData = new TestData;
		Scheduler* scheduler = new Scheduler;

		scheduler->Initialize(Move(Threading::Thread::Group(Threading::Thread::GetHardwareThreadCount())));
		Scheduler::Queue queue;

		for (auto threads = 1; threads < scheduler->GetAvailableThreads(); ++threads)
		{
			testData->HitCount = 0;
			scheduler->SetActiveThreads(threads);

			for (auto i = 0; i < loopCount*threads; ++i)
			{
				queue.FirstOne(
					[](Scheduler::ThreadContext&, void* context)
				{
					CPF_ASSERT(reinterpret_cast<TestData*>(context)->HitCount < 0x7000);
					Atomic::Inc(reinterpret_cast<TestData*>(context)->HitCount);
					auto accumulator = 0;
					for (auto i = 0; i < innerLoopCount; ++i)
						accumulator += i;
				},
					testData);
			}
			// Creates a fence.
			queue.LastOneBarrier(
				[](Scheduler::ThreadContext&, void* context)
			{
				auto& sem = reinterpret_cast<TestData*>(context)->Complete;
				sem.Release();
			},
				testData);

			scheduler->Execute(queue);
			testData->Complete.Acquire();
			EXPECT_EQ(loopCount*threads, Cpf::Atomic::Load(testData->HitCount));
		}
		for (auto threads = scheduler->GetAvailableThreads(); threads > 0; --threads)
		{
			testData->HitCount = 0;
			scheduler->SetActiveThreads(threads);

			for (auto i = 0; i < loopCount*threads; ++i)
			{
				queue.FirstOne(
					[](Scheduler::ThreadContext&, void* context)
				{
					CPF_ASSERT(reinterpret_cast<TestData*>(context)->HitCount < 0x7000);
					Atomic::Inc(reinterpret_cast<TestData*>(context)->HitCount);
					auto accumulator = 0;
					for (auto i = 0; i < innerLoopCount; ++i)
						accumulator += i;
				},
					testData);
			}
			// Creates a fence.
			queue.LastOneBarrier(
				[](Scheduler::ThreadContext&, void* context)
			{
				auto& sem = reinterpret_cast<TestData*>(context)->Complete;
				sem.Release();
			},
				testData);

			scheduler->Execute(queue);
			testData->Complete.Acquire();
			EXPECT_EQ(loopCount*threads, Atomic::Load(testData->HitCount));
		}

		for (auto threads = 0; threads < 50; ++threads)
		{
			auto threadCount = int((rand() / float(RAND_MAX)) * (scheduler->GetAvailableThreads() - 1) + 1.49999f);
			threadCount = threadCount <= 0 ? 1 : threadCount > scheduler->GetAvailableThreads() ? scheduler->GetAvailableThreads() : threadCount;

			testData->HitCount = 0;
			scheduler->SetActiveThreads(threadCount);

			for (auto i = 0; i < loopCount*threadCount; ++i)
			{
				queue.FirstOne(
					[](Scheduler::ThreadContext&, void* context)
				{
					CPF_ASSERT(reinterpret_cast<TestData*>(context)->HitCount < 0x7000);
					Atomic::Inc(reinterpret_cast<TestData*>(context)->HitCount);
					auto accumulator = 0;
					for (auto i = 0; i < innerLoopCount; ++i)
						accumulator += i;
				},
					testData);
			}
			// Creates a fence.
			queue.LastOneBarrier(
				[](Scheduler::ThreadContext&, void* context)
			{
				auto& sem = reinterpret_cast<TestData*>(context)->Complete;
				sem.Release();
			},
				testData);

			scheduler->Execute(queue);
			testData->Complete.Acquire();
			EXPECT_EQ(loopCount*threadCount, Cpf::Atomic::Load(testData->HitCount));
		}

		scheduler->Shutdown();
		delete testData;
		delete scheduler;
	}
}