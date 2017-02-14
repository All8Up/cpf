//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/Scheduler.hpp"


TEST(Concurrency, Set_ThreadLocalDataRegister)
{
	using namespace Cpf;
	using namespace Concurrency;
	ScopedInitializer<Platform::TimeInitializer> timeInit;

	Platform::Threading::Thread::Group threads(Platform::Threading::Thread::GetHardwareThreadCount());
	Scheduler* scheduler = new Scheduler;
	scheduler->Initialize(std::move(threads));
	{
		Scheduler::Queue queue = scheduler->CreateQueue();

		for (int i = 0; i < Scheduler::kRegisterCount; ++i)
			queue.TLD(i, i);

		for (int i=0; i<Scheduler::kRegisterCount; ++i)
			queue.FirstOne([](Scheduler::ThreadContext& threadContext, void* context) {
			int ival(int((intptr_t)context));
			EXPECT_EQ(ival, threadContext.TLD(ival));
		}, (void*)intptr_t(i));

		queue.BlockingSubmit();
	}
}
