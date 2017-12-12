#include <gtest/gtest.h>
#include "CPF/Math.hpp"
#include "CPF/SIMD.hpp"
#include "CPF/Math/Matrix22v.hpp"
#include "CPF/Math/Constants.hpp"

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_Matrix22 : public::testing::Test
{
public:
};

typedef ::testing::Types <
	CPF::SIMD::Reference::F32x4_2,
	CPF::SIMD::SSE4_1::F32x4_2
> Data32_2_Types;

TYPED_TEST_CASE(TypedTest_Matrix22, Data32_2_Types);


TYPED_TEST(TypedTest_Matrix22, Construction)
{
	using Element = typename TypeParam::LaneType;
	using VType = CPF::Math::Vector2v<TypeParam>;
	using Type = CPF::Math::Matrix22<TypeParam>;

	Type t0;  // Should be a garbage type.
	Type t1(VType(Element(0.0f)), VType(Element(0.0f)));
	EXPECT_TRUE(Near(t1, Type(Element(0.0f)), Element(0.01f)));
	EXPECT_NEAR(t1[0][0], 0.0f, 0.01f);
	EXPECT_NEAR(t1[0][1], 0.0f, 0.01f);
	EXPECT_NEAR(t1[1][0], 0.0f, 0.01f);
	EXPECT_NEAR(t1[1][1], 0.0f, 0.01f);

	Type t2(Element(1.0f), Element(0.0f), Element(0.0f), Element(1.0f));
	EXPECT_NEAR(t2[0][0], 1.0f, 0.01f);
	EXPECT_NEAR(t2[0][1], 0.0f, 0.01f);
	EXPECT_NEAR(t2[1][0], 0.0f, 0.01f);
	EXPECT_NEAR(t2[1][1], 1.0f, 0.01f);
}

TYPED_TEST(TypedTest_Matrix22, Identity)
{
	using Type = CPF::Math::Matrix22<TypeParam>;
	using Element = typename TypeParam::LaneType;

	Type t0 = Type::Identity();
	EXPECT_TRUE(Near(t0, Type(Element(1), Element(0), Element(0), Element(1)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Matrix22, Rotation)
{
	using Type = CPF::Math::Matrix22<TypeParam>;
	using Element = typename TypeParam::LaneType;

	Type t0 = Type::Rotation(Element(CPF::Math::kDegToRad * 90.0f));
	EXPECT_TRUE(Near(t0, Type(Element(0), Element(-1), Element(1), Element(0)), Element(0.01f)));
}

TYPED_TEST(TypedTest_Matrix22, Scale)
{
	using Type = CPF::Math::Matrix22<TypeParam>;
	using Element = typename TypeParam::LaneType;

	Type t0 = Type::Scale(Element(0.5), Element(0.5));
	EXPECT_TRUE(Near(t0, Type(Element(0.5), Element(0.0), Element(0.0), Element(0.5)), Element(0.01f)));
}
