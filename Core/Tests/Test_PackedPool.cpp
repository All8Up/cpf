//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "CPF/Std/PackedPool.hpp"

using namespace CPF;
using namespace STD;

TEST(PackedPool, Basics)
{
	PackedPool<uint64_t, int32_t, 2> t0;
	EXPECT_EQ(0, t0.GetSize());

	auto h0 = t0.Insert(1);
	EXPECT_NE(0, h0);
	auto h1 = t0.Insert(2);
	EXPECT_NE(0, h1);
	auto h2 = t0.Insert(3);
	EXPECT_NE(0, h2);

	EXPECT_EQ(1, *t0.Get(h0));
	EXPECT_EQ(2, *t0.Get(h1));
	EXPECT_EQ(3, *t0.Get(h2));

	t0.Erase(h1);
	EXPECT_EQ(1, *t0.Get(h0));
	EXPECT_EQ(nullptr, t0.Get(h1));
	EXPECT_EQ(3, *t0.Get(h2));
}

TEST(PackedPool, Iterator)
{
	PackedPool<uint64_t, int32_t> t0;
	for (int i = 0; i < 64; ++i)
		t0.Insert(i);

	int i = 0;
	for (auto& v : t0)
	{
		EXPECT_EQ(v.second, i++);
	}
}

TEST(PackedPool, ConstIterator)
{
	PackedPool<uint64_t, int32_t> t0;
	for (int i = 0; i < 64; ++i)
		t0.Insert(i);

	const PackedPool<uint64_t, int32_t>& t1 = t0;

	int i = 0;
	for (auto& v : t1)
	{
		EXPECT_EQ(v.second, i++);
	}
}
