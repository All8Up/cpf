//////////////////////////////////////////////////////////////////////////
#include <gtest\gtest.h>
#include "SimdX.hpp"
#include "SIMD/Vector2v.hpp"
#include "SIMD/Vector3v.hpp"

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_Vector3v : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Cpf::Math::Vector3v<Cpf::SIMD::Reference::F32x4_3>,
	Cpf::Math::Vector3v<Cpf::SIMD::SSE4_1::F32x4_3>,
	Cpf::Math::Vector3v<Cpf::SIMD::Reference::I32x4_3>,
	Cpf::Math::Vector3v<Cpf::SIMD::SSE4_1::I32x4_3>
> F32x4_1_Types;

TYPED_TEST_CASE(TypedTest_Vector3v, F32x4_1_Types);


TYPED_TEST(TypedTest_Vector3v, Construction)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	EXPECT_TRUE(Near(t0, { Element(1), Element(2), Element(3) }, Element(0.01f)));

	Type t1(Element(3), Element(4), Element(5));
	EXPECT_TRUE(Near(t1, { Element(3), Element(4), Element(5) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector3v, ArrayAccess)
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

TYPED_TEST(TypedTest_Vector3v, OperatorAddAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	t0 += t1;

	EXPECT_TRUE((t0 == Type(Element(4), Element(6), Element(8))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3v, OperatorSubtractAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	t0 -= t1;

	EXPECT_TRUE((t0 == Type(Element(-2), Element(-2), Element(-2))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3v, OperatorMultiplyAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	t0 *= t1;

	EXPECT_TRUE((t0 == Type(Element(3), Element(8), Element(15))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3v, OperatorDivideAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(12), Element(20), Element(25) };
	Type t1 = { Element(3), Element(4), Element(5) };
	t0 /= t1;

	EXPECT_TRUE((t0 == Type(Element(4), Element(5), Element(5))) == Type::kLaneMask);
}

#if 0
TYPED_TEST(TypedTest_Vector3v, OperatorNegate)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = -t0;

	EXPECT_TRUE(Near(t1, { Element(-1), Element(-2) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector3v, OperatorEquals)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 == Type(Element(1), Element(2))) == Type::kLaneMask);
	EXPECT_FALSE(t0 == t1);
}

TYPED_TEST(TypedTest_Vector3v, OperatorNotEquals)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_FALSE((t0 != Type(Element(1), Element(2))) == Type::kLaneMask);
	EXPECT_TRUE((t0 != t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3v, OperatorLessThan)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 < Type(Element(1), Element(2))) == 0);
	EXPECT_TRUE((t0 < t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3v, OperatorLessThanEqual)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 <= Type(Element(1), Element(2))) == Type::kLaneMask);
	EXPECT_TRUE((t0 <= t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3v, OperatorGreaterThan)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 > Type(Element(1), Element(2))) == 0);
	EXPECT_FALSE((t0 > t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3v, OperatorGreaterThanEqual)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 >= Type(Element(1), Element(2))) == Type::kLaneMask);
	EXPECT_FALSE((t0 >= t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3v, OperatorAdd)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = t0 + t1;

	EXPECT_TRUE((t2 == Type(Element(4), Element(6))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3v, OperatorSubtract)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = t0 - t1;

	EXPECT_TRUE((t2 == Type(Element(-2), Element(-2))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3v, OperatorMultiply)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = t0 * t1;

	EXPECT_TRUE(Near(t2, Type(Element(3), Element(8)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector3v, OperatorDevide)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = t0 / t1;

	EXPECT_TRUE((t2 == Type(Element(1.0f / 3.0f), Element(2.0f / 4.0f))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3v, Min)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = Min(t0, t1);

	EXPECT_TRUE((t2 == Type(Element(1.0f), Element(2.0f))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3v, HMin)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = HMin(t0);

	EXPECT_TRUE(t1.x == Element(1));
}

TYPED_TEST(TypedTest_Vector3v, Max)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = Max(t0, t1);

	EXPECT_TRUE((t2 == Type(Element(3.0f), Element(4.0f))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector3v, HMax)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = HMax(t0);

	EXPECT_TRUE(t1.x == Element(2));
}

TYPED_TEST(TypedTest_Vector3v, Sqrt)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(9), Element(25) };
	Type t1 = Sqrt(t0);

	EXPECT_TRUE(t1.x == Element(3));
	EXPECT_TRUE(t1.y == Element(5));
}

TYPED_TEST(TypedTest_Vector3v, Clamp)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(9), Element(25) };
	Type t1 = Clamp(t0, Element(12), Element(16));

	EXPECT_TRUE(t1.x == Element(12));
	EXPECT_TRUE(t1.y == Element(16));
}


TYPED_TEST(TypedTest_Vector3v, Modulus)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;
	Type t0 = { Element(5.25f), Element(12.85f) };
	Type t1 = { Element(3.0f), Element(4.0f) };
	Type t2 = Modulus(t0, t1);

	EXPECT_TRUE(Near(t2, { Element(2.25f), Element(0.85f) }, Element(0.01f)));
}

// NOTE: Next items only make sense for floating point.
TEST(Vector3fv, Dot_Reference)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::Reference::F32x4_2>;
	Vector3fv t0 = { 5.0f, 12.0f, 13.0f };
	Vector3fv t1 = { 3.0f, 5.0f, 6.0f };
	float dot = Dot(t0, t1);
	EXPECT_NEAR(dot, (3.0f * 5.0f) + (5.0f * 12.0f) + (13.0f * 6.0f), 0.01f);
}

TEST(Vector3fv, Dot_SSE4_1)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector3fv t0 = { 5.0f, 12.0f };
	Vector3fv t1 = { 3.0f, 5.0f };
	float dot = Dot(t0, t1);
	EXPECT_NEAR(dot, (3.0f * 5.0f) + (5.0f * 12.0f), 0.01f);
}

TEST(Vector3fv, Magnitude_Reference)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::Reference::F32x4_2>;
	Vector3fv t0 = { 5.0f, 12.0f };
	float dot = Magnitude(t0);
	EXPECT_NEAR(dot, std::sqrt((5.0f * 5.0f) + (12.0f * 12.0f)), 0.01f);
}

