//////////////////////////////////////////////////////////////////////////
#include <gtest\gtest.h>
#include "SimdX.hpp"
#include "SIMD/Vector2.hpp"
#include "SIMD/Vector3.hpp"

//////////////////////////////////////////////////////////////////////////
using Vector3fv_SSE4_1 = Cpf::Math::Vector3<Cpf::SIMD::SSE4_1::F32x4_3>;
using Vector3fv_Reference = Cpf::Math::Vector3<Cpf::SIMD::Reference::F32x4_3>;

template <typename T>
class TypedTest_Vector3 : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Vector3fv_Reference,
	Vector3fv_SSE4_1,
	Cpf::Math::Vector3<Cpf::SIMD::Reference::I32x4_3>,
	Cpf::Math::Vector3<Cpf::SIMD::SSE4_1::I32x4_3>
> F32x4_1_Types;

TYPED_TEST_CASE(TypedTest_Vector3, F32x4_1_Types);


TYPED_TEST(TypedTest_Vector3, Construction)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	EXPECT_TRUE(Near(t0, { Element(1), Element(2), Element(3) }, Element(0.01f)));

	Type t1(Element(3), Element(4), Element(5));
	EXPECT_TRUE(Near(t1, { Element(3), Element(4), Element(5) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector3, ArrayAccess)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	EXPECT_NEAR(t0[0], Element(1), Element(0.01f));
	EXPECT_NEAR(t0[1], Element(2), Element(0.01f));
	EXPECT_NEAR(t0[2], Element(3), Element(0.01f));

	t0[0] = Element(5);
	t0[1] = Element(7);
	t0[2] = Element(8);
	EXPECT_NEAR(t0[0], Element(5), Element(0.01f));
	EXPECT_NEAR(t0[1], Element(7), Element(0.01f));
	EXPECT_NEAR(t0[2], Element(8), Element(0.01f));
}

TYPED_TEST(TypedTest_Vector3, OperatorAddAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	t0 += t1;

	EXPECT_TRUE((t0 == Type(Element(4), Element(6), Element(8))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3, OperatorSubtractAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	t0 -= t1;

	EXPECT_TRUE((t0 == Type(Element(-2), Element(-2), Element(-2))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3, OperatorMultiplyAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	t0 *= t1;

	EXPECT_TRUE((t0 == Type(Element(3), Element(8), Element(15))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3, OperatorDivideAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(12), Element(20), Element(25) };
	Type t1 = { Element(3), Element(4), Element(5) };
	t0 /= t1;

	EXPECT_TRUE((t0 == Type(Element(4), Element(5), Element(5))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3, OperatorNegate)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = -t0;

	EXPECT_TRUE(Near(t1, { Element(-1), Element(-2), Element(-3) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector3, OperatorEquals)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };

	EXPECT_TRUE((t0 == Type(Element(1), Element(2), Element(3))) == Type::kLaneMask);
	EXPECT_FALSE(t0 == t1);
}

TYPED_TEST(TypedTest_Vector3, OperatorNotEquals)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };

	EXPECT_FALSE((t0 != Type(Element(1), Element(2), Element(3))) == Type::kLaneMask);
	EXPECT_TRUE((t0 != t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3, OperatorLessThan)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };

	EXPECT_TRUE((t0 < Type(Element(1), Element(2), Element(3))) == 0);
	EXPECT_TRUE((t0 < t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3, OperatorLessThanEqual)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };

	EXPECT_TRUE((t0 <= Type(Element(1), Element(2), Element(3))) == Type::kLaneMask);
	EXPECT_TRUE((t0 <= t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3, OperatorGreaterThan)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };

	EXPECT_TRUE((t0 > Type(Element(1), Element(2), Element(3))) == 0);
	EXPECT_FALSE((t0 > t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3, OperatorGreaterThanEqual)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };

	EXPECT_TRUE((t0 >= Type(Element(1), Element(2), Element(3))) == Type::kLaneMask);
	EXPECT_FALSE((t0 >= t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3, OperatorAdd)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	Type t2 = t0 + t1;

	EXPECT_TRUE((t2 == Type(Element(4), Element(6), Element(8))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3, OperatorSubtract)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	Type t2 = t0 - t1;

	EXPECT_TRUE((t2 == Type(Element(-2), Element(-2), Element(-2))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3, OperatorMultiply)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	Type t2 = t0 * t1;

	EXPECT_TRUE(Near(t2, Type(Element(3), Element(8), Element(15)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector3, OperatorDevide)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	Type t2 = t0 / t1;

	EXPECT_TRUE(Near(t2, Type(Element(1.0f / 3.0f), Element(2.0f / 4.0f), Element(3.0f / 5.0f)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector3, Min)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	Type t2 = Min(t0, t1);

	EXPECT_TRUE((t2 == Type(Element(1.0f), Element(2.0f), Element(3.0f))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3, HMin)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Element t1 = HMin(t0);

	EXPECT_TRUE(t1 == Element(1));
}

TYPED_TEST(TypedTest_Vector3, Max)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	Type t2 = Max(t0, t1);

	EXPECT_TRUE((t2 == Type(Element(3.0f), Element(4.0f), Element(5.0f))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3, HMax)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Element t1 = HMax(t0);

	EXPECT_TRUE(t1 == Element(3));
}

TYPED_TEST(TypedTest_Vector3, Sqrt)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(9), Element(25), Element(36) };
	Type t1 = Sqrt(t0);

	EXPECT_TRUE(t1.x == Element(3));
	EXPECT_TRUE(t1.y == Element(5));
	EXPECT_TRUE(t1.z == Element(6));
}

TYPED_TEST(TypedTest_Vector3, Clamp)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(9), Element(25), Element(4) };
	Type t1 = Clamp(t0, Element(12), Element(16));

	EXPECT_TRUE(t1.x == Element(12));
	EXPECT_TRUE(t1.y == Element(16));
	EXPECT_TRUE(t1.z == Element(12));
}


TYPED_TEST(TypedTest_Vector3, Modulus)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;
	Type t0 = { Element(5.25f), Element(12.85f), Element(16.7f) };
	Type t1 = { Element(3.0f), Element(4.0f), Element(16) };
	Type t2 = Modulus(t0, t1);

	EXPECT_TRUE(Near(t2, { Element(2.25f), Element(0.85f), Element(0.7f) }, Element(0.01f)));
}

// NOTE: Next items only make sense for floating point.
TEST(Vector3fv, Dot_Reference)
{
	using Vector3fv = Vector3fv_Reference;
	Vector3fv t0 = { 5.0f, 12.0f, 13.0f };
	Vector3fv t1 = { 3.0f, 5.0f, 6.0f };
	float dot = Dot(t0, t1);
	EXPECT_NEAR(dot, (3.0f * 5.0f) + (5.0f * 12.0f) + (13.0f * 6.0f), 0.01f);
}

TEST(Vector3fv, Dot_SSE4_1)
{
	using Vector3fv = Vector3fv_SSE4_1;
	Vector3fv t0 = { 5.0f, 12.0f, 13.0f };
	Vector3fv t1 = { 3.0f, 5.0f, 6.0f };
	float dot = Dot(t0, t1);
	EXPECT_NEAR(dot, (3.0f * 5.0f) + (5.0f * 12.0f) + (13.0f * 6.0f), 0.01f);
}

TEST(Vector3fv, Magnitude_Reference)
{
	using Vector3fv = Vector3fv_Reference;
	Vector3fv t0 = { 5.0f, 12.0f, 13.0f };
	float dot = Magnitude(t0);
	EXPECT_NEAR(dot, std::sqrt((5.0f * 5.0f) + (12.0f * 12.0f) + (13.0f * 13.0f)), 0.01f);
}

TEST(Vector3fv, Magnitude_SSE4_1)
{
	using Vector3fv = Vector3fv_SSE4_1;
	Vector3fv t0 = { 5.0f, 12.0f, 13.0f };
	float dot = Magnitude(t0);
	EXPECT_NEAR(dot, std::sqrt((5.0f * 5.0f) + (12.0f * 12.0f) + (13.0f * 13.0f)), 0.01f);
}

TEST(Vector3fv, MagnitudeSq_Reference)
{
	using Vector3fv = Vector3fv_Reference;
	Vector3fv t0 = { 5.0f, 12.0f, 13.0f };
	float dot = MagnitudeSq(t0);
	EXPECT_NEAR(dot, (5.0f * 5.0f) + (12.0f * 12.0f) + (13.0f * 13.0f), 0.01f);
}

TEST(Vector3fv, MagnitudeSq_SSE4_1)
{
	using Vector3fv = Vector3fv_SSE4_1;
	Vector3fv t0 = { 5.0f, 12.0f, 13.0f };
	float dot = MagnitudeSq(t0);
	EXPECT_NEAR(dot, (5.0f * 5.0f) + (12.0f * 12.0f) + (13.0f * 13.0f), 0.01f);
}

TEST(Vector3fv, Normalize_Reference)
{
	using Vector3fv = Vector3fv_Reference;
	Vector3fv t0 = { 5.0f, 12.0f, 13.0f };
	Vector3fv t1 = Normalize(t0);
	EXPECT_TRUE(Near(t1, { t0.x / Magnitude(t0), t0.y / Magnitude(t0), t0.z / Magnitude(t0) }, 0.01f));
}

TEST(Vector3fv, Normalize_SSE4_1)
{
	using Vector3fv = Vector3fv_SSE4_1;
	Vector3fv t0 = { 5.0f, 12.0f, 13.0f };
	Vector3fv t1 = Normalize(t0);
	EXPECT_TRUE(Near(t1, { t0.x / Magnitude(t0), t0.y / Magnitude(t0), t0.z / Magnitude(t0) }, 0.01f));
}

TEST(Vector3fv, Reflect_Reference)
{
	using Type = Vector3fv_Reference;
	Type t0 = { 1.0f, 0.0f, 0.0f };
	Type t1 = { 0.0f, 1.0f, 0.0f };
	Type t3 = Reflect(t0, t1);
	EXPECT_TRUE(Near(t3, { 0.0f, -1.0f, 0.0f }, 0.01f));
}

TEST(Vector3fv, Reflect_SSE4_1)
{
	using Type = Vector3fv_SSE4_1;
	Type t0 = { 1.0f, 0.0f, 0.0f };
	Type t1 = { 0.0f, 1.0f, 0.0f };
	Type t3 = Reflect(t0, t1);
	EXPECT_TRUE(Near(t3, { 0.0f, -1.0f, 0.0f }, 0.01f));
}

TEST(Vector3fv, Reciprocal_Reference)
{
	using Vector3fv = Vector3fv_Reference;
	Vector3fv t0 = { 5.0f, 12.0f, 15.0f };
	Vector3fv t1 = Reciprocal(t0);

	EXPECT_NEAR(t1.x, 1.0f / t0.x, 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / t0.y, 0.01f);
	EXPECT_NEAR(t1.z, 1.0f / t0.z, 0.01f);
}
TEST(Vector3fv, Reciprocal_SSE4_1)
{
	using Vector3fv = Vector3fv_SSE4_1;
	Vector3fv t0 = { 5.0f, 12.0f, 15.0f };
	Vector3fv t1 = Reciprocal(t0);

	EXPECT_NEAR(t1.x, 1.0f / t0.x, 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / t0.y, 0.01f);
	EXPECT_NEAR(t1.z, 1.0f / t0.z, 0.01f);
}

TEST(Vector3fv, RSqrt_Reference)
{
	using Vector3fv = Vector3fv_Reference;
	Vector3fv t0 = { 5.0f, 12.0f, 15.0f };
	Vector3fv t1 = RSqrt(t0);

	EXPECT_NEAR(t1.x, 1.0f / std::sqrt(t0.x), 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / std::sqrt(t0.y), 0.01f);
	EXPECT_NEAR(t1.z, 1.0f / std::sqrt(t0.z), 0.01f);
}
TEST(Vector3fv, RSqrt_SSE4_1)
{
	using Vector3fv = Vector3fv_SSE4_1;
	Vector3fv t0 = { 5.0f, 12.0f, 15.0f };
	Vector3fv t1 = RSqrt(t0);

	EXPECT_NEAR(t1.x, 1.0f / std::sqrt(t0.x), 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / std::sqrt(t0.y), 0.01f);
	EXPECT_NEAR(t1.z, 1.0f / std::sqrt(t0.z), 0.01f);
}

//////////////////////////////////////////////////////////////////////////
TEST(Vector3fv, Round_Truncate_Reference)
{
	using Vector3fv = Vector3fv_Reference;
	Vector3fv t0 = { 5.25f, 12.85f, 19.22f };
	Vector3fv t1 = Round(t0, Cpf::SIMD::Rounding::eTruncate);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f, 19.0f }, 0.01f));
}
TEST(Vector3fv, Round_Truncate_SSE4_1)
{
	using Vector3fv = Vector3fv_SSE4_1;
	Vector3fv t0 = { 5.25f, 12.85f, 19.22f };
	Vector3fv t1 = Round(t0, Cpf::SIMD::Rounding::eTruncate);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f, 19.0f }, 0.01f));
}

TEST(Vector3fv, Floor_Reference)
{
	using Vector3fv = Vector3fv_Reference;
	Vector3fv t0 = { 5.25f, 12.85f, 19.22f };
	Vector3fv t1 = Floor(t0);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f, 19.0f }, 0.01f));
}
TEST(Vector3fv, Floor_SSE4_1)
{
	using Vector3fv = Vector3fv_SSE4_1;
	Vector3fv t0 = { 5.25f, 12.85f, 19.22f };
	Vector3fv t1 = Floor(t0);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f, 19.0f }, 0.01f));
}

