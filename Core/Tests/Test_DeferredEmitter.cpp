#include <gtest/gtest.h>
#include "CPF/Event/Emitter.hpp"
#include "CPF/Std/Functional.hpp"

namespace TestDeferred
{
	struct Test : CPF::Events::DeferredEmitter
	{
		typedef CPF::Events::Event< 0, CPF::STD::Function< void() > > Test0;
	};
}


TEST(Events, DeferredSingleVoidPost)
{
	TestDeferred::Test test;
	int32_t test0 = 0;

	CPF::Events::Handle event0(test.On<TestDeferred::Test::Test0>([&]() {
		++test0;
	}));
	test.Post<TestDeferred::Test::Test0>();

	EXPECT_EQ(0, test0);
	test();
	EXPECT_EQ(1, test0);
}


TEST(Events, DeferredSingleVoidEmit)
{
	TestDeferred::Test test;
	int32_t test0 = 0;
	int32_t test1 = 0;

	CPF::Events::Handle event0(test.On<TestDeferred::Test::Test0>([&]() {
		++test0;
	}));
	test.Emit<TestDeferred::Test::Test0>([&]() {++test1;});

	EXPECT_EQ(0, test0);
	EXPECT_EQ(0, test1);
	test();
	EXPECT_EQ(1, test0);
	EXPECT_EQ(1, test1);
}
