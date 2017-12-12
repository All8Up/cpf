#include <gtest/gtest.h>
#include "CPF/Math.hpp"
#include "CPF/SIMD.hpp"
#include "CPF/Math/Vector3v.hpp"
#include "CPF/Math/Matrix33v.hpp"
#include "CPF/Math/Constants.hpp"

using namespace CPF;
using namespace Math;

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_Matrix33 : public::testing::Test
{
public:
};

typedef ::testing::Types <
	CPF::SIMD::Reference::F32x4_3,
	CPF::SIMD::SSE4_1::F32x4_3
> Data32_3_Types;

TYPED_TEST_CASE(TypedTest_Matrix33, Data32_3_Types);

TYPED_TEST(TypedTest_Matrix33, BasicConstruction)
{
	using Type = Matrix33<TypeParam>;
	using Element = typename TypeParam::LaneType;

	Type t0; // Garbage.
	Type t1(Element(0)); // Zero'd.
	EXPECT_TRUE(Near(t1[0], { Element(0), Element(0), Element(0) }, 0.01f));
	EXPECT_TRUE(Near(t1[1], { Element(0), Element(0), Element(0) }, 0.01f));
	EXPECT_TRUE(Near(t1[2], { Element(0), Element(0), Element(0) }, 0.01f));

	Type t2(
		Element(1), Element(2), Element(3),
		Element(4), Element(5), Element(6),
		Element(7), Element(8), Element(9)
		);
	EXPECT_TRUE(Near(t2[0], { Element(1), Element(2), Element(3) }, 0.01f));
	EXPECT_TRUE(Near(t2[1], { Element(4), Element(5), Element(6) }, 0.01f));
	EXPECT_TRUE(Near(t2[2], { Element(7), Element(8), Element(9) }, 0.01f));
}
