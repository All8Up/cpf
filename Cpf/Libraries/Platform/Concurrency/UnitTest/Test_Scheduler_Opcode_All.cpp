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

	//////////////////////////////////////////////////////////////////////////
	auto scheduler = new Scheduler(nullptr);
	EXPECT_TRUE(scheduler != nullptr);
	if (scheduler)
	{
		//////////////////////////////////////////////////////////////////////////
		EXPECT_TRUE(COM::Succeeded(scheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));
		EXPECT_TRUE(scheduler->GetAvailableThreads() >= 4);

		Queue queue;
		Semaphore sync;
		scheduler->SetActiveThreads(4);
		{
			//////////////////////////////////////////////////////////////////////////
			int hitCount = 0;
			for (int i=0; i<25; ++i)
			{
				queue.All( [](const WorkContext*, void* context)
				{
					Atomic::Inc(*reinterpret_cast<int*>(context));
				},
					&hitCount);
			}
			scheduler->Execute(queue);
			scheduler->Submit(&sync);
			sync.Acquire();
			EXPECT_EQ(4 * 25, hitCount);
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}
