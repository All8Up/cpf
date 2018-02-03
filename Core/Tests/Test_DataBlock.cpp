//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "CPF/DataBlock.hpp"
#include "CPF/DataBlockBuilder.hpp"
#include <memory>

using namespace CPF;

TEST(DataBlock, Basics)
{
	DataBlockBuilder builder;
	auto d0 = Vector<int64_t>{ 1, 2, 3, 4, 5 };
	builder.AddSection(SectionID(1), d0.data(), d0.size());
	
	std::shared_ptr<CPF::DataBlock> t0(builder.Create());
}
