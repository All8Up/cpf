//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Hash/HashID.hpp"

TEST(Hash, Basic_HashID)
{
	Cpf::Hash::HashID<uint64_t> test0("Test"_crc64);
}
