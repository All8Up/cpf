//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Hash/Crc.hpp"

namespace Cpf
{
	namespace Hash
	{
		class StringHash
		{
		public:
			constexpr StringHash(const char* string, size_t length);
			constexpr StringHash(StringHash&& rhs) noexcept;

			const char* GetString() const;
			uint64_t GetID() const;

			const char* String;
			const uint64_t ID;
		};

		constexpr StringHash::StringHash(const char* string, size_t length)
			: String(string)
			, ID(Crc64(string, length))
		{}

		constexpr StringHash::StringHash(StringHash&& rhs) noexcept
			: String(rhs.String)
			, ID(rhs.ID)
		{}
	}
}


constexpr Cpf::Hash::StringHash operator "" _stringHash(const char* val, size_t idx)
{
	return Cpf::Hash::StringHash(val, idx);
}
