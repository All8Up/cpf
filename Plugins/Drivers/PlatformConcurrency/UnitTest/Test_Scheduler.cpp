//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "gtest/gtest.h"
#include "CPF/Platform/Concurrency/iScheduler.hpp"
#include "CPF/Platform/Concurrency/iWorkBuffer.hpp"
#include "CPF/Platform/Concurrency/iFence.hpp"
#include "CPF/Threading/Thread.hpp"

bool ConcurrencyTest::mLoggingInitialized = false;

TEST_F(ConcurrencyTest, Basics)
{
	using namespace CPF;
	using namespace Platform;

	for (auto iterations = 0; iterations < 20; ++iterations)
	{
		IntrusivePtr<iScheduler> pScheduler;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iScheduler::kCID, iScheduler::kIID, pScheduler.AsVoidPP())));
		EXPECT_TRUE(GOM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

		IntrusivePtr<iFence> pFence;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iFence::kCID, iFence::kIID, pFence.AsVoidPP())));

		IntrusivePtr<iWorkBuffer> pWorkBuffer;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iWorkBuffer::kCID, iWorkBuffer::kIID, pWorkBuffer.AsVoidPP())));

		{
			static const auto loopCount = 25000;
			int valid[loopCount] = { 0 };

			for (auto i = 0; i < loopCount; ++i)
			{
				pWorkBuffer->FirstOne(
					[](const WorkContext*, void* context)
				{
					auto *target = reinterpret_cast<int*>(context);
					*target += 1;
				},
					&valid[i]);
			}

			// Wait for completion.
			pScheduler->Execute(pWorkBuffer);
			pWorkBuffer->Reset();
			pScheduler->Submit(pFence);
			pFence->Wait();
			for (auto i = 0; i < loopCount; ++i)
				EXPECT_EQ(1, valid[i]);
		}
		pScheduler->Shutdown();
	}
}
