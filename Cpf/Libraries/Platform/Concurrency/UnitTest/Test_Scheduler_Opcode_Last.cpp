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
	ScopedInitializer<Platform::TimeInitializer> timeInit;

	for (auto i = 0; i < 100; ++i)
	{
		Platform::Threading::Thread::Group threads(Platform::Threading::Thread::GetHardwareThreadCount());
		Scheduler* scheduler = new Scheduler;
		scheduler->Initialize(std::move(threads));
		{
			Scheduler::Queue queue = scheduler->CreateQueue();

			auto firstThreadArrived = 0;
			queue.LastOne(
				[](Scheduler::ThreadContext&, void* context)
			{
				// The next instruction should execute and the flag should be set.
				for (; Atomic::Load(*reinterpret_cast<int*>(context)) != 1;)
					;
			},
				&firstThreadArrived);

			queue.FirstOne(
				[](Scheduler::ThreadContext&, void* context)
			{
				// Signal that we have arrived.
				Atomic::Store(*reinterpret_cast<int*>(context), 1);
			},
				&firstThreadArrived);

			// Wait for completion.
			queue.BlockingSubmit();
			EXPECT_EQ(1, firstThreadArrived);
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}
