#pragma once
#include "Time/Unit.hpp"


TEST_F(TimeLibrary, InitializationUs)
{
	using namespace CPF::Time;
	EXPECT_EQ(1, int64_t(oneUs));
}


TEST_F(TimeLibrary, ComparisonsUs)
{
	using namespace CPF::Time;
	Us twoUs(2);

	EXPECT_GT(twoUs, oneUs);
	EXPECT_LT(oneUs, twoUs);
	EXPECT_GE(twoUs, oneUs);
	EXPECT_GE(twoUs, twoUs);
	EXPECT_LE(oneUs, twoUs);
	EXPECT_LE(oneUs, oneUs);
	EXPECT_EQ(oneUs, oneUs);
	EXPECT_NE(oneUs, twoUs);
}


TEST_F(TimeLibrary, MathUs)
{
	using namespace CPF::Time;
	Us twoUs(2);

	EXPECT_EQ(twoUs, oneUs + oneUs);
	EXPECT_EQ(oneUs, twoUs - oneUs);
	EXPECT_EQ(oneUs, twoUs * 0.5);
	EXPECT_EQ(oneUs, twoUs / 2.0);
}


TEST_F(TimeLibrary, InitializationMs)
{
	using namespace CPF::Time;
	EXPECT_EQ(1, int64_t(oneMs));
}


TEST_F(TimeLibrary, ComparisonsMs)
{
	using namespace CPF::Time;
	Ms twoMs(2);

	EXPECT_GT(twoMs, oneMs);
	EXPECT_LT(oneMs, twoMs);
	EXPECT_GE(twoMs, oneMs);
	EXPECT_GE(twoMs, twoMs);
	EXPECT_LE(oneMs, twoMs);
	EXPECT_LE(oneMs, oneMs);
	EXPECT_EQ(oneMs, oneMs);
	EXPECT_NE(oneMs, twoMs);
}


TEST_F(TimeLibrary, MathMs)
{
	using namespace CPF::Time;
	Ms twoMs(2);

	EXPECT_EQ(twoMs, oneMs + oneMs);
	EXPECT_EQ(oneMs, twoMs - oneMs);
	EXPECT_EQ(oneMs, twoMs * 0.5);
	EXPECT_EQ(oneMs, twoMs / 2.0);
}
