//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Threading/Mutex.hpp"
#include "Threading/ConditionVariable.hpp"


// NOTE: you can't really test mutex by itself, it needs helpers.
// For the purposes here we use a condition variable to tell the main
// thread when the worker has begun execution.  By side effect, we
// end up testing the mutex as intended.

class Threading_Mutex : public ::testing::Test
{
public:
	virtual void SetUp() override
	{}
	virtual void TearDown() override
	{}

	void TestAcquireRelease()
	{
		mHasRun = true;
		mCondition.Release();
	}

	bool mHasRun = false;
	CPF::Threading::Mutex mMutex;
	CPF::Threading::ConditionVariable mCondition;
};


TEST_F(Threading_Mutex, Mutex_Create)
{
	CPF::Threading::Mutex testMutex;
	testMutex.Acquire();
	testMutex.Release();
}


TEST_F(Threading_Mutex, AcquireRelease)
{
	CPF::Threading::Thread testThread(std::bind(&Threading_Mutex::TestAcquireRelease, this));
	mCondition.Acquire(mMutex, [this]{return mHasRun;});
	EXPECT_TRUE(mHasRun);
	mMutex.Release();
	testThread.Join();
}
