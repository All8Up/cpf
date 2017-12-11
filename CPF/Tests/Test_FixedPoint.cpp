//////////////////////////////////////////////////////////////////////////
#include "gtest/gtest.h"
#include "CPF/Math/FixedPoint.hpp"

using Type32_4 = CPF::Math::FixedPoint<32, 4>;
using Type32_8 = CPF::Math::FixedPoint<32, 8>;
using Type64_4 = CPF::Math::FixedPoint<64, 4>;
using Type64_8 = CPF::Math::FixedPoint<64, 8>;

Type32_4 fp32_4_one(1.0f);
Type32_4 nfp32_4_one(-1.0f);

Type32_4 fp32_4(1.25f);
Type32_4 nfp32_4(-1.25f);
Type32_4 fp32_4h(0.5f);

Type32_8 fp32_8(1.25f);
Type32_8 nfp32_8(-1.25f);
Type32_8 fp32_8h(0.5f);

Type64_4 fp64_4(1.25f);
Type64_4 nfp64_4(-1.25f);
Type64_4 fp64_4h(0.5f);

Type64_8 fp64_8(1.25f);
Type64_8 nfp64_8(-1.25f);
Type64_8 fp64_8h(0.5f);

TEST(FixedPoint, Construction)
{
	EXPECT_NEAR(1.0f, float(fp32_4_one), 0.01f);
	EXPECT_NEAR(-1.0f, float(nfp32_4_one), 0.01f);
	EXPECT_NEAR(-1.25f, float(nfp32_4), 0.01f);

	// Should be 16(=1) + 4(=.25)
	EXPECT_EQ(16 + 4, int32_t(fp32_4));
	EXPECT_NEAR(1.25f, float(fp32_4), 0.01f);

	// Should be 256(=1) + 64(=.25)
	EXPECT_EQ(320, int32_t(fp32_8));
	EXPECT_NEAR(1.25f, float(fp32_8), 0.01f);

	// Should be 16(=1) + 4(=.25) 
	EXPECT_EQ(16 + 4, int64_t(fp64_4));
	EXPECT_NEAR(1.25, double(fp64_4), 0.01);

	// Should be 256(=1) + 64(=.25)
	EXPECT_EQ(320, int64_t(fp64_8));
	EXPECT_NEAR(1.25, double(fp64_8), 0.01);
}

TEST(FixedPoint, Addition)
{
	// Should be 16(=1) + 4(=.25) * 2 = 40;
	Type32_4 fp32_4_add = fp32_4 + fp32_4;
	EXPECT_EQ(32 + 8, int32_t(fp32_4_add));
	EXPECT_NEAR(2.5f, float(fp32_4_add), 0.01f);

	// Should be 256(=1) + 64(=.25)
	Type32_8 fp32_8_add = fp32_8 + fp32_8;
	EXPECT_EQ(640, int32_t(fp32_8_add));
	EXPECT_NEAR(2.5f, float(fp32_8_add), 0.01f);

	// Should be 16(=1) + 4(=.25) * 2 = 40;
	Type64_4 fp64_4_add = fp64_4 + fp64_4;
	EXPECT_EQ(32 + 8, int64_t(fp64_4_add));
	EXPECT_NEAR(2.5, double(fp64_4_add), 0.01);

	// Should be 256(=1) + 64(=.25)
	Type64_8 fp64_8_add = fp64_8 + fp64_8;
	EXPECT_EQ(640, int64_t(fp64_8_add));
	EXPECT_NEAR(2.5, double(fp64_8_add), 0.01);
}

TEST(FixedPoint, Subtraction)
{
	Type32_4 fp32_4_sub = fp32_4 - fp32_4h;
	EXPECT_EQ(20 - 8, int32_t(fp32_4_sub));
	EXPECT_NEAR(0.75f, float(fp32_4_sub), 0.01f);

	Type32_8 fp32_8_sub = fp32_8 - fp32_8h;
	EXPECT_EQ(320 - 128, int32_t(fp32_8_sub));
	EXPECT_NEAR(0.75f, float(fp32_8_sub), 0.01f);

	Type64_4 fp64_4_sub = fp64_4 - fp64_4h;
	EXPECT_EQ(20 - 8, int64_t(fp64_4_sub));
	EXPECT_NEAR(0.75, double(fp64_4_sub), 0.01);

	Type64_8 fp64_8_sub = fp64_8 - fp64_8h;
	EXPECT_EQ(320 - 128, int64_t(fp64_8_sub));
	EXPECT_NEAR(0.75, double(fp64_8_sub), 0.01);
}

TEST(FixedPoint, Multiplication)
{
	Type32_4 fp32_4_mul = fp32_4 * fp32_4h;
	EXPECT_EQ(10, int32_t(fp32_4_mul));
	EXPECT_NEAR(0.625f, float(fp32_4_mul), 0.01f);
}

TEST(FixedPoint, Division)
{
	Type32_4 fp32_4_div = fp32_4 / fp32_4h;
	EXPECT_EQ(40, int32_t(fp32_4_div));
	EXPECT_NEAR(2.5f, float(fp32_4_div), 0.01f);
}
