//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Threading/Reactor.hpp"
#include "Threading/Thread.hpp"
#include "Move.hpp"
#include "Vector.hpp"


class TestThreadingReactor : public ::testing::Test
{
public:
	virtual void SetUp() override
	{
		mQueue.Initialize(&mReactor);
	}
	virtual void TearDown() override
	{}

	using FunctionVector = Cpf::Vector<Cpf::Function<void(void)>>;
	void DoWorker(int count, FunctionVector& funcs)
	{
		mpData = new bool[count];
		for (int i = 0; i < count; ++i)
			mpData[i] = false;

		mGroup.Initialize(count);
		for (int i = 0; i < count; ++i)
			mGroup(i, Cpf::Move(funcs[i]));
		mGroup.Join();

		for (int i = 0; i < count; ++i)
			EXPECT_TRUE(mpData[i]);

		delete mpData;
	}

	Cpf::Platform::Threading::Reactor mReactor;
	Cpf::Platform::Threading::Reactor::WorkQueue mQueue;
	Cpf::Platform::Threading::Thread::Group mGroup;
	bool* mpData;
};


TEST_F(TestThreadingReactor, MultipleReader)
{
	// Issue some threads to run the work.
	FunctionVector funcs;
	for (int i = 0; i < 4; ++i)
		funcs.push_back(std::bind([this]() { mReactor.RunOne(); }));

	// Issue some work.
	for (int i = 0; i < 4; ++i)
		mQueue(std::bind([this](int j) { mpData[j] = true; }, i));

	// Kick things off.
	DoWorker(4, funcs);

	// Queue should be empty.
	EXPECT_FALSE(mReactor.RunOne());
}


TEST_F(TestThreadingReactor, SingleReader)
{
	// Issue some threads to run the work.
	FunctionVector funcs;
	funcs.push_back(std::bind([this]() { mReactor.Run(); }));

	// Issue some work.
	for (int i = 0; i < 4; ++i)
		mQueue(std::bind([]() {
	}));
	mQueue(std::bind([this]() {
		EXPECT_FALSE(mReactor.RunOne()); mpData[0] = true; mReactor.Quit();
	}));

	// Kick things off.
	DoWorker(1, funcs);
}
