//////////////////////////////////////////////////////////////////////////
#pragma once
#include <gtest\gtest.h>
#include "SimdX.hpp"
#include "SIMD/Vector2v.hpp"
#include "SIMD/Vector3v.hpp"
#include "SIMD/Vector4v.hpp"


//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_Vector3v : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Cpf::Math::Vector3v<Cpf::SIMD::Reference::F32x4_3>,
	Cpf::Math::Vector3v<Cpf::SIMD::SSE4_1::F32x4_3>
> TypedTest_Vector3v_Types;

TYPED_TEST_CASE(TypedTest_Vector3v, TypedTest_Vector3v_Types);

TYPED_TEST(TypedTest_Vector3v, Vector3fv)
{
	using Vector3fv = typename TypeParam;

	Vector3fv t0 = Vector3fv(0.0f);
	EXPECT_NEAR(t0.x, 0.0f, 0.01f);
	EXPECT_NEAR(t0.y, 0.0f, 0.01f);
	EXPECT_NEAR(t0.z, 0.0f, 0.01f);
/*	EXPECT_TRUE(Near(t0.xy, { 0.0f, 0.0f }, 0.01f));
	EXPECT_TRUE(Near(t0.yz, { 0.0f, 0.0f }, 0.01f));
	EXPECT_TRUE(Near(t0.xyz, { 0.0f, 0.0f,0.0f }, 0.01f)); */

	Vector3fv t1 = t0.xyz;
	EXPECT_NEAR(t1.x, 0.0f, 0.01f);
	EXPECT_NEAR(t1.y, 0.0f, 0.01f);
	EXPECT_NEAR(t1.z, 0.0f, 0.01f);

	/*
	EXPECT_TRUE(Near(t0, t1));
	*/

	t1 = Vector3fv(1.0f, 0.0f, 1.0f);
	t1 = Vector3fv(2.0f, 3.0f, 4.0f);
}

TEST(SimdX, I32x4_1)
{
	using namespace Cpf;
	using namespace SIMD;

	using Type = Cpf::SIMD::SSE4_1::I32x4_1; // typename TypeParam;

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
	using namespace SSE4_1;

	F32x4_1 a = 1.0f;
	F32x4_1 b = 2.0f;
	F32x4_2 aa = { a, a };
	F32x4_2 ab = { a, b };
	F32x4_2 bb = { b, b };
	F32x4_2 ba = { b, a };

	EXPECT_TRUE(Near(aa, { 1.0f, 1.0f }, 0.01f));
	EXPECT_TRUE(Near(ab, { 1.0f, 2.0f }, 0.01f));
	EXPECT_TRUE(Near(bb, { 2.0f, 2.0f }, 0.01f));
	EXPECT_TRUE(Near(ba, { 2.0f, 1.0f }, 0.01f));

	F32x4_2 aaab_p = aa + ab;
	EXPECT_TRUE(Near(aaab_p, { 2.0f, 3.0f }, 0.01f));
	F32x4_2 aaab_s = aa - ab;
	EXPECT_TRUE(Near(aaab_s, { 0.0f, -1.0f }, 0.01f));
	F32x4_2 aaab_m = aa * ab;
	EXPECT_TRUE(Near(aaab_m, { 1.0f, 2.0f }, 0.01f));
	F32x4_2 aaab_d = aa / ab;
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

TEST(SimdX, F32x4)
{
	using namespace Cpf;
	using namespace SIMD;
	using namespace SSE4_1;

	{
		F32x4_4 a = { 1.0f, 2.0f, 3.0f, 4.0f };
		float low_a = HMin(a);
		EXPECT_NEAR(low_a, 1.0f, 0.01f);

		F32x4_4 b = { 4.0f, 3.0f, 2.0f, 1.0f };
		float low_b = HMin(b);
		EXPECT_NEAR(low_b, 1.0f, 0.01f);
	}
	{
		F32x4_4 a = { 1.0f, 2.0f, 3.0f, 4.0f };
		float high_a = HMax(a);
		EXPECT_NEAR(high_a, 4.0f, 0.01f);

		F32x4_4 b = { 4.0f, 3.0f, 2.0f, 1.0f };
		float high_b = HMax(b);
		EXPECT_NEAR(high_b, 4.0f, 0.01f);
	}
}
/*
TEST(SimdX, IntersectRayBox)
{
	using namespace Cpf;
	using namespace SIMD;
	using namespace SSE4_1;

	Float32x4<F32x4_4> rayOrg(0.0f, 0.0f, 0.0f, 0.0f);
	Float32x4<F32x4_4> invDir(0.0f, 0.0f, 1.0f, 0.0f);
	Float32x4<F32x4_4> bbmin(5.0f, 5.0f, 1.0f, 0.0f);
	Float32x4<F32x4_4> bbmax(6.0f, 5.0f, 2.0f, 0.0f);
	float hitT = 0.0f;

	Float32x4<F32x4_4> d0 = (bbmin - rayOrg) * invDir;
	Float32x4<F32x4_4> d1 = (bbmax - rayOrg) * invDir;

	Float32x4<F32x4_4> v0 = Min(d0, d1);
	Float32x4<F32x4_4> v1 = Max(d0, d1);

	float tmin = HMax(v0);
	float tmax = HMin(v1);

	hitT = tmin;
	bool hit = (tmax >= 0) && (tmax >= tmin) && (tmin <= hitT);
	EXPECT_FALSE(hit);
}
*/
