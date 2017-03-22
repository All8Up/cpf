//////////////////////////////////////////////////////////////////////////
#include <gtest\gtest.h>
#include "SimdX.hpp"
#include "Math/Vector2v.hpp"

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_Vector2 : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Cpf::Math::Vector2v<Cpf::SIMD::Reference::F32x4_2>,
	Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::F32x4_2>,
	Cpf::Math::Vector2v<Cpf::SIMD::Reference::I32x4_2>,
	Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::I32x4_2>
> F32x4_1_Types;

TYPED_TEST_CASE(TypedTest_Vector2, F32x4_1_Types);


TYPED_TEST(TypedTest_Vector2, Construction)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = {Element(1), Element(2)};
	EXPECT_TRUE(Near(t0, { Element(1), Element(2) }, Element(0.01f)));

	Type t1(Element(3), Element(4));
	EXPECT_TRUE(Near(t1, { Element(3), Element(4) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector2, ArrayAccess)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	EXPECT_NEAR(t0[0], Element(1), Element(0.01f));
	EXPECT_NEAR(t0[1], Element(2), Element(0.01f));

	t0[0] = Element(5);
	t0[1] = Element(7);
	EXPECT_NEAR(t0[0], Element(5), Element(0.01f));
	EXPECT_NEAR(t0[1], Element(7), Element(0.01f));
}

TYPED_TEST(TypedTest_Vector2, ElementAccess)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;
	Type t0 = { Element(1), Element(2) };

	// NOTE: Have to cast it back to a vector type here to get the Near function to resolve.
	// This should not be a deal breaker since it will still resolve to vectors/refs in most other cases.
	EXPECT_TRUE(Near(Type(t0.xx), { Element(1), Element(1) }, Element(0.01f)));
	EXPECT_TRUE(Near(Type(t0.xy), { Element(1), Element(2) }, Element(0.01f)));
	EXPECT_TRUE(Near(Type(t0.yy), { Element(2), Element(2) }, Element(0.01f)));
	EXPECT_TRUE(Near(Type(t0.yx), { Element(2), Element(1) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector2, OperatorAddAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	t0 += t1;

	EXPECT_TRUE((t0 == Type(Element(4), Element(6))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2, OperatorSubtractAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	t0 -= t1;

	EXPECT_TRUE((t0 == Type(Element(-2), Element(-2))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2, OperatorMultiplyAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	t0 *= t1;

	EXPECT_TRUE((t0 == Type(Element(3), Element(8))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2, OperatorDivideAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(12), Element(20) };
	Type t1 = { Element(3), Element(4) };
	t0 /= t1;

	EXPECT_TRUE((t0 == Type(Element(4), Element(5))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2, OperatorNegate)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = -t0;

	EXPECT_TRUE(Near(t1, { Element(-1), Element(-2) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector2, OperatorEquals)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 == Type(Element(1), Element(2))) == Type::kLaneMask);
	EXPECT_FALSE(t0 == t1);
}

TYPED_TEST(TypedTest_Vector2, OperatorNotEquals)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_FALSE((t0 != Type(Element(1), Element(2))) == Type::kLaneMask);
	EXPECT_TRUE((t0 != t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2, OperatorLessThan)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 < Type(Element(1), Element(2))) == 0);
	EXPECT_TRUE((t0 < t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2, OperatorLessThanEqual)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 <= Type(Element(1), Element(2))) == Type::kLaneMask);
	EXPECT_TRUE((t0 <= t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2, OperatorGreaterThan)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 > Type(Element(1), Element(2))) == 0);
	EXPECT_FALSE((t0 > t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2, OperatorGreaterThanEqual)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 >= Type(Element(1), Element(2))) == Type::kLaneMask);
	EXPECT_FALSE((t0 >= t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2, OperatorAdd)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = t0 + t1;

	EXPECT_TRUE((t2 == Type(Element(4), Element(6))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2, OperatorSubtract)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = t0 - t1;

	EXPECT_TRUE((t2 == Type(Element(-2), Element(-2))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2, OperatorMultiply)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = t0 * t1;

	EXPECT_TRUE(Near(t2, Type(Element(3), Element(8)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector2, OperatorMultiplyScalar)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t2 = t0 * Element(2);

	EXPECT_TRUE(Near(t2, Type(Element(2), Element(4)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector2, OperatorScalarMultiply)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t2 = Element(2) * t0;

	EXPECT_TRUE(Near(t2, Type(Element(2), Element(4)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector2, OperatorDevide)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = t0 / t1;

	EXPECT_TRUE(Near(t2, Type(Element(1.0f / 3.0f), Element(2.0f / 4.0f)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector2, Min)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = Min(t0, t1);

	EXPECT_TRUE((t2 == Type(Element(1.0f), Element(2.0f))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2, HMin)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Element t1 = HMin(t0);

	EXPECT_TRUE(t1 == Element(1));
}

TYPED_TEST(TypedTest_Vector2, Max)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = Max(t0, t1);

	EXPECT_TRUE((t2 == Type(Element(3.0f), Element(4.0f))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2, HMax)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Element t1 = HMax(t0);

	EXPECT_TRUE(t1 == Element(2));
}

TYPED_TEST(TypedTest_Vector2, Sqrt)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(9), Element(25) };
	Type t1 = Sqrt(t0);

	EXPECT_TRUE(t1.x == Element(3));
	EXPECT_TRUE(t1.y == Element(5));
}

TYPED_TEST(TypedTest_Vector2, Clamp)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(9), Element(25) };
	Type t1 = Clamp(t0, Element(12), Element(16));

	EXPECT_TRUE(t1.x == Element(12));
	EXPECT_TRUE(t1.y == Element(16));
}


TYPED_TEST(TypedTest_Vector2, Modulus)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;
	Type t0 = { Element(5.25f), Element(12.85f) };
	Type t1 = { Element(3.0f), Element(4.0f) };
	Type t2 = Modulus(t0, t1);

	EXPECT_TRUE(Near(t2, { Element(2.25f), Element(0.85f) }, Element(0.01f)));
}


// NOTE: Next items only make sense for floating point.
TEST(Vector2fv, Dot_Reference)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::Reference::F32x4_2>;
	Vector2fv t0 = { 5.0f, 12.0f };
	Vector2fv t1 = { 3.0f, 5.0f };
	float dot = Dot(t0, t1);
	EXPECT_NEAR(dot, (3.0f * 5.0f) + (5.0f * 12.0f), 0.01f);
}

TEST(Vector2fv, Dot_SSE4_1)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector2fv t0 = { 5.0f, 12.0f };
	Vector2fv t1 = { 3.0f, 5.0f };
	float dot = Dot(t0, t1);
	EXPECT_NEAR(dot, (3.0f * 5.0f) + (5.0f * 12.0f), 0.01f);
}

TEST(Vector2fv, Magnitude_Reference)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::Reference::F32x4_2>;
	Vector2fv t0 = { 5.0f, 12.0f };
	float dot = Magnitude(t0);
	EXPECT_NEAR(dot, std::sqrt((5.0f * 5.0f) + (12.0f * 12.0f)), 0.01f);
}

TEST(Vector2fv, Magnitude_SSE4_1)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector2fv t0 = { 5.0f, 12.0f };
	float dot = Magnitude(t0);
	EXPECT_NEAR(dot, std::sqrt((5.0f * 5.0f) + (12.0f * 12.0f)), 0.01f);
}

TEST(Vector2fv, MagnitudeSq_Reference)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::Reference::F32x4_2>;
	Vector2fv t0 = { 5.0f, 12.0f };
	float dot = MagnitudeSq(t0);
	EXPECT_NEAR(dot, (5.0f * 5.0f) + (12.0f * 12.0f), 0.01f);
}

TEST(Vector2fv, MagnitudeSq_SSE4_1)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector2fv t0 = { 5.0f, 12.0f };
	float dot = MagnitudeSq(t0);
	EXPECT_NEAR(dot, (5.0f * 5.0f) + (12.0f * 12.0f), 0.01f);
}

TEST(Vector2fv, Normalize_Reference)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::Reference::F32x4_2>;
	Vector2fv t0 = { 5.0f, 12.0f };
	Vector2fv t1 = Normalize(t0);
	EXPECT_TRUE(Near(t1, {t0.x / Magnitude(t0), t0.y / Magnitude(t0)}, 0.01f));
}

TEST(Vector2fv, Normalize_SSE4_1)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector2fv t0 = { 5.0f, 12.0f };
	Vector2fv t1 = Normalize(t0);
	EXPECT_TRUE(Near(t1, { t0.x / Magnitude(t0), t0.y / Magnitude(t0) }, 0.01f));
}

TEST(Vector2fv, Reflect_Reference)
{
	using Type = Cpf::Math::Vector2v<Cpf::SIMD::Reference::F32x4_2>;
	Type t0 = { 1.0f, 0.0f };
	Type t1 = { 0.0f, 1.0f };
	Type t3 = Reflect(t0, t1);
	EXPECT_TRUE(Near(t3, {0.0f, -1.0f}, 0.01f));
}

TEST(Vector2fv, Reflect_SSE4_1)
{
	using Type = Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Type t0 = { 1.0f, 0.0f };
	Type t1 = { 0.0f, 1.0f };
	Type t3 = Reflect(t0, t1);
	EXPECT_TRUE(Near(t3, { 0.0f, -1.0f }, 0.01f));
}

TEST(Vector2fv, Reciprocal_Reference)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::Reference::F32x4_2>;
	Vector2fv t0 = { 5.0f, 12.0f };
	Vector2fv t1 = Reciprocal(t0);

	EXPECT_NEAR(t1.x, 1.0f / t0.x, 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / t0.y, 0.01f);
}
TEST(Vector2fv, Reciprocal_SSE4_1)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector2fv t0 = { 5.0f, 12.0f };
	Vector2fv t1 = Reciprocal(t0);

	EXPECT_NEAR(t1.x, 1.0f / t0.x, 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / t0.y, 0.01f);
}

TEST(Vector2fv, RSqrt_Reference)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::Reference::F32x4_2>;
	Vector2fv t0 = { 5.0f, 12.0f };
	Vector2fv t1 = RSqrt(t0);

	EXPECT_NEAR(t1.x, 1.0f / std::sqrt(t0.x), 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / std::sqrt(t0.y), 0.01f);
}
TEST(Vector2fv, RSqrt_SSE4_1)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector2fv t0 = { 5.0f, 12.0f };
	Vector2fv t1 = RSqrt(t0);

	EXPECT_NEAR(t1.x, 1.0f / std::sqrt(t0.x), 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / std::sqrt(t0.y), 0.01f);
}

