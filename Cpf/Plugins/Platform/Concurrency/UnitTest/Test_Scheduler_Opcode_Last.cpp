//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "Concurrency/iFence.hpp"
#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Atomic/Atomic.hpp"
#include "Threading/Thread.hpp"

TEST_F(ConcurrencyTest, Last_Opcode)
{
	using namespace CPF;
	using namespace Concurrency;

	for (auto i = 0; i < 100; ++i)
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
			auto firstThreadArrived = 0;
			pWorkBuffer->LastOne(
				[](const WorkContext*, void* context)
			{
				// The next instruction should execute and the flag should be set.
				for (; Atomic::Load(*reinterpret_cast<int*>(context)) != 1;)
					;
			},
				&firstThreadArrived);

			pWorkBuffer->FirstOne(
				[](const WorkContext*, void* context)
			{
				// Signal that we have arrived.
				Atomic::Store(*reinterpret_cast<int*>(context), 1);
			},
				&firstThreadArrived);

			// Wait for completion.
			pScheduler->Execute(pWorkBuffer);
			pScheduler->Submit(pFence);
			pFence->Wait();
			EXPECT_EQ(1, firstThreadArrived);
		}
		pScheduler->Shutdown();
	}
}
