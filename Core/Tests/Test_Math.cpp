//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "CPF/Math/Vector3v.hpp"

TEST(Math, TestNan)
{
	using namespace CPF;
	using namespace Math;

	Vector3fv inf(std::numeric_limits<float>::quiet_NaN());
	inf = inf * Vector3fv(0.0f);
	EXPECT_TRUE(All(inf != Vector3fv(0.0f)));
}
