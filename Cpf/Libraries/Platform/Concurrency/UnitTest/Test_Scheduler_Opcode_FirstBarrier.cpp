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
	ScopedInitializer<TimeInitializer> timeInit;

	for (auto i = 0; i < 10; ++i)
	{
		Scheduler* scheduler = new Scheduler;
		Scheduler::Semaphore sync;
		Threading::Thread::Group threads(Threading::Thread::GetHardwareThreadCount());
		scheduler->Initialize(std::move(threads));
		{
			auto firstThreadArrived = 0;
			Scheduler::Queue queue;
			queue.FirstOneBarrier([](Scheduler::ThreadContext&, void* context)
			{
				Atomic::Store(*reinterpret_cast<int*>(context), 1);
			},
				&firstThreadArrived);

			queue.AllBarrier([](Scheduler::ThreadContext&, void* context)
			{
				EXPECT_EQ(1, Atomic::Load(*reinterpret_cast<int*>(context)));
			},
				&firstThreadArrived);

			scheduler->Execute(queue);

			// Wait for completion.
			scheduler->Submit(sync);
			sync.Acquire();

			EXPECT_EQ(1, firstThreadArrived);
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}
