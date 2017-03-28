//////////////////////////////////////////////////////////////////////////
#include "Math/Quaternion.hpp"
#include "Math/Constants.hpp"
#include "Math/Vector3v.hpp"
#include "SIMD.hpp"
#include <gmock/gmock.h>

//////////////////////////////////////////////////////////////////////////
using namespace Cpf;
using namespace SIMD;
using namespace Math;

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_Quaternion : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Reference::F32x4_4,
	SSE4_1::F32x4_4
> Data32_2_Types;

TYPED_TEST_CASE(TypedTest_Quaternion, Data32_2_Types);


//////////////////////////////////////////////////////////////////////////
TYPED_TEST(TypedTest_Quaternion, Construction)
{
	using Type = Quaternion<typename TypeParam>;

	Type t0;  // Should be garbage.
	Type t1(0.0f);  // Should be all zeros.  Not sure this makes sense for quaternions.
	Type t2(0.0f, 0.0f, 0.0f, 1.0f);  // Identity.

	EXPECT_NEAR(t1.x, 0.0f, 0.01f);
	EXPECT_NEAR(t1.y, 0.0f, 0.01f);
	EXPECT_NEAR(t1.z, 0.0f, 0.01f);
	EXPECT_NEAR(t1.w, 0.0f, 0.01f);

	EXPECT_NEAR(t2.x, 0.0f, 0.01f);
	EXPECT_NEAR(t2.y, 0.0f, 0.01f);
	EXPECT_NEAR(t2.z, 0.0f, 0.01f);
	EXPECT_NEAR(t2.w, 1.0f, 0.01f);
}

TYPED_TEST(TypedTest_Quaternion, AxisAngle)
{
	using Type = Quaternion<typename TypeParam>;
	Vector3v<typename Type::Type::Lanes_3> axis(0.0f, 1.0f, 0.0f);
	Type t0 = Type::AxisAngle(axis, 0.0f);
	EXPECT_NEAR(t0.x, 0.0f, 0.01f);
	EXPECT_NEAR(t0.y, 0.0f, 0.01f);
	EXPECT_NEAR(t0.z, 0.0f, 0.01f);
	EXPECT_NEAR(t0.w, 1.0f, 0.01f);
}
