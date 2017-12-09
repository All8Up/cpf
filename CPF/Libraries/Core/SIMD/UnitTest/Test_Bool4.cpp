//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "SIMD/Detail/FPU/Bool4.hpp"
#include "SIMD/Detail/Reference/Bool4.hpp"
#include "SIMD/Detail/SSE4_1/Bool4.hpp"

using namespace CPF::SIMD;

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_Bool4 : public::testing::Test
{
public:
};

typedef ::testing::Types <
	FPU::Bool4_4,
	Reference::Bool4_4,
	SSE4_1::Bool4_4
> Bool4_Types;

TYPED_TEST_CASE(TypedTest_Bool4, Bool4_Types);

TYPED_TEST(TypedTest_Bool4, Bool4_SplatConstruction)
{
	typename TypeParam::Lanes_1 t0(true);
	EXPECT_EQ(1, t0.ToMask());
	typename TypeParam::Lanes_2 t1(true);
	EXPECT_EQ(3, t1.ToMask());
	typename TypeParam::Lanes_3 t2(true);
	EXPECT_EQ(7, t2.ToMask());
	typename TypeParam::Lanes_4 t3(true);
	EXPECT_EQ(15, t3.ToMask());
}

TYPED_TEST(TypedTest_Bool4, Bool4_LaneConstruction)
{
	typename TypeParam::Lanes_1 t0(true);
	EXPECT_EQ(1, t0.ToMask());

	typename TypeParam::Lanes_2 t1(true, true);
	EXPECT_EQ(3, t1.ToMask());
	typename TypeParam::Lanes_2 t1_01(false, true);
	EXPECT_EQ(2, t1_01.ToMask());
	typename TypeParam::Lanes_2 t1_10(true, false);
	EXPECT_EQ(1, t1_10.ToMask());

	typename TypeParam::Lanes_3 t2(true, true, true);
	EXPECT_EQ(7, t2.ToMask());

	typename TypeParam::Lanes_4 t3(true, true, true, true);
	EXPECT_EQ(15, t3.ToMask());
	typename TypeParam::Lanes_4 t3_0001(false, false, false, true);
	EXPECT_EQ(8, t3_0001.ToMask());
	typename TypeParam::Lanes_4 t3_0010(false, false, true, false);
	EXPECT_EQ(4, t3_0010.ToMask());
	typename TypeParam::Lanes_4 t3_0100(false, true, false, false);
	EXPECT_EQ(2, t3_0100.ToMask());
	typename TypeParam::Lanes_4 t3_1000(true, false, false, false);
	EXPECT_EQ(1, t3_1000.ToMask());
}

TYPED_TEST(TypedTest_Bool4, Bool4_Comparison)
{
	typename TypeParam::Lanes_2 t1(true, true);
	typename TypeParam::Lanes_2 t1_01(false, true);
	typename TypeParam::Lanes_2 t1_10(true, false);

	typename TypeParam::Lanes_2 t2(true, true);
	typename TypeParam::Lanes_2 t2_01(false, true);
	typename TypeParam::Lanes_2 t2_10(true, false);

	EXPECT_TRUE(t1 == t2);
	EXPECT_TRUE(t1_01 == t2_01);
	EXPECT_TRUE(t1_10 == t2_10);
}

TYPED_TEST(TypedTest_Bool4, Bool4_Any)
{
	typename TypeParam::Lanes_2 t1(true, true);
	typename TypeParam::Lanes_2 t1_01(false, true);
	typename TypeParam::Lanes_2 t1_10(true, false);
	typename TypeParam::Lanes_2 t1_00(false, false);

	EXPECT_TRUE(Any(t1));
	EXPECT_TRUE(Any(t1_01));
	EXPECT_TRUE(Any(t1_10));
	EXPECT_FALSE(Any(t1_00));
}

TYPED_TEST(TypedTest_Bool4, Bool4_All)
{
	typename TypeParam::Lanes_2 t1(true, true);
	typename TypeParam::Lanes_2 t1_01(false, true);
	typename TypeParam::Lanes_2 t1_10(true, false);
	typename TypeParam::Lanes_2 t1_00(false, false);

	EXPECT_TRUE(All(t1));
	EXPECT_FALSE(All(t1_01));
	EXPECT_FALSE(All(t1_10));
	EXPECT_FALSE(All(t1_00));
}
