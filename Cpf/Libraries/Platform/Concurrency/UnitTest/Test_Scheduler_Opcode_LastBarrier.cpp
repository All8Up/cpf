//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Opcodes.hpp"


TEST(Concurrency, LastFenced_Opcode)
{
	using namespace Cpf;
	using namespace Concurrency;

	for (auto i = 0; i < 100; ++i)
	{
		Scheduler* scheduler = new Scheduler(nullptr);
		scheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr);
		EXPECT_TRUE(scheduler->GetAvailableThreads() >= 4);
		Semaphore sync;
		scheduler->SetActiveThreads(4);
		{
			auto hitCount = 0;

			Queue queue;
			queue.All([](const WorkContext*, void* context) {
				// Increment the counter.
				Atomic::Inc(*reinterpret_cast<int*>(context));
			},
			&hitCount);

			queue.LastOneBarrier([](const WorkContext*, void* context) {
				// All threads should have executed the counter by the time we get here
				// and none should have gotten to the next instruction.
				EXPECT_EQ(4, Cpf::Atomic::Load(*reinterpret_cast<int*>(context)));
			},
			&hitCount);

			queue.All([](const WorkContext*, void* context) {
				// Increment the counter.
				Atomic::Inc(*reinterpret_cast<int*>(context));
			},
			&hitCount);

			// Wait for completion.
			scheduler->Execute(queue);
			scheduler->Submit(&sync);
			sync.Acquire();
			EXPECT_EQ(8, hitCount);
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}
