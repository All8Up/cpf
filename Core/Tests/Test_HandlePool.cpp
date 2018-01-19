#include <gtest/gtest.h>
#include "CPF/Std/HandlePool.hpp"

using namespace CPF;

TEST(HandlePool, BasicConstruction)
{
	HandlePool<> testData0;
	HandlePool<> testData1(10);
	HandlePool<> testData2(Move(testData0));
}

TEST(HandlePool, AddRemove)
{
	HandlePool<uint64_t, 4> testData;

	auto h0 = testData.Alloc(1);
	auto t0 = testData.Get(h0);
	EXPECT_EQ(t0, 1);

	auto h1 = testData.Alloc(2);
	auto t1 = testData.Get(h1);
	EXPECT_EQ(t1, 2);

	//
	testData.Free(h0);
	EXPECT_EQ(testData.Get(h0), uint32_t(-1));
}

TEST(HandlePool, HandleReuse)
{
	HandlePool<uint64_t, 4> testData;
	{
		auto h0 = testData.Alloc(0);
		auto h1 = testData.Alloc(1);
		auto h2 = testData.Alloc(2);
		auto h3 = testData.Alloc(3);

		EXPECT_EQ(testData.Get(h0), 0);
		EXPECT_EQ(testData.Get(h1), 1);
		EXPECT_EQ(testData.Get(h2), 2);
		EXPECT_EQ(testData.Get(h3), 3);

		testData.Free(h0);
		testData.Free(h1);
		testData.Free(h2);
		testData.Free(h3);

		EXPECT_EQ(testData.Get(h0), uint32_t(-1));
		EXPECT_EQ(testData.Get(h1), uint32_t(-1));
		EXPECT_EQ(testData.Get(h2), uint32_t(-1));
		EXPECT_EQ(testData.Get(h3), uint32_t(-1));
	}
	{
		auto h0 = testData.Alloc(4);
		auto h1 = testData.Alloc(5);
		auto h2 = testData.Alloc(6);
		auto h3 = testData.Alloc(7);

		EXPECT_EQ(testData.Get(h0), 4);
		EXPECT_EQ(testData.Get(h1), 5);
		EXPECT_EQ(testData.Get(h2), 6);
		EXPECT_EQ(testData.Get(h3), 7);

		testData.Free(h0);
		testData.Free(h1);
		testData.Free(h2);
		testData.Free(h3);

		EXPECT_EQ(testData.Get(h0), uint32_t(-1));
		EXPECT_EQ(testData.Get(h1), uint32_t(-1));
		EXPECT_EQ(testData.Get(h2), uint32_t(-1));
		EXPECT_EQ(testData.Get(h3), uint32_t(-1));
	}
}

TEST(HandlePool, HandleExpansion)
{
	HandlePool<uint64_t, 2> testData;
	{
		auto h0 = testData.Alloc(0);
		auto h1 = testData.Alloc(1);
		auto h2 = testData.Alloc(2);
		auto h3 = testData.Alloc(3);

		EXPECT_EQ(testData.Get(h0), 0);
		EXPECT_EQ(testData.Get(h1), 1);
		EXPECT_EQ(testData.Get(h2), 2);
		EXPECT_EQ(testData.Get(h3), 3);

		testData.Free(h0);
		testData.Free(h1);
		testData.Free(h2);
		testData.Free(h3);

		EXPECT_EQ(testData.Get(h0), uint32_t(-1));
		EXPECT_EQ(testData.Get(h1), uint32_t(-1));
		EXPECT_EQ(testData.Get(h2), uint32_t(-1));
		EXPECT_EQ(testData.Get(h3), uint32_t(-1));
	}
}

TEST(HandlePool, Prediction)
{
	HandlePool<uint64_t, 2> testData;
	auto p0 = testData.PredictHandle(0);
	auto p1 = testData.PredictHandle(1);
	auto p2 = testData.PredictHandle(2);
	auto p3 = testData.PredictHandle(3);

	auto a0 = testData.Alloc(0);
	auto a1 = testData.Alloc(0);
	auto a2 = testData.Alloc(0);
	auto a3 = testData.Alloc(0);

	EXPECT_EQ(p0, a0);
	EXPECT_EQ(p1, a1);
	EXPECT_EQ(p2, a2);
	EXPECT_EQ(p3, a3);
}
