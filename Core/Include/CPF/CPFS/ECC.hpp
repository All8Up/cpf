//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"

namespace CPF
{
	namespace CPFS
	{
		enum ECC : uint64_t { eInvalid = uint64_t(-1) };

		constexpr ECC MakeECC(char a, char b, char c, char d, char e, char f, char g, char h)
		{
			return ECC(
				uint64_t(a) | (uint64_t(b) << 8) | (uint64_t(c) << 16) | (uint64_t(d) << 24) |
				(uint64_t(e) << 32) | (uint64_t(f) << 40) | (uint64_t(g) << 48) | (uint64_t(h) << 56) );
		}
	}
}
