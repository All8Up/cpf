//////////////////////////////////////////////////////////////////////////
#include <gtest\gtest.h>
#include "SimdX.hpp"

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_F32x4_1 : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Cpf::SIMD::SSE4_1::F32x4_1
> F32x4_1_Types;

TYPED_TEST_CASE( TypedTest_F32x4_1, F32x4_1_Types );


TYPED_TEST( TypedTest_F32x4_1 , BasicMath )
{
	using namespace Cpf;
	using namespace SIMD;
	using Type = Cpf::SIMD::F32x4_1; // typename TypeParam;

	Type a = 1.0f;
	Type b = 2.0f;

	EXPECT_NEAR(a, 1.0f, 0.01f);
	EXPECT_TRUE(Near(a, 1.0f, 0.01f));
	EXPECT_NEAR(b, 2.0f, 0.01f);
	EXPECT_TRUE(Near(b, 2.0f, 0.01f));

	EXPECT_FALSE(Near(a, 2.0f, 0.01f));
	EXPECT_FALSE(Near(b, 1.0f, 0.01f));

	Type c = a + b;
	Type d = b - a;
	Type e = a * b;
	Type f = a / b;

	EXPECT_NEAR(c, 3.0f, 0.01f);
	EXPECT_NEAR(d, 1.0f, 0.01f);
	EXPECT_NEAR(e, 2.0f, 0.01f);
	EXPECT_NEAR(f, 0.5f, 0.01f);

	EXPECT_TRUE(Valid(a));
	EXPECT_TRUE(Valid(b));
	EXPECT_TRUE(Valid(c));
	EXPECT_TRUE(Valid(d));
	EXPECT_TRUE(Valid(e));
	EXPECT_TRUE(Valid(f));
}

TEST(SimdX, I32x4_1)
{
	using namespace Cpf;
	using namespace SIMD;

	using Type = Cpf::SIMD::I32x4_1; // typename TypeParam;

	Type a = 1;
	Type b = 2;

	EXPECT_EQ(a, 1);
	EXPECT_EQ(b, 2);
	Type ab_p = a + b;
	EXPECT_EQ(ab_p, 3);
	Type ab_s = a - b;
	EXPECT_EQ(ab_s, -1);
	Type ab_m = a * b;
	EXPECT_EQ(ab_m, 2);
	Type ab_d = a / b;
	EXPECT_EQ(ab_d, 0);
}

TEST(SimdX, Float32x2)
{
	using namespace Cpf;
	using namespace SIMD;

	F32x1 a = 1.0f;
	F32x1 b = 2.0f;
	F32x2 aa = { a, a };
	F32x2 ab = { a, b };
	F32x2 bb = { b, b };
	F32x2 ba = { b, a };

	EXPECT_TRUE(Near(aa, { 1.0f, 1.0f }, 0.01f));
	EXPECT_TRUE(Near(ab, { 1.0f, 2.0f }, 0.01f));
	EXPECT_TRUE(Near(bb, { 2.0f, 2.0f }, 0.01f));
	EXPECT_TRUE(Near(ba, { 2.0f, 1.0f }, 0.01f));

	F32x2 aaab_p = aa + ab;
	EXPECT_TRUE(Near(aaab_p, { 2.0f, 3.0f }, 0.01f));
	F32x2 aaab_s = aa - ab;
	EXPECT_TRUE(Near(aaab_s, { 0.0f, -1.0f }, 0.01f));
	F32x2 aaab_m = aa * ab;
	EXPECT_TRUE(Near(aaab_m, { 1.0f, 2.0f }, 0.01f));
	F32x2 aaab_d = aa / ab;
	EXPECT_TRUE(Near(aaab_d, { 1.0f, 0.5f }, 0.01f));

	EXPECT_TRUE(Valid(a));
	EXPECT_TRUE(Valid(b));
	EXPECT_TRUE(Valid(aa));
	EXPECT_TRUE(Valid(ab));
	EXPECT_TRUE(Valid(bb));
	EXPECT_TRUE(Valid(ba));
	EXPECT_TRUE(Valid(aaab_p));
	EXPECT_TRUE(Valid(aaab_s));
	EXPECT_TRUE(Valid(aaab_m));
	EXPECT_TRUE(Valid(aaab_d));
}

TEST(SimdX, Float32x4)
{
	using namespace Cpf;
	using namespace SIMD;

	Float32x4 a = {1.0f, 2.0f, 3.0f, 4.0f};
	float x = a.x;
	float y = a.y;
	float z = a.z;
	float w = a.w;

	Float32x4 _xy89(a.xy, 8.0f, 9.0f);
	Float32x4 _8yz9(8.0f, a.yz, 9.0f);
	Float32x4 _89zw(8.0f, 9.0f, a.zw);
	Float32x4 _zwxy(a.zw, a.xy);
}
