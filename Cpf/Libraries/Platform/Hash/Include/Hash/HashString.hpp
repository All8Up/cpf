//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Hash/Crc.hpp"
#include "Functional.hpp"

namespace Cpf
{
	namespace Hash
	{
		//////////////////////////////////////////////////////////////////////////
		class HashString
		{
		public:
			constexpr HashString();
			constexpr HashString(HashString&& rhs) noexcept;
			constexpr HashString(const char* string, size_t length);
			constexpr HashString(const HashString& rhs) noexcept;

			const HashString& operator = (const HashString& rhs);
			const HashString& operator = (const HashString&& rhs);

			bool operator == (const HashString& rhs) const;
			bool operator != (const HashString& rhs) const;
			bool operator < (const HashString& rhs) const;
			bool operator <= (const HashString& rhs) const;
			bool operator > (const HashString& rhs) const;
			bool operator >= (const HashString& rhs) const;

			const char* GetString() const;
			uint64_t GetID() const;

		private:
			const char* mpString;
			uint64_t mID;
		};

		//////////////////////////////////////////////////////////////////////////
		constexpr HashString::HashString()
			: mpString(nullptr)
			, mID(uint64_t(-1))
		{}

		constexpr HashString::HashString(HashString&& rhs) noexcept
			: mpString(rhs.mpString)
			, mID(rhs.mID)
		{}

		constexpr HashString::HashString(const char* string, size_t length)
			: mpString(string)
			, mID(Crc64(string, length))
		{}

		constexpr HashString::HashString(const HashString& rhs) noexcept
			: mpString(rhs.mpString)
			, mID(rhs.mID)
		{}

		inline const HashString& HashString::operator = (const HashString& rhs)
		{
			mpString = rhs.mpString;
			mID = rhs.mID;
			return *this;
		}

		inline const HashString& HashString::operator = (const HashString&& rhs)
		{
			mpString = rhs.mpString;
			mID = rhs.mID;
			return *this;
		}

		inline bool HashString::operator == (const HashString& rhs) const
		{
			return mID == rhs.mID;
		}

		inline bool HashString::operator != (const HashString& rhs) const
		{
			return mID != rhs.mID;
		}

		inline bool HashString::operator < (const HashString& rhs) const
		{
			return mID < rhs.mID;
		}

		inline bool HashString::operator <= (const HashString& rhs) const
		{
			return mID <= rhs.mID;
		}

		inline bool HashString::operator > (const HashString& rhs) const
		{
			return mID > rhs.mID;
		}

		inline bool HashString::operator >= (const HashString& rhs) const
		{
			return mID >= rhs.mID;
		}

		inline const char* HashString::GetString() const
		{
			return mpString;
		}
		
		inline uint64_t HashString::GetID() const
		{
			return mID;
		}
	}
}


constexpr Cpf::Hash::HashString operator "" _hashString(const char* val, size_t idx)
{
	return Cpf::Hash::HashString(val, idx);
}

namespace CPF_STL_NAMESPACE
{
	template <>
	struct hash<Cpf::Hash::HashString>
	{
		size_t operator ()(const Cpf::Hash::HashString& id) const
		{
			return id.GetID();
		}
	};
}
