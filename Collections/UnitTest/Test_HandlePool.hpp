//////////////////////////////////////////////////////////////////////////
#pragma once
#include <HandlePool.hpp>


TEST(Collections, HandleValue)
{
	class TestObject
	{
	public:
		TestObject(int i) : mData(i) {}

		int mData;
	};

	TestObject obj1(0);
	TestObject obj2(1);

	using HandleType = Cpf::HandlePool<TestObject, 2>;
	HandleType testHandles;

	// Make sure we can alloc/free handles over and over.
	for (auto i = 0; i < 10; ++i)
	{
		auto hdl1 = testHandles.Alloc(&obj1);
		auto hdl2 = testHandles.Alloc(&obj2);

		EXPECT_EQ(&obj1, testHandles.Get(hdl1));
		EXPECT_EQ(&obj2, testHandles.Get(hdl2));

		testHandles.Free(hdl1);
		testHandles.Free(hdl2);

		EXPECT_EQ(nullptr, testHandles.Get(hdl1));
		EXPECT_EQ(nullptr, testHandles.Get(hdl2));

		auto hdl3 = testHandles.Alloc(&obj1);
		auto hdl4 = testHandles.Alloc(&obj2);

		EXPECT_EQ(nullptr, testHandles.Get(hdl1));
		EXPECT_EQ(nullptr, testHandles.Get(hdl2));
		EXPECT_EQ(&obj1, testHandles.Get(hdl3));
		EXPECT_EQ(&obj2, testHandles.Get(hdl4));

		testHandles.Free(hdl3);
		testHandles.Free(hdl4);

		EXPECT_EQ(nullptr, testHandles.Get(hdl1));
		EXPECT_EQ(nullptr, testHandles.Get(hdl2));
		EXPECT_EQ(nullptr, testHandles.Get(hdl3));
		EXPECT_EQ(nullptr, testHandles.Get(hdl4));
	}
}


TEST(Collections, Handle)
{
	class TestObject
	{
	public:
		TestObject(int i) : mData(i) {}

		int mData;
	};

	TestObject obj1(0);
	TestObject obj2(1);

	using HandlePool = Cpf::HandlePool<TestObject, 2>;
	HandlePool testHandles;

	// Make sure we can alloc/free handles over and over.
	for (auto i = 0; i < 10; ++i)
	{
		auto hdl1(testHandles.Alloc(&obj1));
		auto hdl2(testHandles.Alloc(&obj2));

		// Mix the usages...
		EXPECT_EQ(&obj1, testHandles.Get(hdl1));
		EXPECT_EQ(&obj2, testHandles.Get(hdl2));

		testHandles.Free(hdl1);
		testHandles.Free(hdl2);

		EXPECT_EQ(nullptr, testHandles.Get(hdl1));
		EXPECT_EQ(nullptr, testHandles.Get(hdl2));

		auto hdl3 = testHandles.Alloc(&obj1);
		auto hdl4 = testHandles.Alloc(&obj2);

		EXPECT_EQ(nullptr, testHandles.Get(hdl1));
		EXPECT_EQ(nullptr, testHandles.Get(hdl2));
		EXPECT_EQ(&obj1, testHandles.Get(hdl3));
		EXPECT_EQ(&obj2, testHandles.Get(hdl4));

		testHandles.Free(hdl3);
		testHandles.Free(hdl4);

		EXPECT_EQ(nullptr, testHandles.Get(hdl1));
		EXPECT_EQ(nullptr, testHandles.Get(hdl2));
		EXPECT_EQ(nullptr, testHandles.Get(hdl3));
		EXPECT_EQ(nullptr, testHandles.Get(hdl4));
	}
}
