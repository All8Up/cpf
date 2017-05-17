//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "Concurrency/iFence.hpp"
#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Atomic/Atomic.hpp"
#include "Threading/Thread.hpp"

TEST_F(ConcurrencyTest, FirstFenced_Opcode)
{
	using namespace Cpf;
	using namespace Concurrency;

	for (auto i = 0; i < 10; ++i)
	{
		//////////////////////////////////////////////////////////////////////////
		IntrusivePtr<iScheduler> pScheduler;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kSchedulerCID, iScheduler::kIID, pScheduler.AsVoidPP())));
		EXPECT_TRUE(GOM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

		IntrusivePtr<iFence> pFence;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kFenceCID, iFence::kIID, pFence.AsVoidPP())));

		IntrusivePtr<iWorkBuffer> pWorkBuffer;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kWorkBufferCID, iWorkBuffer::kIID, pWorkBuffer.AsVoidPP())));

		{
			auto firstThreadArrived = 0;
			pWorkBuffer->FirstOneBarrier([](const WorkContext*, void* context)
			{
				Atomic::Store(*reinterpret_cast<int*>(context), 1);
			},
				&firstThreadArrived);

			pWorkBuffer->AllBarrier([](const WorkContext*, void* context)
			{
				EXPECT_EQ(1, Atomic::Load(*reinterpret_cast<int*>(context)));
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
