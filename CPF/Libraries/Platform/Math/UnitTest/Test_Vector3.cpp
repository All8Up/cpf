//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "SIMD.hpp"
#include "Math/Vector2v.hpp"
#include "Math/Vector3v.hpp"
#include "SIMD/Detail/FPU/I32x3.hpp"

//////////////////////////////////////////////////////////////////////////
using Vector3f = CPF::Math::Vector3<CPF::SIMD::FPU::F32x3_3>;

template <typename T>
class TypedTest_Vector3_fpu : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Vector3f,
	CPF::Math::Vector3<CPF::SIMD::FPU::I32x3_3>
> F32x4_1_Types;

TYPED_TEST_CASE(TypedTest_Vector3_fpu, F32x4_1_Types);

TYPED_TEST(TypedTest_Vector3_fpu, SizeValidation)
{
	EXPECT_EQ(sizeof(TypeParam), sizeof(typename TypeParam::LaneType)*3);
}

TYPED_TEST(TypedTest_Vector3_fpu, Construction)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	EXPECT_TRUE(Near(t0, { Element(1), Element(2), Element(3) }, Element(0.01f)));

	TypeParam t1(Element(3), Element(4), Element(5));
	EXPECT_TRUE(Near(t1, { Element(3), Element(4), Element(5) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector3_fpu, ArrayAccess)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
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

TYPED_TEST(TypedTest_Vector3_fpu, ElementAccess)
{
	using Element = typename TypeParam::LaneType;
	TypeParam t0 = { Element(1), Element(2), Element(3) };

	// NOTE: Have to cast it back to a vector type here to get the Near function to resolve.
	// This should not be a deal breaker since it will still resolve to vectors/refs in most other cases.
	EXPECT_TRUE(Near(TypeParam(t0.xx, Element(0)), { Element(1), Element(1), Element(0) }, Element(0.01f)));
	EXPECT_TRUE(Near(TypeParam(t0.xy, Element(0)), { Element(1), Element(2), Element(0) }, Element(0.01f)));
	EXPECT_TRUE(Near(TypeParam(t0.yy, Element(0)), { Element(2), Element(2), Element(0) }, Element(0.01f)));
	EXPECT_TRUE(Near(TypeParam(t0.yx, Element(0)), { Element(2), Element(1), Element(0) }, Element(0.01f)));

	EXPECT_TRUE(Near(TypeParam(Element(0), t0.xx), { Element(0), Element(1), Element(1) }, Element(0.01f)));
	EXPECT_TRUE(Near(TypeParam(Element(0), t0.xy), { Element(0), Element(1), Element(2) }, Element(0.01f)));
	EXPECT_TRUE(Near(TypeParam(Element(0), t0.yy), { Element(0), Element(2), Element(2) }, Element(0.01f)));
	EXPECT_TRUE(Near(TypeParam(Element(0), t0.yx), { Element(0), Element(2), Element(1) }, Element(0.01f)));

	EXPECT_TRUE(Near(TypeParam(t0.xxx), { Element(1), Element(1), Element(1) }, Element(0.01f)));
	EXPECT_TRUE(Near(TypeParam(t0.xyx), { Element(1), Element(2), Element(1) }, Element(0.01f)));
	EXPECT_TRUE(Near(TypeParam(t0.yyz), { Element(2), Element(2), Element(3) }, Element(0.01f)));
	EXPECT_TRUE(Near(TypeParam(t0.zyx), { Element(3), Element(2), Element(1) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector3_fpu, MemoryLayout)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	Element* data = reinterpret_cast<Element*>(&t0);

	EXPECT_NEAR(Element(1), data[0], 0.0001f);
	EXPECT_NEAR(Element(2), data[1], 0.0001f);
	EXPECT_NEAR(Element(3), data[2], 0.0001f);
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorAddAssign)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };
	t0 += t1;

	EXPECT_TRUE(All(t0 == TypeParam(Element(4), Element(6), Element(8))));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorSubtractAssign)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };
	t0 -= t1;

	EXPECT_TRUE(All(t0 == TypeParam(Element(-2), Element(-2), Element(-2))));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorMultiplyAssign)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };
	t0 *= t1;

	EXPECT_TRUE(All(t0 == TypeParam(Element(3), Element(8), Element(15))));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorDivideAssign)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(12), Element(20), Element(25) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };
	t0 /= t1;

	EXPECT_TRUE(All(t0 == TypeParam(Element(4), Element(5), Element(5))));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorNegate)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = -t0;

	EXPECT_TRUE(Near(t1, { Element(-1), Element(-2), Element(-3) }, Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorEquals)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };

	EXPECT_TRUE(All(t0 == TypeParam(Element(1), Element(2), Element(3))));
	EXPECT_FALSE(Any(t0 == t1));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorNotEquals)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };

	EXPECT_FALSE(Any(t0 != TypeParam(Element(1), Element(2), Element(3))));
	EXPECT_TRUE(All(t0 != t1));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorLessThan)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };

	EXPECT_TRUE(None(t0 < TypeParam(Element(1), Element(2), Element(3))));
	EXPECT_TRUE(All(t0 < t1));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorLessThanEqual)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };

	EXPECT_TRUE(All(t0 <= TypeParam(Element(1), Element(2), Element(3))));
	EXPECT_TRUE(All(t0 <= t1));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorGreaterThan)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };

	EXPECT_TRUE(None(t0 > TypeParam(Element(1), Element(2), Element(3))));
	EXPECT_FALSE(All(t0 > t1));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorGreaterThanEqual)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };

	EXPECT_TRUE(All(t0 >= TypeParam(Element(1), Element(2), Element(3))));
	EXPECT_FALSE(All(t0 >= t1));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorAdd)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };
	TypeParam t2 = t0 + t1;

	EXPECT_TRUE(All(t2 == TypeParam(Element(4), Element(6), Element(8))));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorSubtract)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };
	TypeParam t2 = t0 - t1;

	EXPECT_TRUE(All(t2 == TypeParam(Element(-2), Element(-2), Element(-2))));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorMultiply)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };
	TypeParam t2 = t0 * t1;

	EXPECT_TRUE(Near(t2, TypeParam(Element(3), Element(8), Element(15)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorMultiplyScalar)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t2 = t0 * Element(2);

	EXPECT_TRUE(Near(t2, TypeParam(Element(2), Element(4), Element(6)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector3_fpu, OperatorScalarMultiply)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t2 = Element(2) * t0;

	EXPECT_TRUE(Near(t2, TypeParam(Element(2), Element(4), Element(6)), Element(0.01f)));
}

#if 0
TYPED_TEST(TypedTest_Vector3_fpu, OperatorDevide)
{
	using Type = typename TypeParam;
	using Element = typename Type::LaneType;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	Type t2 = t0 / t1;

	EXPECT_TRUE(Near(t2, Type(Element(1.0f / 3.0f), Element(2.0f / 4.0f), Element(3.0f / 5.0f)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Vector3_fpu, Min)
{
	using Type = typename TypeParam;
	using Element = typename Type::LaneType;

	Type t0 = { Element(1), Element(2), Element(3) };
	Type t1 = { Element(3), Element(4), Element(5) };
	Type t2 = Min(t0, t1);

	EXPECT_TRUE((t2 == Type(Element(1.0f), Element(2.0f), Element(3.0f))) == Type::LaneMask);
}
#endif

TYPED_TEST(TypedTest_Vector3_fpu, HMin)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	Element t1 = HMin(t0);

	EXPECT_TRUE(t1 == Element(1));
}

TYPED_TEST(TypedTest_Vector3_fpu, Max)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	TypeParam t1 = { Element(3), Element(4), Element(5) };
	TypeParam t2 = Max(t0, t1);

	EXPECT_TRUE(All(t2 == TypeParam(Element(3.0f), Element(4.0f), Element(5.0f))));
}

TYPED_TEST(TypedTest_Vector3_fpu, HMax)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(1), Element(2), Element(3) };
	Element t1 = HMax(t0);

	EXPECT_TRUE(t1 == Element(3));
}

TYPED_TEST(TypedTest_Vector3_fpu, Sqrt)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(9), Element(25), Element(36) };
	TypeParam t1 = Sqrt(t0);

	EXPECT_TRUE(t1.x == Element(3));
	EXPECT_TRUE(t1.y == Element(5));
	EXPECT_TRUE(t1.z == Element(6));
}

