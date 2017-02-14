//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Opcodes.hpp"
#include "Atomic/Atomic.hpp"


TEST(Concurrency, All_Opcode)
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Cpf;
	using namespace Concurrency;

	ScopedInitializer<Platform::TimeInitializer> timeInit;

	//////////////////////////////////////////////////////////////////////////
	auto scheduler = new Scheduler;
	EXPECT_TRUE(scheduler != nullptr);
	if (scheduler)
	{
		//////////////////////////////////////////////////////////////////////////
		Platform::Threading::Thread::Group threads(Platform::Threading::Thread::GetHardwareThreadCount());
		EXPECT_TRUE(scheduler->Initialize(std::move(threads)));
		EXPECT_TRUE(scheduler->ThreadCount() >= 4);

		Scheduler::Queue queue = scheduler->CreateQueue();
		scheduler->CreateQueue().ActiveThreads(4).Submit();
		{
			//////////////////////////////////////////////////////////////////////////
			int hitCount = 0;
			for (int i=0; i<25; ++i)
			{
				queue.All( [](Scheduler::ThreadContext&, void* context)
				{
					Atomic::Inc(*reinterpret_cast<int*>(context));
				},
					&hitCount);
			}
			queue.BlockingSubmit();
			EXPECT_EQ(4 * 25, hitCount);
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}
