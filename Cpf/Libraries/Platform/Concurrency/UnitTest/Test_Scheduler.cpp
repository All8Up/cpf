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

	for (auto iterations = 0; iterations < 20; ++iterations)
	{
		Scheduler* scheduler = new Scheduler(nullptr);

		scheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr);
		Semaphore sync;
		{
			static const auto loopCount = 25000;
			int valid[loopCount] = { 0 };

			Queue queue;

			for (auto i = 0; i < loopCount; ++i)
			{
				queue.FirstOne(
					[](const WorkContext*, void* context)
				{
					auto *target = reinterpret_cast<int*>(context);
					*target += 1;
				},
					&valid[i]);
			}

			// Wait for completion.
			scheduler->Execute(queue);
			scheduler->Submit(&sync);
			sync.Acquire();
			for (auto i = 0; i < loopCount; ++i)
				EXPECT_EQ(1, valid[i]);
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}
