//////////////////////////////////////////////////////////////////////////
#include "Configuration/Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/Scheduler.hpp"


TEST(Concurrency, Set_SharedDataRegister)
{
	using namespace Cpf;
	using namespace Concurrency;
	ScopedInitializer<Platform::TimeInitializer> timeInit;

	Platform::Threading::Thread::Group threads(Platform::Threading::Thread::GetHardwareThreadCount());
	Scheduler* scheduler = new Scheduler;
	scheduler->Initialize(std::move(threads));
	{
		Scheduler::Queue queue = scheduler->CreateQueue();

		for (intptr_t i = 0; i < Scheduler::kRegisterCount; ++i)
			queue.SD(int(i), int32_t(i));

		for (intptr_t i = 0; i < Scheduler::kRegisterCount; ++i)
			queue.FirstOne([](Scheduler::ThreadContext& threadContext, void* context) {
			int ival(int((intptr_t)context));
			EXPECT_EQ(ival, threadContext.SD(ival));
		}, (void*)intptr_t(i));

		queue.BlockingSubmit();
	}
}
