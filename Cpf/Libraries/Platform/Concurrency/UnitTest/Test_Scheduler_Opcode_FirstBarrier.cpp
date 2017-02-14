//////////////////////////////////////////////////////////////////////////
#include "Configuration/Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Opcodes.hpp"
#include "Atomic/Atomic.hpp"


TEST(Concurrency, FirstFenced_Opcode)
{
	using namespace Cpf;
	using namespace Concurrency;
	ScopedInitializer<Platform::TimeInitializer> timeInit;

	for (auto i = 0; i < 10; ++i)
	{
		Scheduler* scheduler = new Scheduler;
		Platform::Threading::Thread::Group threads(Platform::Threading::Thread::GetHardwareThreadCount());
		scheduler->Initialize(std::move(threads));
		{
			auto firstThreadArrived = 0;
			Scheduler::Queue queue = scheduler->CreateQueue();
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

			// Wait for completion.
			queue.BlockingSubmit();
			EXPECT_EQ(1, firstThreadArrived);
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}