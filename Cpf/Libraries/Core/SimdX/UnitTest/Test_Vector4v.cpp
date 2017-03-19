//////////////////////////////////////////////////////////////////////////
#include <gtest\gtest.h>
#include "SimdX.hpp"
#include "SIMD/Vector2v.hpp"
#include "SIMD/Vector4v.hpp"

//////////////////////////////////////////////////////////////////////////
using Vector4fv_SSE4_1 = Cpf::Math::Vector4v<Cpf::SIMD::SSE4_1::F32x4_4>;
using Vector4fv_Reference = Cpf::Math::Vector4v<Cpf::SIMD::Reference::F32x4_4>;

template <typename T>
class TypedTest_Vector4v : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Vector4fv_Reference,
	Vector4fv_SSE4_1,
	Cpf::Math::Vector4v<Cpf::SIMD::Reference::I32x4_4>,
	Cpf::Math::Vector4v<Cpf::SIMD::SSE4_1::I32x4_4>
> x32x4_1_Types;

TYPED_TEST_CASE(TypedTest_Vector4v, x32x4_1_Types);


TYPED_TEST(TypedTest_Vector4v, Construction)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	EXPECT_TRUE(Near(t0, { Element(1), Element(2), Element(3), Element(4) }, Element(0.01f)));

	Type t1(Element(3), Element(4), Element(5), Element(6));
	EXPECT_TRUE(Near(t1, { Element(3), Element(4), Element(5), Element(6) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector4v, ArrayAccess)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	EXPECT_NEAR(t0[0], Element(1), Element(0.01f));
	EXPECT_NEAR(t0[1], Element(2), Element(0.01f));
	EXPECT_NEAR(t0[2], Element(3), Element(0.01f));
	EXPECT_NEAR(t0[3], Element(4), Element(0.01f));

	t0[0] = Element(5);
	t0[1] = Element(7);
	t0[2] = Element(8);
	t0[3] = Element(9);
	EXPECT_NEAR(t0[0], Element(5), Element(0.01f));
	EXPECT_NEAR(t0[1], Element(7), Element(0.01f));
	EXPECT_NEAR(t0[2], Element(8), Element(0.01f));
	EXPECT_NEAR(t0[3], Element(9), Element(0.01f));
}

TYPED_TEST(TypedTest_Vector4v, OperatorAddAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };
	t0 += t1;

	EXPECT_TRUE((t0 == Type(Element(4), Element(6), Element(8), Element(10))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, OperatorSubtractAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };
	t0 -= t1;

	EXPECT_TRUE((t0 == Type(Element(-2), Element(-2), Element(-2), Element(-2))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, OperatorMultiplyAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };
	t0 *= t1;

	EXPECT_TRUE((t0 == Type(Element(3), Element(8), Element(15), Element(24))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, OperatorDivideAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(12), Element(20), Element(25), Element(30) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };
	t0 /= t1;

	EXPECT_TRUE((t0 == Type(Element(4), Element(5), Element(5), Element(5))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, OperatorNegate)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = -t0;

	EXPECT_TRUE(Near(t1, { Element(-1), Element(-2), Element(-3), Element(-4) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector4v, OperatorEquals)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };

	EXPECT_TRUE((t0 == Type(Element(1), Element(2), Element(3), Element(4))) == Type::kLaneMask);
	EXPECT_FALSE(t0 == t1);
}

TYPED_TEST(TypedTest_Vector4v, OperatorNotEquals)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };

	EXPECT_FALSE((t0 != Type(Element(1), Element(2), Element(3), Element(4))) == Type::kLaneMask);
	EXPECT_TRUE((t0 != t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, OperatorLessThan)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };

	EXPECT_TRUE((t0 < Type(Element(1), Element(2), Element(3), Element(4))) == 0);
	EXPECT_TRUE((t0 < t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, OperatorLessThanEqual)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };

	EXPECT_TRUE((t0 <= Type(Element(1), Element(2), Element(3), Element(4))) == Type::kLaneMask);
	EXPECT_TRUE((t0 <= t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, OperatorGreaterThan)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };

	EXPECT_TRUE((t0 > Type(Element(1), Element(2), Element(3), Element(4))) == 0);
	EXPECT_FALSE((t0 > t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, OperatorGreaterThanEqual)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };

	EXPECT_TRUE((t0 >= Type(Element(1), Element(2), Element(3), Element(4))) == Type::kLaneMask);
	EXPECT_FALSE((t0 >= t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, OperatorAdd)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };
	Type t2 = t0 + t1;

	EXPECT_TRUE((t2 == Type(Element(4), Element(6), Element(8), Element(10))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, OperatorSubtract)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };
	Type t2 = t0 - t1;

	EXPECT_TRUE((t2 == Type(Element(-2), Element(-2), Element(-2), Element(-2))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, OperatorMultiply)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };
	Type t2 = t0 * t1;

	EXPECT_TRUE(Near(t2, Type(Element(3), Element(8), Element(15), Element(24.0f)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector4v, OperatorDevide)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };
	Type t2 = t0 / t1;

	EXPECT_TRUE((t2 == Type(Element(1.0f / 3.0f), Element(2.0f / 4.0f), Element(3.0f / 5.0f), Element(4.0f / 6.0f))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, Min)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };
	Type t2 = Min(t0, t1);

	EXPECT_TRUE((t2 == Type(Element(1.0f), Element(2.0f), Element(3.0f), Element(4.0f))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, HMin)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Element t1 = HMin(t0);

	EXPECT_TRUE(t1 == Element(1));
}

TYPED_TEST(TypedTest_Vector4v, Max)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Type t1 = { Element(3), Element(4), Element(5), Element(6) };
	Type t2 = Max(t0, t1);

	EXPECT_TRUE((t2 == Type(Element(3.0f), Element(4.0f), Element(5.0f), Element(6.0f))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector4v, HMax)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2), Element(3), Element(4) };
	Element t1 = HMax(t0);

	EXPECT_TRUE(t1 == Element(4));
}

TYPED_TEST(TypedTest_Vector4v, Sqrt)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(9), Element(25), Element(36), Element(64) };
	Type t1 = Sqrt(t0);

	EXPECT_TRUE(t1.x == Element(3));
	EXPECT_TRUE(t1.y == Element(5));
	EXPECT_TRUE(t1.z == Element(6));
	EXPECT_TRUE(t1.w == Element(8));
}

TYPED_TEST(TypedTest_Vector4v, Clamp)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(9), Element(25), Element(4), Element(40) };
	Type t1 = Clamp(t0, Element(12), Element(16));

	EXPECT_TRUE(t1.x == Element(12));
	EXPECT_TRUE(t1.y == Element(16));
	EXPECT_TRUE(t1.z == Element(12));
	EXPECT_TRUE(t1.w == Element(16));
}