TYPED_TEST(TypedTest_Vector3_fpu, Clamp)
{
	using Element = typename TypeParam::LaneType;

	TypeParam t0 = { Element(9), Element(25), Element(4) };
	TypeParam t1 = Clamp(t0, Element(12), Element(16));

	EXPECT_TRUE(t1.x == Element(12));
	EXPECT_TRUE(t1.y == Element(16));
	EXPECT_TRUE(t1.z == Element(12));
}


TYPED_TEST(TypedTest_Vector3_fpu, Modulus)
{
	using Element = typename TypeParam::LaneType;
	TypeParam t0 = { Element(5.25f), Element(12.85f), Element(16.7f) };
	TypeParam t1 = { Element(3.0f), Element(4.0f), Element(16) };
	TypeParam t2 = Modulus(t0, t1);

	EXPECT_TRUE(Near(t2, { Element(2.25f), Element(0.85f), Element(0.7f) }, Element(0.01f)));
}

// NOTE: Next items only make sense for floating point.
TEST(Vector3f, Dot_Reference)
{
	using Vector3f = Vector3f;
	Vector3f t0 = { 5.0f, 12.0f, 13.0f };
	Vector3f t1 = { 3.0f, 5.0f, 6.0f };
	float dot = Dot(t0, t1);
	EXPECT_NEAR(dot, (3.0f * 5.0f) + (5.0f * 12.0f) + (13.0f * 6.0f), 0.01f);
}

