//////////////////////////////////////////////////////////////////////////
#include "CPF/Configuration.hpp"
#include "gtest/gtest.h"
#include "CPF/Platform/Concurrency/iScheduler.hpp"

#if 0
TEST(Concurrency, Set_SharedDataRegister)
{
	using namespace CPF;
	using namespace Concurrency;
	ScopedInitializer<Platform::TimeInitializer> timeInit;

	Threading::Thread::Group threads(Threading::Thread::GetHardwareThreadCount());
	Scheduler* scheduler = new Scheduler;
	scheduler->Initialize(std::move(threads));
	Scheduler::Semaphore sync;
	{
		Scheduler::Queue queue = scheduler->CreateQueue();

		for (intptr_t i = 0; i < Scheduler::kRegisterCount; ++i)
			queue.SD(int(i), int32_t(i));

		for (intptr_t i = 0; i < Scheduler::kRegisterCount; ++i)
			queue.FirstOne([](Scheduler::ThreadContext& threadContext, void* context) {
			int ival(int((intptr_t)context));
			EXPECT_EQ(ival, threadContext.SD(ival));
		}, (void*)intptr_t(i));

		queue.Submit(sync);
		queue.Execute();
		sync.Acquire();
	}
}
#endif
