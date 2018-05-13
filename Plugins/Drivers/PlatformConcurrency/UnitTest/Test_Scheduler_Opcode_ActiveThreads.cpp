//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "gtest/gtest.h"
#include "CPF/Platform/Concurrency/iScheduler.hpp"
#include "CPF/Platform/Concurrency/iWorkBuffer.hpp"
#include "CPF/Platform/Concurrency/iFence.hpp"
#include "CPF/Threading/Thread.hpp"
#include "CPF/Threading/Semaphore.hpp"
#include <atomic>

namespace ConcurrencyTestData
{
	struct CPF_ALIGN(16) TestData
	{
		std::atomic <int32_t> HitCount;
		CPF::Threading::Semaphore Complete;
	};
}


TEST_F(ConcurrencyTest, ActiveChange)
{
	using namespace CPF;
	using namespace Platform;
	using namespace ConcurrencyTestData;

	srand(int(Time::Value::Now().GetTicks()));

	static const auto loopCount = 1000;
	static const auto innerLoopCount = 1000;

	{
		TestData* testData = new TestData;

		IntrusivePtr<iScheduler> pScheduler;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iScheduler::kCID, iScheduler::kIID, pScheduler.AsVoidPP())));
		EXPECT_TRUE(GOM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

		IntrusivePtr<iFence> pFence;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iFence::kCID, iFence::kIID, pFence.AsVoidPP())));

		IntrusivePtr<iWorkBuffer> pWorkBuffer;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iWorkBuffer::kCID, iWorkBuffer::kIID, pWorkBuffer.AsVoidPP())));

		for (auto threads = 1; threads < pScheduler->GetMaxThreads(); ++threads)
		{
			testData->HitCount.store(0);
			pScheduler->SetActiveThreads(threads);

			for (auto i = 0; i < loopCount*threads; ++i)
			{
				pWorkBuffer->FirstOne(
					[](const WorkContext*, void* context)
				{
					CPF_ASSERT(reinterpret_cast<TestData*>(context)->HitCount < 0x70000000);
					(reinterpret_cast<TestData*>(context)->HitCount).fetch_add(1);
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
			pWorkBuffer->Reset();
			testData->Complete.Acquire();
			EXPECT_EQ(loopCount*threads, testData->HitCount.load());
		}
		for (auto threads = pScheduler->GetMaxThreads(); threads > 0; --threads)
		{
			testData->HitCount.store(0);
			pScheduler->SetActiveThreads(threads);

			for (auto i = 0; i < loopCount*threads; ++i)
			{
				pWorkBuffer->FirstOne(
					[](const WorkContext*, void* context)
				{
					CPF_ASSERT(reinterpret_cast<TestData*>(context)->HitCount < 0x70000000);
					(reinterpret_cast<TestData*>(context)->HitCount).fetch_add(1);
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
			pWorkBuffer->Reset();
			testData->Complete.Acquire();
			EXPECT_EQ(loopCount*threads, testData->HitCount.load());
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
					(reinterpret_cast<TestData*>(context)->HitCount).fetch_add(1);
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
			pWorkBuffer->Reset();
			testData->Complete.Acquire();
			EXPECT_EQ(loopCount*threadCount, testData->HitCount.load());
		}

		pScheduler->Shutdown();
		delete testData;
	}
}
