//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Opcodes.hpp"
#include "Atomic/Atomic.hpp"


TEST(Concurrency, First_Opcode)
{
	using namespace Cpf;
	using namespace Concurrency;
	ScopedInitializer<Platform::TimeInitializer> init;

	for (auto i = 0; i < 10; ++i)
	{
		Threading::Thread::Group threads(Threading::Thread::GetHardwareThreadCount());
		Scheduler* scheduler = new Scheduler;
		scheduler->Initialize(std::move(threads));
		Scheduler::Semaphore sync;
		{
			Scheduler::Queue queue;

			auto firstThreadArrived = 0;
			queue.FirstOne(
				[](Scheduler::ThreadContext&, void* context)
			{
				// Signal that we have arrived.
				Atomic::Store(*reinterpret_cast<int*>(context), 1);

				// Wait a sec, just to make sure the next instruction executes before we wake.
				Threading::Thread::Sleep(Platform::Time::Seconds(0.1f));
			},
				&firstThreadArrived);
			queue.FirstOne(
				[](Scheduler::ThreadContext&, void* context)
			{
				// Some thread should arrive that is not the above thread.
				for (; Atomic::Load(*reinterpret_cast<int*>(context)) != 1;)
					;
			},
				&firstThreadArrived);

			// Wait for completion.
			scheduler->Execute(queue);
			scheduler->Submit(sync);
			sync.Acquire();
			EXPECT_EQ(1, firstThreadArrived);
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}
