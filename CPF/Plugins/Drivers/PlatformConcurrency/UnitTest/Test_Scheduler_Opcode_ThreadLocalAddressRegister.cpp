//////////////////////////////////////////////////////////////////////////
#include "CPF/Configuration.hpp"
#include "gtest/gtest.h"
#include "CPF/Platform/Concurrency/iScheduler.hpp"

#if 0
TEST(Concurrency, Set_ThreadLocalAddressRegister)
{
	using namespace CPF;
	using namespace Concurrency;
	ScopedInitializer<Platform::TimeInitializer> timeInit;

	Threading::Thread::Group threads(Threading::Thread::GetHardwareThreadCount());
	Scheduler* scheduler = new Scheduler;
	Scheduler::Semaphore sync;
	scheduler->Initialize(std::move(threads));
	{
		Scheduler::Queue queue;

		for (intptr_t i = 0; i < Scheduler::kRegisterCount; ++i)
			queue.TLA(int(i), (void*)i);

		for (intptr_t i=0; i<Scheduler::kRegisterCount; ++i)
			queue.FirstOne([](Scheduler::ThreadContext& threadContext, void* context) {
			int ival(int((intptr_t)context));
			EXPECT_EQ(context, threadContext.TLA(ival));
		}, (void*)i);

		queue.Submit(sync);
		queue.Execute();
		sync.Acquire();
	}
}
#endif
