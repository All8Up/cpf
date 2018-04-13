//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include <CPF/Memory/ScratchAllocator.hpp>

using namespace CPF;
using namespace Memory;

TEST(ScratchAllocator, Basics)
{
	using Allocator = ScratchAllocator<>;
	using Handle = Allocator::Handle;

	Allocator testAllocator;
	EXPECT_EQ(testAllocator.Size(), 0);
	EXPECT_EQ(testAllocator.Capacity(), Allocator::kInitSize);

	EXPECT_EQ(testAllocator.Alloc(10), Handle(0));
	EXPECT_EQ(testAllocator.Alloc(10), Handle(Allocator::kAlignment));

	EXPECT_EQ(testAllocator.Data(), testAllocator.Get(Handle(0)));
	EXPECT_EQ(reinterpret_cast<uint8_t*>(testAllocator.Data()) + Allocator::kAlignment, testAllocator.Get(Handle(16)));
}

TEST(ScratchAllocator, Grow)
{
	using Allocator = ScratchAllocator<32, 32>;
	using Handle = Allocator::Handle;

	Allocator testAllocator;
	EXPECT_EQ(testAllocator.Size(), 0);
	EXPECT_EQ(testAllocator.Capacity(), Allocator::kInitSize);

	EXPECT_EQ(testAllocator.Alloc(10), Handle(0));
	EXPECT_EQ(testAllocator.Data(), testAllocator.Get(Handle(0)));
	EXPECT_EQ(testAllocator.Size(), 32);
	EXPECT_EQ(testAllocator.Capacity(), 32);
	CSTD::MemSet(testAllocator.Get(Handle(0)), 1, 10);

	EXPECT_EQ(testAllocator.Alloc(10), Handle(32));
	EXPECT_EQ(reinterpret_cast<uint8_t*>(testAllocator.Data()) + Allocator::kAlignment, testAllocator.Get(Handle(32)));
	EXPECT_EQ(testAllocator.Size(), 64);
	EXPECT_EQ(testAllocator.Capacity(), 64);
	CSTD::MemSet(testAllocator.Get(Handle(32)), 2, 10);

	for (int i = 0; i < 64; i += 32)
	{
		const auto val = (i / 32) + 1;
		auto ptr = reinterpret_cast<uint8_t*>(testAllocator.Get(Handle(i)));
		for (int j = 0; j < 10; ++j)
		{
			EXPECT_EQ(val, *ptr++);
		}
	}
}
