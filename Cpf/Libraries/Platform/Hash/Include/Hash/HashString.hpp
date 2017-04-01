//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Hash/Hash.hpp"
#include "Hash/Crc.hpp"
#include "Functional.hpp"

namespace Cpf
{
	namespace Hash
	{
		//////////////////////////////////////////////////////////////////////////
		struct CPF_EXPORT_HASH BaseHashString_Tag {};

		//////////////////////////////////////////////////////////////////////////
		template <typename TAG = BaseHashString_Tag>
		class CPF_EXPORT_HASH HashString
		{
		public:
			constexpr HashString();
			constexpr HashString(HashString&& rhs) noexcept;
			constexpr HashString(const char* string, size_t length);
			explicit constexpr HashString(uint64_t ID, const char* string);
			constexpr HashString(const HashString& rhs) noexcept;

			const HashString& operator = (const HashString& rhs);
			const HashString& operator = (const HashString&& rhs);

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


constexpr Cpf::Hash::HashString<Cpf::Hash::BaseHashString_Tag> operator "" _hashString(const char* val, size_t idx)
{
	return Cpf::Hash::HashString<Cpf::Hash::BaseHashString_Tag>(val, idx);
}

namespace CPF_STL_NAMESPACE
{
	template <typename TAG>
	struct hash<Cpf::Hash::HashString<TAG>>
	{
		size_t operator ()(const Cpf::Hash::HashString<TAG>& id) const
		{
			return id.GetID();
		}
	};
}
