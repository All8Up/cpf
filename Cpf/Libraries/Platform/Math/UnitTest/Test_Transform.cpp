//////////////////////////////////////////////////////////////////////////
#include "gmock/gmock.h"
#include "Math/Transform.hpp"
#include "Math/Constants.hpp"

using namespace Cpf;
using namespace Math;

TEST(Math, Transform)
{
	Transform test;
	EXPECT_EQ(test.GetOrientation(), Quaternionfv::Identity());
	EXPECT_EQ(test.GetScale(), Vector3fv(1.0f));
	EXPECT_EQ(test.GetTranslation(), Vector3fv(0.0f));
}

TEST(Math, Transform_Multiplication)
{
	Transform test0(
		Quaternionfv::AxisAngle(Vector3fv(0.0f, 1.0f, 0.0f), kDegToRad * 90.0f)
	);	// Identity.
	Transform test1(
		Quaternionfv::Identity(),
		Vector3fv(0.5f),
		Vector3fv(1.0f, 0.0f, 0.0f)
	);
	Transform result = test0 * test1;

	EXPECT_EQ(result.GetScale(), Vector3fv(0.5f));
	EXPECT_NEAR(result.GetTranslation().z, -1.0f, 0.01f);
}
