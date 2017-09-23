//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "gmock/gmock.h"
#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Concurrency/iFence.hpp"
#include "Atomic/Atomic.hpp"
#include "Threading/Thread.hpp"
#include "Threading/Semaphore.hpp"

namespace ConcurrencyTestData
{
	struct CPF_ALIGN(16) TestData
	{
		int32_t HitCount;
		CPF::Threading::Semaphore Complete;
	};
}


TEST_F(ConcurrencyTest, ActiveChange)
{
	using namespace CPF;
	using namespace Concurrency;
	using namespace ConcurrencyTestData;

	srand(int(Time::Value::Now().GetTicks()));

	static const auto loopCount = 1000;
	static const auto innerLoopCount = 1000;

	{
		TestData* testData = new TestData;

		IntrusivePtr<iScheduler> pScheduler;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kSchedulerCID.GetID(), iScheduler::kIID.GetID(), pScheduler.AsVoidPP())));
		EXPECT_TRUE(GOM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

		IntrusivePtr<iFence> pFence;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kFenceCID.GetID(), iFence::kIID.GetID(), pFence.AsVoidPP())));

		IntrusivePtr<iWorkBuffer> pWorkBuffer;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kWorkBufferCID.GetID(), iWorkBuffer::kIID.GetID(), pWorkBuffer.AsVoidPP())));

		for (auto threads = 1; threads < pScheduler->GetMaxThreads(); ++threads)
		{
			testData->HitCount = 0;
			pScheduler->SetActiveThreads(threads);

			for (auto i = 0; i < loopCount*threads; ++i)
			{
				pWorkBuffer->FirstOne(
					[](const WorkContext*, void* context)
				{
					CPF_ASSERT(reinterpret_cast<TestData*>(context)->HitCount < 0x70000000);
					Atomic::Inc(reinterpret_cast<TestData*>(context)->HitCount);
					auto accumulator = 0;
					for (auto i = 0; i < innerLoopCount; ++i)
						accumulator += i;
				},
					testData);
			}
			// Creates a fence.
			pWorkBuffer->LastOneBarrier(
				[](const WorkContext*, void* context)
			{
				auto& sem = reinterpret_cast<TestData*>(context)->Complete;
				sem.Release();
			},
				testData);

			pScheduler->Execute(pWorkBuffer);
			testData->Complete.Acquire();
			EXPECT_EQ(loopCount*threads, CPF::Atomic::Load(testData->HitCount));
		}
		for (auto threads = pScheduler->GetMaxThreads(); threads > 0; --threads)
		{
			testData->HitCount = 0;
			pScheduler->SetActiveThreads(threads);

			for (auto i = 0; i < loopCount*threads; ++i)
			{
				pWorkBuffer->FirstOne(
					[](const WorkContext*, void* context)
				{
					CPF_ASSERT(reinterpret_cast<TestData*>(context)->HitCount < 0x70000000);
					Atomic::Inc(reinterpret_cast<TestData*>(context)->HitCount);
					auto accumulator = 0;
					for (auto i = 0; i < innerLoopCount; ++i)
						accumulator += i;
				},
					testData);
			}
			// Creates a fence.
			pWorkBuffer->LastOneBarrier(
				[](const WorkContext*, void* context)
			{
				auto& sem = reinterpret_cast<TestData*>(context)->Complete;
				sem.Release();
			},
				testData);

			pScheduler->Execute(pWorkBuffer);
			testData->Complete.Acquire();
			EXPECT_EQ(loopCount*threads, Atomic::Load(testData->HitCount));
		}

		for (auto threads = 0; threads < 50; ++threads)
		{
			auto threadCount = int((rand() / float(RAND_MAX)) * (pScheduler->GetMaxThreads() - 1) + 1.49999f);
			threadCount = threadCount <= 0 ? 1 : threadCount > pScheduler->GetMaxThreads() ? pScheduler->GetMaxThreads() : threadCount;

			testData->HitCount = 0;
			pScheduler->SetActiveThreads(threadCount);

			for (auto i = 0; i < loopCount*threadCount; ++i)
			{
				pWorkBuffer->FirstOne(
					[](const WorkContext*, void* context)
				{
					CPF_ASSERT(reinterpret_cast<TestData*>(context)->HitCount < 0x70000000);
					Atomic::Inc(reinterpret_cast<TestData*>(context)->HitCount);
					auto accumulator = 0;
					for (auto i = 0; i < innerLoopCount; ++i)
						accumulator += i;
				},
					testData);
			}
			// Creates a fence.
			pWorkBuffer->LastOneBarrier(
				[](const WorkContext*, void* context)
			{
				auto& sem = reinterpret_cast<TestData*>(context)->Complete;
				sem.Release();
			},
				testData);

			pScheduler->Execute(pWorkBuffer);
			testData->Complete.Acquire();
			EXPECT_EQ(loopCount*threadCount, CPF::Atomic::Load(testData->HitCount));
		}

		pScheduler->Shutdown();
		delete testData;
	}
}
