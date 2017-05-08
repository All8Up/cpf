//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Opcodes.hpp"
#include "Atomic/Atomic.hpp"


TEST(Concurrency, Last_Opcode)
{
	using namespace Cpf;
	using namespace Concurrency;

	for (auto i = 0; i < 100; ++i)
	{
		Scheduler* scheduler = new Scheduler(nullptr);
		scheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr);
		Semaphore sync;
		{
			Queue queue;

			auto firstThreadArrived = 0;
			queue.LastOne(
				[](const WorkContext*, void* context)
			{
				// The next instruction should execute and the flag should be set.
				for (; Atomic::Load(*reinterpret_cast<int*>(context)) != 1;)
					;
			},
				&firstThreadArrived);

			queue.FirstOne(
				[](const WorkContext*, void* context)
			{
				// Signal that we have arrived.
				Atomic::Store(*reinterpret_cast<int*>(context), 1);
			},
				&firstThreadArrived);

			// Wait for completion.
			scheduler->Execute(queue);
			scheduler->Submit(&sync);
			sync.Acquire();
			EXPECT_EQ(1, firstThreadArrived);
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}
