//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Hash/HashID.hpp"

TEST(Hash, Basic_HashID)
{
	struct test_tag {};
	CPF::Hash::HashID<uint64_t, test_tag> test0("Test"_crc64);
}
