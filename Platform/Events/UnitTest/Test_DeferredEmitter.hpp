//////////////////////////////////////////////////////////////////////////
#include "Events/Emitter.hpp"
#include "Functional.hpp"
/// @cond


namespace TestDeferred
{
	struct Test : public Cpf::Platform::Events::DeferredEmitter
	{
		typedef Cpf::Platform::Events::Event< 0, Cpf::Function< void(void) > > Test0;
	};
}


TEST(Events, DeferredSingleVoidPost)
{
	TestDeferred::Test test;
	int32_t test0 = 0;

	Cpf::Platform::Events::Handle event0(test.On<TestDeferred::Test::Test0>([&]() {
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

	Cpf::Platform::Events::Handle event0(test.On<TestDeferred::Test::Test0>([&]() {
		++test0;
	}));
	test.Emit<TestDeferred::Test::Test0>([&]() {++test1;});

	EXPECT_EQ(0, test0);
	EXPECT_EQ(0, test1);
	test();
	EXPECT_EQ(1, test0);
	EXPECT_EQ(1, test1);
}