//////////////////////////////////////////////////////////////////////////
TEST(Vector2fv, Round_Truncate_Reference)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::Reference::F32x4_2>;
	Vector2fv t0 = { 5.25f, 12.85f };
	Vector2fv t1 = Round(t0, Cpf::SIMD::Rounding::eTruncate);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f }, 0.01f));
}
TEST(Vector2fv, Round_Truncate_SSE4_1)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector2fv t0 = { 5.25f, 12.85f };
	Vector2fv t1 = Round(t0, Cpf::SIMD::Rounding::eTruncate);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f }, 0.01f));
}

TEST(Vector2fv, Floor_Reference)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::Reference::F32x4_2>;
	Vector2fv t0 = { 5.25f, 12.85f };
	Vector2fv t1 = Floor(t0);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f }, 0.01f));
}
TEST(Vector2fv, Floor_SSE4_1)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector2fv t0 = { 5.25f, 12.85f };
	Vector2fv t1 = Floor(t0);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f }, 0.01f));
}

TEST(Vector2fv, Ceil_Reference)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::Reference::F32x4_2>;
	Vector2fv t0 = { 5.25f, 12.85f };
	Vector2fv t1 = Ceil(t0);

	EXPECT_TRUE(Near(t1, { 6.0f, 13.0f }, 0.01f));
}
TEST(Vector2fv, Ceil_SSE4_1)
{
	using Vector2fv = Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::F32x4_2>;
	Vector2fv t0 = { 5.25f, 12.85f };
	Vector2fv t1 = Ceil(t0);

	EXPECT_TRUE(Near(t1, { 6.0f, 13.0f }, 0.01f));
}
