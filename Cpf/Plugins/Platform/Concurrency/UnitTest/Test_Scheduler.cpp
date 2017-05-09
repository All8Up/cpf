//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "gmock/gmock.h"
#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Concurrency/iFence.hpp"
#include "Threading/Thread.hpp"
#include "Atomic/Atomic.hpp"


TEST_F(ConcurrencyTest, Basics)
{
	using namespace Cpf;
	using namespace Concurrency;

	for (auto iterations = 0; iterations < 20; ++iterations)
	{
		IntrusivePtr<iScheduler> pScheduler;
		EXPECT_TRUE(COM::Succeeded(GetRegistry()->Create(nullptr, kSchedulerCID, iScheduler::kIID, pScheduler.AsVoidPP())));
		EXPECT_TRUE(COM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

		IntrusivePtr<iFence> pFence;
		EXPECT_TRUE(COM::Succeeded(GetRegistry()->Create(nullptr, kFenceCID, iFence::kIID, pFence.AsVoidPP())));

		IntrusivePtr<iWorkBuffer> pWorkBuffer;
		EXPECT_TRUE(COM::Succeeded(GetRegistry()->Create(nullptr, kWorkBufferCID, iWorkBuffer::kIID, pWorkBuffer.AsVoidPP())));

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
			pScheduler->Submit(pFence);
			pFence->Wait();
			for (auto i = 0; i < loopCount; ++i)
				EXPECT_EQ(1, valid[i]);
		}
		pScheduler->Shutdown();
	}
}
