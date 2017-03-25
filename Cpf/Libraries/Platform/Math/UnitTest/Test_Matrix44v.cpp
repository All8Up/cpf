//////////////////////////////////////////////////////////////////////////
#include "SIMD.hpp"
#include "Math/Matrix44v.hpp"
#include "Math/Constants.hpp"
#include <gmock/gmock.h>

using namespace Cpf;
using namespace Math;

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_Matrix44 : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Cpf::SIMD::Reference::F32x4_4,
	Cpf::SIMD::SSE4_1::F32x4_4
> Data32_4_Types;

TYPED_TEST_CASE(TypedTest_Matrix44, Data32_4_Types);

TYPED_TEST(TypedTest_Matrix44, BasicConstruction)
{
	using Type = typename Matrix44<TypeParam>;
	using Element = typename TypeParam::Element;

	Type t0; // Garbage.
	Type t1(Element(0)); // Zero'd.
	EXPECT_TRUE(Near(t1[0], { Element(0), Element(0), Element(0), Element(0) }, 0.01f));
	EXPECT_TRUE(Near(t1[1], { Element(0), Element(0), Element(0), Element(0) }, 0.01f));
	EXPECT_TRUE(Near(t1[2], { Element(0), Element(0), Element(0), Element(0) }, 0.01f));
	EXPECT_TRUE(Near(t1[3], { Element(0), Element(0), Element(0), Element(0) }, 0.01f));

	Type t2(
		Element(1), Element(2), Element(3), Element(4),
		Element(5), Element(6), Element(7), Element(8),
		Element(9), Element(10), Element(11), Element(12),
		Element(13), Element(14), Element(15), Element(16)
		);
	EXPECT_TRUE(Near(t2[0], { Element(1), Element(2), Element(3), Element(4) }, 0.01f));
	EXPECT_TRUE(Near(t2[1], { Element(5), Element(6), Element(7), Element(8) }, 0.01f));
	EXPECT_TRUE(Near(t2[2], { Element(9), Element(10), Element(11), Element(12) }, 0.01f));
	EXPECT_TRUE(Near(t2[3], { Element(13), Element(14), Element(15), Element(16) }, 0.01f));
}
