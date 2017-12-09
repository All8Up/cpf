//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "Concurrency/iFence.hpp"
#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Threading/Thread.hpp"
#include <atomic>

TEST_F(ConcurrencyTest, FirstFenced_Opcode)
{
	using namespace CPF;
	using namespace Concurrency;

	for (auto i = 0; i < 10; ++i)
	{
		//////////////////////////////////////////////////////////////////////////
		IntrusivePtr<iScheduler> pScheduler;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kSchedulerCID.GetID(), iScheduler::kIID.GetID(), pScheduler.AsVoidPP())));
		EXPECT_TRUE(GOM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

		IntrusivePtr<iFence> pFence;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kFenceCID.GetID(), iFence::kIID.GetID(), pFence.AsVoidPP())));

		IntrusivePtr<iWorkBuffer> pWorkBuffer;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kWorkBufferCID.GetID(), iWorkBuffer::kIID.GetID(), pWorkBuffer.AsVoidPP())));

		{
			std::atomic<int> firstThreadArrived = 0;
			pWorkBuffer->FirstOneBarrier([](const WorkContext*, void* context)
			{
				(*reinterpret_cast<std::atomic<int>*>(context)).store(1);
			},
				&firstThreadArrived);

			pWorkBuffer->AllBarrier([](const WorkContext*, void* context)
			{
				EXPECT_EQ(1, (*reinterpret_cast<std::atomic<int>*>(context)).load());
			},
				&firstThreadArrived);

			pScheduler->Execute(pWorkBuffer);

			// Wait for completion.
			pScheduler->Submit(pFence);
			pFence->Wait();

			EXPECT_EQ(1, firstThreadArrived);
		}
		pScheduler->Shutdown();
	}
}
