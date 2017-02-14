//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Opcodes.hpp"
#include "Atomic/Atomic.hpp"


TEST(Concurrency, Basics)
{
	using namespace Cpf;
	using namespace Concurrency;
	ScopedInitializer<Platform::TimeInitializer> timeInit;

	for (auto iterations = 0; iterations < 20; ++iterations)
	{
		Platform::Threading::Thread::Group threads(Platform::Threading::Thread::GetHardwareThreadCount());
		Scheduler* scheduler = new Scheduler;

		scheduler->Initialize(Move(threads));
		Scheduler::Semaphore sync;
		{
			static const auto loopCount = 25000;
			int valid[loopCount] = { 0 };

			Scheduler::Queue queue = scheduler->CreateQueue();

			for (auto i = 0; i < loopCount; ++i)
			{
				queue.FirstOne(
					[](Scheduler::ThreadContext&, void* context)
				{
					auto *target = reinterpret_cast<int*>(context);
					*target += 1;
				},
					&valid[i]);
			}

			// Wait for completion.
			queue.Submit(sync);
			queue.Execute();
			sync.Acquire();
			for (auto i = 0; i < loopCount; ++i)
				EXPECT_EQ(1, valid[i]);
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}
