//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "CPF/Outcome.hpp"

using namespace CPF;

TEST(Outcome, BasicNonVoidError)
{
	using OptionInt = Outcome<int, int>;
	auto t0 = OptionInt::OK(1);
	auto t1 = OptionInt::Error(2);
	
	EXPECT_EQ(1, t0.GetOK());
	EXPECT_EQ(2, t1.GetError());
}

TEST(Outcome, BasicVoidError)
{
	using OptionInt = Outcome<int>;
	auto t0 = OptionInt::OK(1);
	auto t1 = OptionInt::Error();
	
	EXPECT_EQ(1, t0.GetOK());
	EXPECT_TRUE(t1.IsError());
}
