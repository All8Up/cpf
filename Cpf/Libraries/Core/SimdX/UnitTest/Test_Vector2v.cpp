//////////////////////////////////////////////////////////////////////////
#include <gtest\gtest.h>
#include "SimdX.hpp"
#include "SIMD/Vector2v.hpp"

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_Vector2v : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Cpf::Math::Vector2v<Cpf::SIMD::Reference::F32x4_2>,
	Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::F32x4_2>,
	Cpf::Math::Vector2v<Cpf::SIMD::Reference::I32x4_2>,
	Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::I32x4_2>
> F32x4_1_Types;

TYPED_TEST_CASE(TypedTest_Vector2v, F32x4_1_Types);


TYPED_TEST(TypedTest_Vector2v, Construction)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = {Element(1), Element(2)};
	EXPECT_TRUE(Near(t0, { Element(1), Element(2) }, Element(0.01f)));

	Type t1(Element(3), Element(4));
	EXPECT_TRUE(Near(t1, { Element(3), Element(4) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector2v, ArrayAccess)
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

TYPED_TEST(TypedTest_Vector2v, OperatorAddAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	t0 += t1;

	EXPECT_TRUE((t0 == Type(Element(4), Element(6))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, OperatorSubtractAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	t0 -= t1;

	EXPECT_TRUE((t0 == Type(Element(-2), Element(-2))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, OperatorMultiplyAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	t0 *= t1;

	EXPECT_TRUE((t0 == Type(Element(3), Element(8))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, OperatorDivideAssign)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(12), Element(20) };
	Type t1 = { Element(3), Element(4) };
	t0 /= t1;

	EXPECT_TRUE((t0 == Type(Element(4), Element(5))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, OperatorNegate)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = -t0;

	EXPECT_TRUE(Near(t1, { Element(-1), Element(-2) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector2v, OperatorEquals)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 == Type(Element(1), Element(2))) == Type::kLaneMask);
	EXPECT_FALSE(t0 == t1);
}

TYPED_TEST(TypedTest_Vector2v, OperatorNotEquals)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_FALSE((t0 != Type(Element(1), Element(2))) == Type::kLaneMask);
	EXPECT_TRUE((t0 != t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, OperatorLessThan)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 < Type(Element(1), Element(2))) == 0);
	EXPECT_TRUE((t0 < t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, OperatorLessThanEqual)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 <= Type(Element(1), Element(2))) == Type::kLaneMask);
	EXPECT_TRUE((t0 <= t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, OperatorGreaterThan)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 > Type(Element(1), Element(2))) == 0);
	EXPECT_FALSE((t0 > t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, OperatorGreaterThanEqual)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };

	EXPECT_TRUE((t0 >= Type(Element(1), Element(2))) == Type::kLaneMask);
	EXPECT_FALSE((t0 >= t1) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, OperatorAdd)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = t0 + t1;

	EXPECT_TRUE((t2 == Type(Element(4), Element(6))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, OperatorSubtract)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = t0 - t1;

	EXPECT_TRUE((t2 == Type(Element(-2), Element(-2))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, OperatorMultiply)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = t0 * t1;

	EXPECT_TRUE(Near(t2, Type(Element(3), Element(8)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector2v, OperatorDevide)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = t0 / t1;

	EXPECT_TRUE((t2 == Type(Element(1.0f/3.0f), Element(2.0f/4.0f))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, Min)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = Min(t0, t1);

	EXPECT_TRUE((t2 == Type(Element(1.0f), Element(2.0f))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, HMin)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = HMin(t0);

	EXPECT_TRUE(t1.x == Element(1));
}

TYPED_TEST(TypedTest_Vector2v, Max)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = { Element(3), Element(4) };
	Type t2 = Max(t0, t1);

	EXPECT_TRUE((t2 == Type(Element(3.0f), Element(4.0f))) == Type::kLaneMask);
}

TYPED_TEST(TypedTest_Vector2v, HMax)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(1), Element(2) };
	Type t1 = HMax(t0);

	EXPECT_TRUE(t1.x == Element(2));
}

TYPED_TEST(TypedTest_Vector2v, Sqrt)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(9), Element(25) };
	Type t1 = Sqrt(t0);

	EXPECT_TRUE(t1.x == Element(3));
	EXPECT_TRUE(t1.y == Element(5));
}

TYPED_TEST(TypedTest_Vector2v, Clamp)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;

	Type t0 = { Element(9), Element(25) };
	Type t1 = Clamp(t0, Element(12), Element(16));

	EXPECT_TRUE(t1.x == Element(12));
	EXPECT_TRUE(t1.y == Element(16));
}

// NOTE: Next items only make sense for floating point.
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

