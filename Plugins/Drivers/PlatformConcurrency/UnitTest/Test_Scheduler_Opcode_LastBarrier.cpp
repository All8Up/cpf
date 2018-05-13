//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "CPF/Platform/Concurrency/iFence.hpp"
#include "CPF/Platform/Concurrency/iScheduler.hpp"
#include "CPF/Platform/Concurrency/iWorkBuffer.hpp"
#include "CPF/Threading/Thread.hpp"
#include <atomic>

TEST_F(ConcurrencyTest, LastFenced_Opcode)
{
	using namespace CPF;
	using namespace Platform;

	for (auto i = 0; i < 100; ++i)
	{
		//////////////////////////////////////////////////////////////////////////
		IntrusivePtr<iScheduler> pScheduler;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iScheduler::kCID, iScheduler::kIID, pScheduler.AsVoidPP())));
		EXPECT_TRUE(GOM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

		IntrusivePtr<iFence> pFence;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iFence::kCID, iFence::kIID, pFence.AsVoidPP())));

		IntrusivePtr<iWorkBuffer> pWorkBuffer;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iWorkBuffer::kCID, iWorkBuffer::kIID, pWorkBuffer.AsVoidPP())));

		EXPECT_TRUE(pScheduler->GetMaxThreads() >= 4);
		pScheduler->SetActiveThreads(4);
		{
			std::atomic<int> hitCount = 0;

			pWorkBuffer->All([](const WorkContext*, void* context) {
				// Increment the counter.
				(*reinterpret_cast<std::atomic<int>*>(context)).fetch_add(1);
			},
			&hitCount);

			pWorkBuffer->LastOneBarrier([](const WorkContext*, void* context) {
				// All threads should have executed the counter by the time we get here
				// and none should have gotten to the next instruction.
				EXPECT_EQ(4, (*reinterpret_cast<std::atomic<int>*>(context)).load());
			},
			&hitCount);

			pWorkBuffer->All([](const WorkContext*, void* context) {
				// Increment the counter.
				(*reinterpret_cast<std::atomic<int>*>(context)).fetch_add(1);
			},
			&hitCount);

			// Wait for completion.
			pScheduler->Execute(pWorkBuffer);
			pWorkBuffer->Reset();
			pScheduler->Submit(pFence);
			pFence->Wait();
			EXPECT_EQ(8, hitCount);
		}
		pScheduler->Shutdown();
	}
}
