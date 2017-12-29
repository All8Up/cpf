#include <gtest/gtest.h>
#include "CPF/Std/IndexedPool.hpp"

using namespace CPF;

struct alignas(16) TestData
{
	int8_t mData0;
};

TEST(IndexedPool, BasicConstruction)
{
	IndexedPool<TestData> testData0;
	IndexedPool<TestData> testData1(10);
	IndexedPool<TestData> testData2(Move(testData0));
}

TEST(IndexedPool, AddRemoveAndAlignment)
{
	IndexedPool<TestData> testData;

	auto h0 = testData.Alloc({ 1 });
	auto t0 = testData.Get(h0);
	EXPECT_EQ(t0->mData0, 1);
	EXPECT_TRUE(intptr_t(t0) % 16 == 0);

	auto h1 = testData.Alloc({ 2 });
	auto t1 = testData.Get(h1);
	EXPECT_EQ(t1->mData0, 2);
	EXPECT_TRUE(intptr_t(t1) % 16 == 0);

	//
	testData.Free(h0);
	EXPECT_EQ(testData.Get(h0), nullptr);
	EXPECT_TRUE(testData.Get(h1)->mData0 == 2);
}

TEST(IndexedPool, HandleReuse)
{
	IndexedPool<TestData, 8> testData;
	{
		auto h0 = testData.Alloc({ 0 });
		auto h1 = testData.Alloc({ 1 });
		auto h2 = testData.Alloc({ 2 });
		auto h3 = testData.Alloc({ 3 });

		EXPECT_EQ(testData.Get(h0)->mData0, 0);
		EXPECT_EQ(testData.Get(h1)->mData0, 1);
		EXPECT_EQ(testData.Get(h2)->mData0, 2);
		EXPECT_EQ(testData.Get(h3)->mData0, 3);

		testData.Free(h0);
		testData.Free(h1);
		testData.Free(h2);
		testData.Free(h3);

		EXPECT_EQ(testData.Get(h0), nullptr);
		EXPECT_EQ(testData.Get(h1), nullptr);
		EXPECT_EQ(testData.Get(h2), nullptr);
		EXPECT_EQ(testData.Get(h3), nullptr);
	}
	{
		auto h0 = testData.Alloc({ 4 });
		auto h1 = testData.Alloc({ 5 });
		auto h2 = testData.Alloc({ 6 });
		auto h3 = testData.Alloc({ 7 });

		EXPECT_EQ(testData.Get(h0)->mData0, 4);
		EXPECT_EQ(testData.Get(h1)->mData0, 5);
		EXPECT_EQ(testData.Get(h2)->mData0, 6);
		EXPECT_EQ(testData.Get(h3)->mData0, 7);

		testData.Free(h0);
		testData.Free(h1);
		testData.Free(h2);
		testData.Free(h3);

		EXPECT_EQ(testData.Get(h0), nullptr);
		EXPECT_EQ(testData.Get(h1), nullptr);
		EXPECT_EQ(testData.Get(h2), nullptr);
		EXPECT_EQ(testData.Get(h3), nullptr);
	}
}

TEST(IndexedPool, HandleExpansion)
{
	IndexedPool<TestData, 2> testData;
	{
		auto h0 = testData.Alloc({ 0 });
		auto h1 = testData.Alloc({ 1 });
		auto h2 = testData.Alloc({ 2 });
		auto h3 = testData.Alloc({ 3 });

		EXPECT_EQ(testData.Get(h0)->mData0, 0);
		EXPECT_EQ(testData.Get(h1)->mData0, 1);
		EXPECT_EQ(testData.Get(h2)->mData0, 2);
		EXPECT_EQ(testData.Get(h3)->mData0, 3);

		testData.Free(h0);
		testData.Free(h1);
		testData.Free(h2);
		testData.Free(h3);

		EXPECT_EQ(testData.Get(h0), nullptr);
		EXPECT_EQ(testData.Get(h1), nullptr);
		EXPECT_EQ(testData.Get(h2), nullptr);
		EXPECT_EQ(testData.Get(h3), nullptr);
	}
}
