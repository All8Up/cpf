//////////////////////////////////////////////////////////////////////////
#include "Events/Emitter.hpp"
#include "Functional.hpp"

/// @cond
namespace EventsBasic
{
	class Test : public CPF::Events::Emitter
	{
	public:
		typedef CPF::Events::Event< 0, CPF::Function< void(void) > > Event0;
		typedef CPF::Events::Event< 1, CPF::Function< void(int32_t) > > Event1;
		typedef CPF::Events::Event< 2, CPF::Function< void(int32_t, int32_t) > > Event2;
		typedef CPF::Events::Event< 3, CPF::Function< void(void) > > Event3;
		typedef CPF::Events::Event< 4, CPF::Function< void(void) > > Event4;
	};
}


TEST(Events, Basics)
{
	int32_t event0Fired = 0;
	int32_t event1Fired = 0;
	int32_t event2Fired = 0;
	int32_t event3Fired = 0;
	int32_t event4Fired = 0;

	EventsBasic::Test test0;
	CPF::Events::Handle event0(test0.On<EventsBasic::Test::Event0>([&]() {
		++event0Fired;
	}));

	test0.Emit<EventsBasic::Test::Event0>();
	test0.Emit<EventsBasic::Test::Event1>(0);
	test0.Emit<EventsBasic::Test::Event2>(0, 1);

	EXPECT_EQ(1, event0Fired);
	EXPECT_EQ(0, event1Fired);
	EXPECT_EQ(0, event2Fired);
	EXPECT_EQ(0, event3Fired);

	CPF::Events::Handle event1(test0.On<EventsBasic::Test::Event1>([&](int32_t) {
		++event1Fired;
	}));

	CPF::Events::Handle event2(test0.On<EventsBasic::Test::Event2>([&](int32_t, int32_t) {
		++event2Fired;
	}));

	test0.Emit<EventsBasic::Test::Event0>();
	test0.Emit<EventsBasic::Test::Event1>(0);
	test0.Emit<EventsBasic::Test::Event2>(0, 1);
	test0.Emit<EventsBasic::Test::Event3>();

	EXPECT_EQ(2, event0Fired);
	EXPECT_EQ(1, event1Fired);
	EXPECT_EQ(1, event2Fired);
	EXPECT_EQ(0, event3Fired);

	CPF::Events::Handle event3(test0.On<EventsBasic::Test::Event3>([&]() {
		++event3Fired;
		test0.Remove(event1);
		test0.On<EventsBasic::Test::Event4>([&]() {
			++event4Fired;
		});
	}));

	test0.Emit<EventsBasic::Test::Event3>();
	EXPECT_EQ(1, event3Fired);
	EXPECT_EQ(0, event4Fired);

	test0.Emit<EventsBasic::Test::Event4>();
	EXPECT_EQ(2, event0Fired);
	EXPECT_EQ(1, event1Fired);
	EXPECT_EQ(1, event2Fired);
	EXPECT_EQ(1, event3Fired);
	EXPECT_EQ(1, event4Fired);
}
/// @endcond
