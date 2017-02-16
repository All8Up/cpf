//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Team.hpp"
#include "Threading/Thread.hpp"
#include "gmock/gmock.h"


TEST(Concurrency, Team_SetupTeardown)
{
	using namespace Cpf::Concurrency;

	struct TotalContext
	{
		int testValue;
	} totalContext {1234};
	struct TestData
	{};

	Scheduler scheduler;
	scheduler.Initialize(
		std::move(Cpf::Platform::Threading::Thread::Group(1)),
		[](Scheduler::ThreadContext& threadContext, void* context)
		{
			EXPECT_EQ(1234, ((TotalContext*)context)->testValue);
			threadContext.SetUserData(new TestData);
		},
		[](Scheduler::ThreadContext& threadContext, void* context)
		{
			EXPECT_EQ(1234, ((TotalContext*)context)->testValue);
			delete (TestData*)threadContext.GetUserData();
		},
		&totalContext
	);
	{
		//////////////////////////////////////////////////////////////////////////
		Team team(scheduler);
	}
	scheduler.Shutdown();
}
