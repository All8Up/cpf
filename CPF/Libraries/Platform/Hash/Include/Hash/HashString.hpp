//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Hash/Hash.hpp"
#include "Hash/Crc.hpp"
#include "Functional.hpp"

namespace CPF
{
	namespace Hash
	{
		//////////////////////////////////////////////////////////////////////////
		struct BaseHashString_Tag {};

		//////////////////////////////////////////////////////////////////////////
		template <typename TAG = BaseHashString_Tag>
		class HashString
		{
		public:
			constexpr HashString();
			constexpr HashString(HashString&& rhs) noexcept;
			constexpr HashString(const char* string, size_t length);
			explicit constexpr HashString(uint64_t ID, const char* string);
			constexpr HashString(const HashString& rhs) noexcept;

			template <typename RHS>
			explicit constexpr HashString(const HashString<RHS> rhs) noexcept;

			const HashString& operator = (const HashString& rhs);
			const HashString& operator = (const HashString&& rhs);
			template <typename RHS>
			constexpr HashString& operator = (const HashString<RHS> rhs);

			bool operator == (const HashString& rhs) const;
			bool operator != (const HashString& rhs) const;
			bool operator < (const HashString& rhs) const;
			bool operator <= (const HashString& rhs) const;
			bool operator > (const HashString& rhs) const;
			bool operator >= (const HashString& rhs) const;

			constexpr const char* GetString() const;
			constexpr uint64_t GetID() const;

			constexpr HashString Create(HashString&& rhs)
			{
				return HashString(rhs.GetID(), rhs.GetString());
			}

		private:
			const char* mpString;
			uint64_t mID;
		};

		//////////////////////////////////////////////////////////////////////////
		template <typename TAG>
		constexpr HashString<TAG>::HashString()
			: mpString(nullptr)
			, mID(uint64_t(-1))
		{}

		template <typename TAG>
		constexpr HashString<TAG>::HashString(HashString<TAG>&& rhs) noexcept
			: mpString(rhs.mpString)
			, mID(rhs.mID)
		{}

		template <typename TAG>
		constexpr HashString<TAG>::HashString(const char* string, size_t length)
			: mpString(string)
			, mID(Crc64(string, length))
		{}

		template <typename TAG>
		constexpr HashString<TAG>::HashString(uint64_t ID, const char* string)
			: mpString(string)
			, mID(ID)
		{}

		template <typename TAG>
		constexpr HashString<TAG>::HashString(const HashString<TAG>& rhs) noexcept
			: mpString(rhs.mpString)
			, mID(rhs.mID)
		{}

		template <typename TAG>
		const HashString<TAG>& HashString<TAG>::operator = (const HashString<TAG>& rhs)
		{
			mpString = rhs.mpString;
			mID = rhs.mID;
			return *this;
		}

		template <typename TAG>
		const HashString<TAG>& HashString<TAG>::operator = (const HashString<TAG>&& rhs)
		{
			mpString = rhs.mpString;
			mID = rhs.mID;
			return *this;
		}

		template <typename TAG>
		bool HashString<TAG>::operator == (const HashString<TAG>& rhs) const
		{
			return mID == rhs.mID;
		}

		template <typename TAG>
		bool HashString<TAG>::operator != (const HashString<TAG>& rhs) const
		{
			return mID != rhs.mID;
		}

		template <typename TAG>
		bool HashString<TAG>::operator < (const HashString<TAG>& rhs) const
		{
			return mID < rhs.mID;
		}

		template <typename TAG>
		bool HashString<TAG>::operator <= (const HashString<TAG>& rhs) const
		{
			return mID <= rhs.mID;
		}

		template <typename TAG>
		bool HashString<TAG>::operator > (const HashString<TAG>& rhs) const
		{
			return mID > rhs.mID;
		}

		template <typename TAG>
		bool HashString<TAG>::operator >= (const HashString<TAG>& rhs) const
		{
			return mID >= rhs.mID;
		}

		template <typename TAG>
		constexpr const char* HashString<TAG>::GetString() const
		{
			return mpString;
		}
		
		template <typename TAG>
		constexpr uint64_t HashString<TAG>::GetID() const
		{
			return mID;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TAG>
		constexpr HashString<TAG> Create(HashString<BaseHashString_Tag>&& rhs)
		{
			return HashString<TAG>(rhs.GetID(), rhs.GetString());
		}
	}
}


constexpr CPF::Hash::HashString<CPF::Hash::BaseHashString_Tag> operator "" _hashString(const char* val, size_t idx)
{
	return CPF::Hash::HashString<CPF::Hash::BaseHashString_Tag>(val, idx);
}

namespace CPF_STL_NAMESPACE
{
	template <typename TAG>
	struct hash<CPF::Hash::HashString<TAG>>
	{
		size_t operator ()(const CPF::Hash::HashString<TAG>& id) const
		{
			return id.GetID();
		}
	};
}
