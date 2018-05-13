//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "CPF/STD/PoolVector.hpp"

TEST(STD, PackedIndexContainer_FreeList)
{
	using namespace CPF::STD;
	using Pool = PoolVector<int32_t, 4>;
	Pool test;
	EXPECT_EQ(test.Alloc(), Pool::Handle(0));
	test[Pool::Handle(0)] = 8;
	EXPECT_EQ(test.Alloc(), Pool::Handle(1));
	test[Pool::Handle(1)] = 7;
	EXPECT_EQ(test.Alloc(), Pool::Handle(2));
	test[Pool::Handle(2)] = 6;
	EXPECT_EQ(test.Alloc(), Pool::Handle(3));
	test[Pool::Handle(3)] = 5;

	// Should trigger an expansion.
	EXPECT_EQ(test.Alloc(), Pool::Handle(4));
	test[Pool::Handle(4)] = 4;
	EXPECT_EQ(test.Alloc(), Pool::Handle(5));
	test[Pool::Handle(5)] = 3;
	EXPECT_EQ(test.Alloc(), Pool::Handle(6));
	test[Pool::Handle(6)] = 2;
	EXPECT_EQ(test.Alloc(), Pool::Handle(7));
	test[Pool::Handle(7)] = 1;

	// Free out of order.
	test.Free(Pool::Handle(4));
	test.Free(Pool::Handle(3));

	test.Free(Pool::Handle(5));
	test.Free(Pool::Handle(6));

	test.Free(Pool::Handle(0));

	test.Free(Pool::Handle(7));
	test.Free(Pool::Handle(1));

	test.Free(Pool::Handle(2));
}