TEST(Vector3fv, Magnitude_SSE4_1)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector3fv t0 = { 5.0f, 12.0f };
	float dot = Magnitude(t0);
	EXPECT_NEAR(dot, std::sqrt((5.0f * 5.0f) + (12.0f * 12.0f)), 0.01f);
}

TEST(Vector3fv, MagnitudeSq_Reference)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::Reference::F32x4_2>;
	Vector3fv t0 = { 5.0f, 12.0f };
	float dot = MagnitudeSq(t0);
	EXPECT_NEAR(dot, (5.0f * 5.0f) + (12.0f * 12.0f), 0.01f);
}

TEST(Vector3fv, MagnitudeSq_SSE4_1)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector3fv t0 = { 5.0f, 12.0f };
	float dot = MagnitudeSq(t0);
	EXPECT_NEAR(dot, (5.0f * 5.0f) + (12.0f * 12.0f), 0.01f);
}

TEST(Vector3fv, Normalize_Reference)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::Reference::F32x4_2>;
	Vector3fv t0 = { 5.0f, 12.0f };
	Vector3fv t1 = Normalize(t0);
	EXPECT_TRUE(Near(t1, { t0.x / Magnitude(t0), t0.y / Magnitude(t0) }, 0.01f));
}

TEST(Vector3fv, Normalize_SSE4_1)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector3fv t0 = { 5.0f, 12.0f };
	Vector3fv t1 = Normalize(t0);
	EXPECT_TRUE(Near(t1, { t0.x / Magnitude(t0), t0.y / Magnitude(t0) }, 0.01f));
}

TEST(Vector3fv, Reflect_Reference)
{
	using Type = Cpf::Math::Vector3v<Cpf::SIMD::Reference::F32x4_2>;
	Type t0 = { 1.0f, 0.0f };
	Type t1 = { 0.0f, 1.0f };
	Type t3 = Reflect(t0, t1);
	EXPECT_TRUE(Near(t3, { 0.0f, -1.0f }, 0.01f));
}

TEST(Vector3fv, Reflect_SSE4_1)
{
	using Type = Cpf::Math::Vector3v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Type t0 = { 1.0f, 0.0f };
	Type t1 = { 0.0f, 1.0f };
	Type t3 = Reflect(t0, t1);
	EXPECT_TRUE(Near(t3, { 0.0f, -1.0f }, 0.01f));
}

TEST(Vector3fv, Reciprocal_Reference)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::Reference::F32x4_2>;
	Vector3fv t0 = { 5.0f, 12.0f };
	Vector3fv t1 = Reciprocal(t0);

	EXPECT_NEAR(t1.x, 1.0f / t0.x, 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / t0.y, 0.01f);
}
TEST(Vector3fv, Reciprocal_SSE4_1)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector3fv t0 = { 5.0f, 12.0f };
	Vector3fv t1 = Reciprocal(t0);

	EXPECT_NEAR(t1.x, 1.0f / t0.x, 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / t0.y, 0.01f);
}

TEST(Vector3fv, RSqrt_Reference)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::Reference::F32x4_2>;
	Vector3fv t0 = { 5.0f, 12.0f };
	Vector3fv t1 = RSqrt(t0);

	EXPECT_NEAR(t1.x, 1.0f / std::sqrt(t0.x), 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / std::sqrt(t0.y), 0.01f);
}
TEST(Vector3fv, RSqrt_SSE4_1)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector3fv t0 = { 5.0f, 12.0f };
	Vector3fv t1 = RSqrt(t0);

	EXPECT_NEAR(t1.x, 1.0f / std::sqrt(t0.x), 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / std::sqrt(t0.y), 0.01f);
}

//////////////////////////////////////////////////////////////////////////
TEST(Vector3fv, Round_Truncate_Reference)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::Reference::F32x4_2>;
	Vector3fv t0 = { 5.25f, 12.85f };
	Vector3fv t1 = Round(t0, Cpf::SIMD::Rounding::eTruncate);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f }, 0.01f));
}
TEST(Vector3fv, Round_Truncate_SSE4_1)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector3fv t0 = { 5.25f, 12.85f };
	Vector3fv t1 = Round(t0, Cpf::SIMD::Rounding::eTruncate);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f }, 0.01f));
}

TEST(Vector3fv, Floor_Reference)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::Reference::F32x4_2>;
	Vector3fv t0 = { 5.25f, 12.85f };
	Vector3fv t1 = Floor(t0);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f }, 0.01f));
}
TEST(Vector3fv, Floor_SSE4_1)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector3fv t0 = { 5.25f, 12.85f };
	Vector3fv t1 = Floor(t0);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f }, 0.01f));
}

TEST(Vector3fv, Ceil_Reference)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::Reference::F32x4_2>;
	Vector3fv t0 = { 5.25f, 12.85f };
	Vector3fv t1 = Ceil(t0);

	EXPECT_TRUE(Near(t1, { 6.0f, 13.0f }, 0.01f));
}
TEST(Vector3fv, Ceil_SSE4_1)
{
	using Vector3fv = Cpf::Math::Vector3v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector3fv t0 = { 5.25f, 12.85f };
	Vector3fv t1 = Ceil(t0);

	EXPECT_TRUE(Near(t1, { 6.0f, 13.0f }, 0.01f));
}
#endif
