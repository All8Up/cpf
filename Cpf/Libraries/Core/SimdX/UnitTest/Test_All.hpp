//////////////////////////////////////////////////////////////////////////
#include <gtest\gtest.h>
#include "SimdX.hpp"

TEST(SimdX, Float32x1)
{
	using namespace Cpf;
	using namespace SIMD;

	Float32x1 a = 1.0f;
	EXPECT_NEAR(a, 1.0f, 0.01f);
}
