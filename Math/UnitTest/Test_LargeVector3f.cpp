//////////////////////////////////////////////////////////////////////////
#include "Math/LargeVector3f.hpp"
#include "Math/Morton.hpp"
#include <gmock/gmock.h>

using namespace Cpf;
using namespace Math;

TEST(Math, LargeVector3f_Construction)
{
	LargeVector3f testDefault;
	EXPECT_EQ(0.0f, testDefault.GetLocalPosition().x);
	EXPECT_EQ(0.0f, testDefault.GetLocalPosition().y);
	EXPECT_EQ(0.0f, testDefault.GetLocalPosition().z);
	EXPECT_EQ(0, testDefault.GetSpatialHash().GetCode());
}

TEST(Math, LargeVector3f_Wrapping)
{
	LargeVector3f testlg;

	EXPECT_EQ(SpatialEvent::eNone, testlg.SetLocalPosition(Vector3fv(0.0f)));
	EXPECT_EQ(0, testlg.GetSpatialHash().GetCode());

	// The unit test is configured for 8 unit sector sizes.
	if (LargeVector3f::kHalfSize == 8)
	{
		EXPECT_EQ(SpatialEvent::eModified, testlg.SetLocalPosition(Vector3fv(9.0f, 0.0f, 0.0f)));
		EXPECT_EQ(Morton32Encode(1, 0, 0), testlg.GetSpatialHash().GetCode());
		EXPECT_NEAR(testlg.GetLocalPosition().x, -7.0f, 0.01f);
		EXPECT_NEAR(testlg.GetLocalPosition().y, 0.0f, 0.01f);
		EXPECT_NEAR(testlg.GetLocalPosition().z, 0.0f, 0.01f);

		EXPECT_EQ(SpatialEvent::eModified, testlg.SetLocalPosition(Vector3fv(33.0f, 0.0f, 0.0f)));
		// Incremental with the prior test.  We are setting the local position relative to
		// the existing sector of 1, 0, 0 so two sectors to the 'right' of 1 == 3.
		EXPECT_EQ(Morton32Encode(3, 0, 0), testlg.GetSpatialHash().GetCode());
		EXPECT_NEAR(testlg.GetLocalPosition().x, 1.0f, 0.01f);
		EXPECT_NEAR(testlg.GetLocalPosition().y, 0.0f, 0.01f);
		EXPECT_NEAR(testlg.GetLocalPosition().z, 0.0f, 0.01f);

		Vector3fv testv = testlg.GetAbsolutePosition();
		EXPECT_NEAR(testv.x, 49.0f, 0.01f);
		EXPECT_NEAR(testv.y, 0.0f, 0.01f);
		EXPECT_NEAR(testv.z, 0.0f, 0.01f);
	}
}

TEST(Math, LargeVector3f_Relative)
{
	LargeVector3f zero;
	LargeVector3f target;
	target.SetLocalPosition(Vector3fv(31.0f, 22.0f, 14.0f));

	Vector3fv relative = target.GetRelativePosition(zero.GetSpatialHash());
	EXPECT_NEAR(relative.x, 31.0f, 0.01f);
	EXPECT_NEAR(relative.y, 22.0f, 0.01f);
	EXPECT_NEAR(relative.z, 14.0f, 0.01f);

	LargeVector3f one(Vector3fv(1.0f, 1.0f, 1.0f), 0);
	relative = target.GetVectorTo(one);
	EXPECT_NEAR(relative.x, 30.0f, 0.01f);
	EXPECT_NEAR(relative.y, 21.0f, 0.01f);
	EXPECT_NEAR(relative.z, 13.0f, 0.01f);
}
