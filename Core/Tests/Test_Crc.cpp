#include <gtest/gtest.h>
#include "CPF/Hash/Crc.hpp"


//////////////////////////////////////////////////////////////////////////
TEST(Core, Crc32)
{
	uint32_t test = "test"_crc32;
	uint32_t test2 = CPF::Hash::Crc32("test", 4);
	EXPECT_EQ(test, 0xd87f7e0c);
	EXPECT_EQ(test2, 0xd87f7e0c);
}