TEST(Vector3fv, Ceil_Reference)
{
	using Vector3fv = Vector3fv_Reference;
	Vector3fv t0 = { 5.25f, 12.85f, 19.22f };
	Vector3fv t1 = Ceil(t0);

	EXPECT_TRUE(Near(t1, { 6.0f, 13.0f, 20.0f }, 0.01f));
}
TEST(Vector3fv, Ceil_SSE4_1)
{
	using Vector3fv = Vector3fv_SSE4_1;
	Vector3fv t0 = { 5.25f, 12.85f, 19.22f };
	Vector3fv t1 = Ceil(t0);

	EXPECT_TRUE(Near(t1, { 6.0f, 13.0f, 20.0f }, 0.01f));
}

TEST(Vector3fv, Cross_Reference)
{
	using Vector3fv = Vector3fv_Reference;
	Vector3fv t0 = { 1.0f, 0.0f, 0.0f };
	Vector3fv t1 = { 0.0f, 1.0f, 0.0f };
	Vector3fv t2 = Cross(t0, t1);

	EXPECT_TRUE(Near(t2, { 0.0f, 0.0f, 1.0f }, 0.01f));
}
TEST(Vector3fv, Cross_SSE4_1)
{
	using Vector3fv = Vector3fv_SSE4_1;
	Vector3fv t0 = { 1.0f, 0.0f, 0.0f };
	Vector3fv t1 = { 0.0f, 1.0f, 0.0f };
	Vector3fv t2 = Cross(t0, t1);

	EXPECT_TRUE(Near(t2, { 0.0f, 0.0f, 1.0f }, 0.01f));
}
