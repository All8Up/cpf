//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iFence.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Threading/Thread.hpp"
#include "Atomic/Atomic.hpp"

TEST_F(ConcurrencyTest, First_Opcode)
{
	using namespace Cpf;
	using namespace Concurrency;

	for (auto i = 0; i < 10; ++i)
	{
		IntrusivePtr<iScheduler> pScheduler;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kSchedulerCID, iScheduler::kIID, pScheduler.AsVoidPP())));
		EXPECT_TRUE(GOM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

		IntrusivePtr<iFence> pFence;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kFenceCID, iFence::kIID, pFence.AsVoidPP())));

		IntrusivePtr<iWorkBuffer> pWorkBuffer;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kWorkBufferCID, iWorkBuffer::kIID, pWorkBuffer.AsVoidPP())));

		{
			auto firstThreadArrived = 0;
			pWorkBuffer->FirstOne([](const WorkContext*, void* context) {
				// Signal that we have arrived.
				Atomic::Store(*reinterpret_cast<int*>(context), 1);

				// Wait a sec, just to make sure the next instruction executes before we wake.
				Threading::Thread::Sleep(Time::Seconds(0.1f));
			},
			&firstThreadArrived);
			pWorkBuffer->FirstOne([](const WorkContext*, void* context) {
				// Some thread should arrive that is not the above thread.
				for (; Atomic::Load(*reinterpret_cast<int*>(context)) != 1;)
					;
			},
			&firstThreadArrived);

			// Wait for completion.
			pScheduler->Execute(pWorkBuffer);
			pScheduler->Submit(pFence);
			pFence->Wait();
			EXPECT_EQ(1, firstThreadArrived);
		}
		pScheduler->Shutdown();
		pScheduler.Adopt(nullptr);
	}
}
