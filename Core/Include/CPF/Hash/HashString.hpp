//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Hash/Crc.hpp"
#include "CPF/Std/Functional.hpp"

namespace CPF
{
	namespace Hash
	{
		//////////////////////////////////////////////////////////////////////////
		class HashString
		{
		public:
			constexpr HashString();
			constexpr HashString(HashString&& rhs) noexcept;
			HashString(const char* string);
			constexpr HashString(const char* string, size_t length);
			explicit constexpr HashString(uint64_t ID, const char* string);
			constexpr HashString(const HashString& rhs) noexcept = default;

			HashString& operator = (const HashString& rhs) = default;
			HashString& operator = (HashString&& rhs) noexcept;

			bool operator == (const HashString& rhs) const;
			bool operator != (const HashString& rhs) const;
			bool operator < (const HashString& rhs) const;
			bool operator <= (const HashString& rhs) const;
			bool operator > (const HashString& rhs) const;
			bool operator >= (const HashString& rhs) const;

			constexpr const char* GetString() const;
			constexpr uint64_t GetID() const;

		private:
			const char* mpString;
			uint64_t mID;
		};

		//////////////////////////////////////////////////////////////////////////
		inline constexpr HashString::HashString()
			: mpString(nullptr)
			, mID(uint64_t(-1))
		{}

		inline constexpr HashString::HashString(HashString&& rhs) noexcept
			: mpString(rhs.mpString)
			, mID(rhs.mID)
		{}

		inline HashString::HashString(const char* string)
			: mpString(string)
			, mID(Std::StrLen(string))
		{}

		inline constexpr HashString::HashString(const char* string, size_t length)
			: mpString(string)
			, mID(Crc64(string, length))
		{}

		inline constexpr HashString::HashString(uint64_t ID, const char* string)
			: mpString(string)
			, mID(ID)
		{}

		inline HashString& HashString::operator = (HashString&& rhs) noexcept
		{
			mpString = rhs.mpString;
			mID = rhs.mID;
			rhs.mpString = nullptr;
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

		inline constexpr const char* HashString::GetString() const
		{
			return mpString;
		}
		
		inline constexpr uint64_t HashString::GetID() const
		{
			return mID;
		}

		//////////////////////////////////////////////////////////////////////////
		inline constexpr HashString Create(HashString&& rhs)
		{
			return HashString(rhs.GetID(), rhs.GetString());
		}
	}
}


inline constexpr CPF::Hash::HashString operator "" _hashString(const char* val, size_t idx)
{
	return CPF::Hash::HashString{ val, idx };
}

namespace std
{
	template <>
	struct hash<CPF::Hash::HashString>
	{
		size_t operator ()(const CPF::Hash::HashString& id) const
		{
			return id.GetID();
		}
	};
}