TYPED_TEST(TypedTest_Vector4v, Modulus)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;
	Type t0 = { Element(5.25f), Element(12.85f), Element(16.7f), Element(17.0f) };
	Type t1 = { Element(3.0f), Element(4.0f), Element(16), Element(17.0f) };
	Type t2 = Modulus(t0, t1);

	EXPECT_TRUE(Near(t2, { Element(2.25f), Element(0.85f), Element(0.7f), Element(0.0f) }, Element(0.01f)));
}

//////////////////////////////////////////////////////////////////////////
// NOTE: Next items only make sense for floating point.
template <typename T>
class TypedTest_Vector4fv : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Vector4fv_Reference,
	Vector4fv_SSE4_1
> F32x4_1_Types;

TYPED_TEST_CASE(TypedTest_Vector4fv, F32x4_1_Types);

TYPED_TEST(TypedTest_Vector4fv, Dot)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { 5.0f, 12.0f, 13.0f, 15.0f };
	Type t1 = { 3.0f, 5.0f, 6.0f, 7.0f };
	Element dot = Dot(t0, t1);
	EXPECT_NEAR(dot, (3.0f * 5.0f) + (5.0f * 12.0f) + (13.0f * 6.0f) + (15.0f * 7.0f), 0.01f);
}

TYPED_TEST(TypedTest_Vector4fv, Magnitude)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { 5.0f, 12.0f, 13.0f, 15.0f };
	Element dot = Magnitude(t0);
	EXPECT_NEAR(dot, std::sqrt((5.0f * 5.0f) + (12.0f * 12.0f) + (13.0f * 13.0f) + (15.0f * 15.0f)), 0.01f);
}

TYPED_TEST(TypedTest_Vector4fv, MagnitudeSq)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { 5.0f, 12.0f, 13.0f, 15.0f };
	float dot = MagnitudeSq(t0);
	EXPECT_NEAR(dot, (5.0f * 5.0f) + (12.0f * 12.0f) + (13.0f * 13.0f) + (15.0f * 15.0f), 0.01f);
}

TYPED_TEST(TypedTest_Vector4fv, Normalize)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { 5.0f, 12.0f, 13.0f, 15.0f };
	Type t1 = Normalize(t0);
	EXPECT_TRUE(Near(t1, { t0.x / Magnitude(t0), t0.y / Magnitude(t0), t0.z / Magnitude(t0), t0.w / Magnitude(t0) }, 0.01f));
}

TYPED_TEST(TypedTest_Vector4fv, Reciprocal)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { 5.0f, 12.0f, 15.0f, 16.0f };
	Type t1 = Reciprocal(t0);

	EXPECT_NEAR(t1.x, 1.0f / t0.x, 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / t0.y, 0.01f);
	EXPECT_NEAR(t1.z, 1.0f / t0.z, 0.01f);
	EXPECT_NEAR(t1.w, 1.0f / t0.w, 0.01f);
}

TYPED_TEST(TypedTest_Vector4fv, RSqrt)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { 5.0f, 12.0f, 15.0f, 16.0f };
	Type t1 = RSqrt(t0);

	EXPECT_NEAR(t1.x, 1.0f / std::sqrt(t0.x), 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / std::sqrt(t0.y), 0.01f);
	EXPECT_NEAR(t1.z, 1.0f / std::sqrt(t0.z), 0.01f);
	EXPECT_NEAR(t1.w, 1.0f / std::sqrt(t0.w), 0.01f);
}

//////////////////////////////////////////////////////////////////////////
TYPED_TEST(TypedTest_Vector4fv, Round_Truncate)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { 5.25f, 12.85f, 19.22f, 21.34f };
	Type t1 = Round(t0, Cpf::SIMD::Rounding::eTruncate);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f, 19.0f, 21.0f }, 0.01f));
}

TYPED_TEST(TypedTest_Vector4fv, Floor)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { 5.25f, 12.85f, 19.22f, 21.34f };
	Type t1 = Floor(t0);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f, 19.0f, 21.0f }, 0.01f));
}

TYPED_TEST(TypedTest_Vector4fv, Ceil)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { 5.25f, 12.85f, 19.22f, 21.34f };
	Type t1 = Ceil(t0);

	EXPECT_TRUE(Near(t1, { 6.0f, 13.0f, 20.0f, 22.0f }, 0.01f));
}
