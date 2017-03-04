//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Threading/Thread.hpp"
#include "Atomic/Atomic.hpp"
#include "Threading.hpp"


TEST(Threading, Thread_Run)
{
	Cpf::ScopedInitializer<Cpf::ThreadingInitializer> threadingInit;

	volatile bool testRan = false;
	Cpf::Threading::Thread testThread([&]() {
		testRan = true;
	});
	testThread.Join();
	EXPECT_TRUE(testRan);
}


TEST(Threading, Thread_Sleep)
{
	// Unfortunately this is not perfectly deterministic, odd things can happen in
	// the os and prevent the thread from joining within the tolerance and cause this
	// to fail.  I wish there were a better more guaranteed solution but there doesn't
	// seem to be one.
	const int64_t aproxDurationMs = 2000;
	const int64_t tollerance = 200;

	Cpf::ScopedInitializer<Cpf::ThreadingInitializer> threadingInit;

	Cpf::Platform::Time::Value startTime = Cpf::Platform::Time::Value::Now();
	Cpf::Threading::Thread::Sleep(Cpf::Platform::Time::Ms(aproxDurationMs));
	Cpf::Platform::Time::Value endTime = Cpf::Platform::Time::Value::Now();
	int64_t deltaMs = int64_t(Cpf::Platform::Time::Ms(endTime-startTime))-aproxDurationMs;

	EXPECT_LT(std::abs(deltaMs), tollerance);
}


TEST(Threading, Thread_Group)
{
	using namespace Cpf::Threading;
	Cpf::ScopedInitializer<Cpf::ThreadingInitializer> threadingInit;

	Thread::Group testGroup(10);
	int testValue = 0;
	testGroup(std::move(std::bind([](int* test) {
		Cpf::Atomic::Inc(*test);}, &testValue)));
	testGroup.Join();
	EXPECT_EQ(10, testValue);
}