TEST(Vector3f, Magnitude_Reference)
{
	using Vector3f = Vector3f;
	Vector3f t0 = { 5.0f, 12.0f, 13.0f };
	float dot = Magnitude(t0);
	EXPECT_NEAR(dot, std::sqrt((5.0f * 5.0f) + (12.0f * 12.0f) + (13.0f * 13.0f)), 0.01f);
}

TEST(Vector3f, MagnitudeSq_Reference)
{
	using Vector3f = Vector3f;
	Vector3f t0 = { 5.0f, 12.0f, 13.0f };
	float dot = MagnitudeSq(t0);
	EXPECT_NEAR(dot, (5.0f * 5.0f) + (12.0f * 12.0f) + (13.0f * 13.0f), 0.01f);
}

TEST(Vector3f, Normalize_Reference)
{
	using Vector3f = Vector3f;
	Vector3f t0 = { 5.0f, 12.0f, 13.0f };
	Vector3f t1 = Normalize(t0);
	EXPECT_TRUE(Near(t1, { t0.x / Magnitude(t0), t0.y / Magnitude(t0), t0.z / Magnitude(t0) }, 0.01f));
}

TEST(Vector3f, Reflect_Reference)
{
	using Type = Vector3f;
	Type t0 = { 1.0f, 0.0f, 0.0f };
	Type t1 = { 0.0f, 1.0f, 0.0f };
	Type t3 = Reflect(t0, t1);
	EXPECT_TRUE(Near(t3, { 0.0f, -1.0f, 0.0f }, 0.01f));
}

TEST(Vector3f, Reciprocal_Reference)
{
	using Vector3f = Vector3f;
	Vector3f t0 = { 5.0f, 12.0f, 15.0f };
	Vector3f t1 = Reciprocal(t0);

	EXPECT_NEAR(t1.x, 1.0f / t0.x, 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / t0.y, 0.01f);
	EXPECT_NEAR(t1.z, 1.0f / t0.z, 0.01f);
}

TEST(Vector3f, RSqrt_Reference)
{
	using Vector3f = Vector3f;
	Vector3f t0 = { 5.0f, 12.0f, 15.0f };
	Vector3f t1 = RSqrt(t0);

	EXPECT_NEAR(t1.x, 1.0f / std::sqrt(t0.x), 0.01f);
	EXPECT_NEAR(t1.y, 1.0f / std::sqrt(t0.y), 0.01f);
	EXPECT_NEAR(t1.z, 1.0f / std::sqrt(t0.z), 0.01f);
}

//////////////////////////////////////////////////////////////////////////
TEST(Vector3f, Round_Truncate_Reference)
{
	using Vector3f = Vector3f;
	Vector3f t0 = { 5.25f, 12.85f, 19.22f };
	Vector3f t1 = Round(t0, CPF::SIMD::Rounding::eTruncate);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f, 19.0f }, 0.01f));
}

TEST(Vector3f, Floor_Reference)
{
	using Vector3f = Vector3f;
	Vector3f t0 = { 5.25f, 12.85f, 19.22f };
	Vector3f t1 = Floor(t0);

	EXPECT_TRUE(Near(t1, { 5.0f, 12.0f, 19.0f }, 0.01f));
}

TEST(Vector3f, Ceil_Reference)
{
	using Vector3f = Vector3f;
	Vector3f t0 = { 5.25f, 12.85f, 19.22f };
	Vector3f t1 = Ceil(t0);

	EXPECT_TRUE(Near(t1, { 6.0f, 13.0f, 20.0f }, 0.01f));
}

TEST(Vector3f, Cross_Reference)
{
	using Vector3f = Vector3f;
	Vector3f t0 = { 1.0f, 0.0f, 0.0f };
	Vector3f t1 = { 0.0f, 1.0f, 0.0f };
	Vector3f t2 = Cross(t0, t1);

	EXPECT_TRUE(Near(t2, { 0.0f, 0.0f, 1.0f }, 0.01f));
}
