//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "CPF/Option.hpp"

using namespace CPF;

TEST(Option, BasicNonVoidError)
{
	using OptionInt = Option<int>;
	auto t0 = OptionInt::Some(1);
	auto t1 = OptionInt::None();
	
	EXPECT_EQ(1, t0.GetSome());
	EXPECT_TRUE(t1.IsNone());
}
