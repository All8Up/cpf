//////////////////////////////////////////////////////////////////////////
#include "gmock/gmock.h"
#include "Math/Utilities.hpp"
#include "Math/Constants.hpp"

using namespace Cpf;
using namespace Math;

TEST(MathUtilities, RadiansBetween)
{
	Vector3fv start = Vector3fv::ZAxis();
	EXPECT_NEAR(RadiansBetween(start, start), 0.0f * kDegToRad, 0.01f);

	EXPECT_NEAR(RadiansBetween(start, start + Vector3fv::XAxis()), 45.0f * kDegToRad, 0.01f);
	EXPECT_NEAR(RadiansBetween(start, start - Vector3fv::XAxis()), 45.0f * kDegToRad, 0.01f);

	EXPECT_NEAR(RadiansBetween(start, Vector3fv::XAxis()), 90.0f * kDegToRad, 0.01f);
	EXPECT_NEAR(RadiansBetween(start, -Vector3fv::XAxis()), 90.0f * kDegToRad, 0.01f);

	EXPECT_NEAR(RadiansBetween(start, -start + Vector3fv::XAxis()), 135.0f * kDegToRad, 0.01f);
	EXPECT_NEAR(RadiansBetween(start, -start - Vector3fv::XAxis()), 135.0f * kDegToRad, 0.01f);
}

TEST(MathUtilities, AngleTo)
{
	Vector3fv start = Vector3fv::ZAxis();
	EXPECT_NEAR(ClosestRotationTo(start, start, Vector3fv::YAxis()), 0.0f, 0.01f);

	EXPECT_NEAR(ClosestRotationTo(start, start + Vector3fv::XAxis(), Vector3fv::YAxis()), 45.0f * kDegToRad, 0.01f);
	EXPECT_NEAR(ClosestRotationTo(start, start - Vector3fv::XAxis(), Vector3fv::YAxis()), -45.0f * kDegToRad, 0.01f);

	EXPECT_NEAR(ClosestRotationTo(start, Vector3fv::XAxis(), Vector3fv::YAxis()), 90.0f * kDegToRad, 0.01f);
	EXPECT_NEAR(ClosestRotationTo(start, -Vector3fv::XAxis(), Vector3fv::YAxis()), -90.0f * kDegToRad, 0.01f);

	EXPECT_NEAR(ClosestRotationTo(start, -start + Vector3fv::XAxis(), Vector3fv::YAxis()), 135.0f * kDegToRad, 0.01f);
	EXPECT_NEAR(ClosestRotationTo(start, -start - Vector3fv::XAxis(), Vector3fv::YAxis()), -135.0f * kDegToRad, 0.01f);
}

TEST(MathUtilities, DirectionTowards)
{
	Vector3fv start = Vector3fv::ZAxis();
	EXPECT_NEAR(DirectionTowards(start, start, Vector3fv::YAxis()), 0.0f, 0.01f);

	EXPECT_NEAR(DirectionTowards(start, start + Vector3fv::XAxis(), Vector3fv::YAxis()), 1.0f, 0.01f);
	EXPECT_NEAR(DirectionTowards(start, start - Vector3fv::XAxis(), Vector3fv::YAxis()), -1.0f, 0.01f);

	EXPECT_NEAR(DirectionTowards(start, Vector3fv::XAxis(), Vector3fv::YAxis()), 1.0f, 0.01f);
	EXPECT_NEAR(DirectionTowards(start, -Vector3fv::XAxis(), Vector3fv::YAxis()), -1.0f, 0.01f);

	EXPECT_NEAR(DirectionTowards(start, -start + Vector3fv::XAxis(), Vector3fv::YAxis()), 1.0f, 0.01f);
	EXPECT_NEAR(DirectionTowards(start, -start - Vector3fv::XAxis(), Vector3fv::YAxis()), -1.0f, 0.01f);
}

TEST(MathUtilities, HeadingOnAxis)
{
	Vector3fv v0 = HeadingOnAxis(0.0f, Vector3fv::YAxis());
	EXPECT_NEAR(v0.x, 0.0f, 0.01f);
	EXPECT_NEAR(v0.y, 0.0f, 0.01f);
	EXPECT_NEAR(v0.z, 1.0f, 0.01f);

	Vector3fv v45 = HeadingOnAxis(45.0f * kDegToRad, Vector3fv::YAxis());
	EXPECT_NEAR(v45.x, 0.7071f, 0.01f);
	EXPECT_NEAR(v45.y, 0.0f, 0.01f);
	EXPECT_NEAR(v45.z, 0.7071f, 0.01f);

	Vector3fv vn45 = HeadingOnAxis(-45.0f * kDegToRad, Vector3fv::YAxis());
	EXPECT_NEAR(vn45.x, -0.7071f, 0.01f);
	EXPECT_NEAR(vn45.y, 0.0f, 0.01f);
	EXPECT_NEAR(vn45.z, 0.7071f, 0.01f);
}
