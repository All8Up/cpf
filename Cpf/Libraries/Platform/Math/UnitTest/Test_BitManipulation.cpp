//////////////////////////////////////////////////////////////////////////
#include "Math/BitManipulation.hpp"
#include <gtest/gtest.h>


TEST(Math, Bits_SplitByOne_Limits)
{
	using namespace CPF::Math;
	uint32_t maxBit32 = uint32_t(1) << 15;
	uint32_t maxBit64 = uint32_t(1) << 31;

	// Zero
	EXPECT_EQ(0, SplitByOne32(0));
	EXPECT_EQ(0, SplitByOne64(0));

	// Epsilon
	EXPECT_EQ(1, SplitByOne32(1));
	EXPECT_EQ(1, SplitByOne64(1));

	// Max bit
	EXPECT_EQ(0x40000000, SplitByOne32(maxBit32));
	EXPECT_EQ(0x4000000000000000, SplitByOne64(maxBit64));

	// Max value
	EXPECT_EQ(0x55555555, SplitByOne32(maxBit32 + (maxBit32 - 1)));
	EXPECT_EQ(0x5555555555555555, SplitByOne64(maxBit64 + (maxBit64 - 1)));
}

TEST(Math, Bits_SplitByTwo_Limits)
{
	using namespace CPF::Math;
	uint32_t maxBit32 = uint32_t(1) << 9;
	uint32_t maxBit64 = uint32_t(1) << 20;

	// Zero
	EXPECT_EQ(0, SplitByTwo32(0));
	EXPECT_EQ(0, SplitByTwo64(0));

	// Epsilon
	EXPECT_EQ(1, SplitByTwo32(1));
	EXPECT_EQ(1, SplitByTwo64(1));

	// Max bit
	EXPECT_EQ(0x08000000, SplitByTwo32(maxBit32));
	EXPECT_EQ(0x1000000000000000, SplitByTwo64(maxBit64));

	// Max value
	EXPECT_EQ(0x09249249, SplitByTwo32(maxBit32 + (maxBit32 - 1)));
	EXPECT_EQ(0x1249249249249249, SplitByTwo64(maxBit64 + (maxBit64 - 1)));
}
