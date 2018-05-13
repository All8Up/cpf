//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "CPF/DataBlock.hpp"
#include "CPF/DataBlockBuilder.hpp"
#include <memory>

using namespace CPF;

TEST(DataBlock, Basics)
{
	DataBlockBuilder builder;
	auto d0 = STD::Vector<uint8_t>{ 1, 2, 3, 4, 5 };
	builder.AddSection(SectionID(1), d0.data(), d0.size()*sizeof(uint8_t));

	auto d1 = STD::Vector<uint64_t>{ 5, 4, 3, 2, 1 };
	builder.AddSection(SectionID(2), d1.data(), d1.size() * sizeof(uint64_t));

	DataBlock* t0(builder.Create());
	const auto* td0 = reinterpret_cast<const uint8_t*>(t0->GetSection(SectionID(1), nullptr));
	EXPECT_EQ(td0[0], 1);
	EXPECT_EQ(td0[1], 2);
	EXPECT_EQ(td0[2], 3);
	EXPECT_EQ(td0[3], 4);
	EXPECT_EQ(td0[4], 5);

	const auto* td1 = reinterpret_cast<const uint64_t*>(t0->GetSection(SectionID(2), nullptr));
	EXPECT_EQ(td1[0], 5);
	EXPECT_EQ(td1[1], 4);
	EXPECT_EQ(td1[2], 3);
	EXPECT_EQ(td1[3], 2);
	EXPECT_EQ(td1[4], 1);

	t0->Destroy();
}
