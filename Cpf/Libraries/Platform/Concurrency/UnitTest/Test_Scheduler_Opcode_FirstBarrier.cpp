//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Opcodes.hpp"
#include "Atomic/Atomic.hpp"


TEST(Concurrency, FirstFenced_Opcode)
{
	using namespace Cpf;
	using namespace Concurrency;

	for (auto i = 0; i < 10; ++i)
	{
		Scheduler* scheduler = new Scheduler(nullptr);
		Semaphore sync;
		scheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr);
		{
			auto firstThreadArrived = 0;
			Queue queue;
			queue.FirstOneBarrier([](const WorkContext*, void* context)
			{
				Atomic::Store(*reinterpret_cast<int*>(context), 1);
			},
				&firstThreadArrived);

			queue.AllBarrier([](const WorkContext*, void* context)
			{
				EXPECT_EQ(1, Atomic::Load(*reinterpret_cast<int*>(context)));
			},
				&firstThreadArrived);

			scheduler->Execute(queue);

			// Wait for completion.
			scheduler->Submit(&sync);
			sync.Acquire();

			EXPECT_EQ(1, firstThreadArrived);
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}
