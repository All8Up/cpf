//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Threading/Thread.hpp"
#include "Atomic/Atomic.hpp"
#include "Threading.hpp"


TEST(Threading, Thread_Run)
{
	volatile bool testRan = false;
	CPF::Threading::Thread testThread([&]() {
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

	CPF::Time::Value startTime = CPF::Time::Value::Now();
	CPF::Threading::Thread::Sleep(CPF::Time::Ms(aproxDurationMs));
	CPF::Time::Value endTime = CPF::Time::Value::Now();
	int64_t deltaMs = int64_t(CPF::Time::Ms(endTime-startTime))-aproxDurationMs;

	EXPECT_LT(std::abs(deltaMs), tollerance);
}


TEST(Threading, Thread_Group)
{
	using namespace CPF::Threading;

	Thread::Group testGroup(10);
	int testValue = 0;
	testGroup(std::move(std::bind([](int* test) {
		CPF::Atomic::Inc(*test);}, &testValue)));
	testGroup.Join();
	EXPECT_EQ(10, testValue);
}
