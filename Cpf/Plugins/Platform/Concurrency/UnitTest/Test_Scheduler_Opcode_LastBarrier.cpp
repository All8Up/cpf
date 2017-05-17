//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "Concurrency/iFence.hpp"
#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Threading/Thread.hpp"
#include "Atomic/Atomic.hpp"

TEST_F(ConcurrencyTest, LastFenced_Opcode)
{
	using namespace Cpf;
	using namespace Concurrency;

	for (auto i = 0; i < 100; ++i)
	{
		//////////////////////////////////////////////////////////////////////////
		IntrusivePtr<iScheduler> pScheduler;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kSchedulerCID, iScheduler::kIID, pScheduler.AsVoidPP())));
		EXPECT_TRUE(GOM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

		IntrusivePtr<iFence> pFence;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kFenceCID, iFence::kIID, pFence.AsVoidPP())));

		IntrusivePtr<iWorkBuffer> pWorkBuffer;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kWorkBufferCID, iWorkBuffer::kIID, pWorkBuffer.AsVoidPP())));

		EXPECT_TRUE(pScheduler->GetMaxThreads() >= 4);
		pScheduler->SetActiveThreads(4);
		{
			auto hitCount = 0;

			pWorkBuffer->All([](const WorkContext*, void* context) {
				// Increment the counter.
				Atomic::Inc(*reinterpret_cast<int*>(context));
			},
			&hitCount);

			pWorkBuffer->LastOneBarrier([](const WorkContext*, void* context) {
				// All threads should have executed the counter by the time we get here
				// and none should have gotten to the next instruction.
				EXPECT_EQ(4, Cpf::Atomic::Load(*reinterpret_cast<int*>(context)));
			},
			&hitCount);

			pWorkBuffer->All([](const WorkContext*, void* context) {
				// Increment the counter.
				Atomic::Inc(*reinterpret_cast<int*>(context));
			},
			&hitCount);

			// Wait for completion.
			pScheduler->Execute(pWorkBuffer);
			pScheduler->Submit(pFence);
			pFence->Wait();
			EXPECT_EQ(8, hitCount);
		}
		pScheduler->Shutdown();
	}
}
