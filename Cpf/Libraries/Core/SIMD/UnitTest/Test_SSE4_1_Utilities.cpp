//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "SIMD.hpp"

TEST(SSE4_1_Utilities, Shuffle_F32x4)
{
	using namespace Cpf::SIMD;
	using TYPE = F32x4::StorageType;
	F32x4 t0(1, 2, 3, 4);
	F32x4 t1(5, 6, 7, 8);

	F32x4 r0 = SSE4_1::Shuffle<0, 0, 0, 0>(TYPE(t0), TYPE(t1));
	EXPECT_TRUE(Near(r0, {1, 1, 5, 5}, 0.1f));

	F32x4 r1 = SSE4_1::Shuffle<1, 1, 1, 1>(TYPE(t0), TYPE(t1));
	EXPECT_TRUE(Near(r1, { 2, 2, 6, 6 }, 0.1f));

	F32x4 r2 = SSE4_1::Shuffle<2, 2, 2, 2>(TYPE(t0), TYPE(t1));
	EXPECT_TRUE(Near(r2, { 3, 3, 7, 7 }, 0.1f));

	F32x4 r3 = SSE4_1::Shuffle<3, 3, 3, 3>(TYPE(t0), TYPE(t1));
	EXPECT_TRUE(Near(r3, { 4, 4, 8, 8 }, 0.1f));

	F32x4 r4 = SSE4_1::Shuffle<3, 2, 1, 0>(TYPE(t0), TYPE(t1));
	EXPECT_TRUE(Near(r4, { 4, 3, 6, 5 }, 0.1f));
}

TEST(SSE4_1_Utilities, Swizzle_F32x4)
{
	using namespace Cpf::SIMD;
	using TYPE = F32x4::StorageType;
	F32x4 t0(1, 2, 3, 4);

	F32x4 r0 = SSE4_1::Swizzle<0, 0, 0, 0>(TYPE(t0));
	EXPECT_TRUE(Near(r0, { 1, 1, 1, 1 }, 0.1f));

	F32x4 r1 = SSE4_1::Swizzle<1, 1, 1, 1>(TYPE(t0));
	EXPECT_TRUE(Near(r1, { 2, 2, 2, 2 }, 0.1f));

	F32x4 r2 = SSE4_1::Swizzle<2, 2, 2, 2>(TYPE(t0));
	EXPECT_TRUE(Near(r2, { 3, 3, 3, 3 }, 0.1f));

	F32x4 r3 = SSE4_1::Swizzle<3, 3, 3, 3>(TYPE(t0));
	EXPECT_TRUE(Near(r3, { 4, 4, 4, 4 }, 0.1f));

	F32x4 r4 = SSE4_1::Swizzle<3, 2, 1, 0>(TYPE(t0));
	EXPECT_TRUE(Near(r4, { 4, 3, 2, 1 }, 0.1f));
}
