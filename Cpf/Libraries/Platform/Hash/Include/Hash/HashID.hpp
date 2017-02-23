//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Hash/Crc.hpp"
#include "String.hpp"

namespace Cpf
{
	namespace Hash
	{
		/**
		 @brief A hash identifier.
		 @tparam TYPE   Type of the underlying hash value.
		 @tparam UNIQUE Since this is often used to wrap up the same type,
			providing a unique value makes sure they are not interchangeable
			if not desired.
		 */
		template <typename TYPE, const int UNIQUE = 0>
		struct HashID
		{
			HashID();
			HashID(const HashID& rhs);
			explicit constexpr HashID(TYPE rhs);

			constexpr TYPE GetID() const;

			HashID& operator =(const HashID& rhs);

			bool operator ==(const HashID& rhs) const;
			bool operator !=(const HashID& rhs) const;
			bool operator <(const HashID& rhs) const;
			bool operator <=(const HashID& rhs) const;
			bool operator >(const HashID& rhs) const;
			bool operator >=(const HashID& rhs) const;

		private:
			TYPE mID;
		};

		template <typename TYPE, const int UNIQUE>
		HashID<TYPE, UNIQUE>::HashID()
			: mID(TYPE(-1))
		{}

		template <typename TYPE, const int UNIQUE>
		HashID<TYPE, UNIQUE>::HashID(const HashID& rhs)
			: mID(rhs.mID)
		{}

		template <typename TYPE, const int UNIQUE>
		constexpr HashID<TYPE, UNIQUE>::HashID(TYPE rhs)
			: mID(rhs)
		{}

		template <typename TYPE, const int UNIQUE>
		constexpr TYPE HashID<TYPE, UNIQUE>::GetID() const
		{
			return mID;
		}

		template <typename TYPE, const int UNIQUE>
		HashID<TYPE, UNIQUE>& HashID<TYPE, UNIQUE>::operator =(const HashID<TYPE, UNIQUE>& rhs)
		{
			mID = rhs.mID;
			return *this;
		}

		template <typename TYPE, const int UNIQUE>
		bool HashID<TYPE, UNIQUE>::operator ==(const HashID<TYPE, UNIQUE>& rhs) const
		{
			return mID == rhs.mID;
		}

		template <typename TYPE, const int UNIQUE>
		bool HashID<TYPE, UNIQUE>::operator !=(const HashID<TYPE, UNIQUE>& rhs) const
		{
			return mID != rhs.mID;
		}

		template <typename TYPE, const int UNIQUE>
		bool HashID<TYPE, UNIQUE>::operator <(const HashID<TYPE, UNIQUE>& rhs) const
		{
			return mID < rhs.mID;
		}

		template <typename TYPE, const int UNIQUE>
		bool HashID<TYPE, UNIQUE>::operator <=(const HashID<TYPE, UNIQUE>& rhs) const
		{
			return mID <= rhs.mID;
		}

		template <typename TYPE, const int UNIQUE>
		bool HashID<TYPE, UNIQUE>::operator >(const HashID<TYPE, UNIQUE>& rhs) const
		{
			return mID > rhs.mID;
		}

		template <typename TYPE, const int UNIQUE>
		bool HashID<TYPE, UNIQUE>::operator >=(const HashID<TYPE, UNIQUE>& rhs) const
		{
			return mID >= rhs.mID;
		}
	}
}

namespace CPF_STL_NAMESPACE
{
	template <typename IDTYPE, const int UNIQUE>
	struct hash<Cpf::Hash::HashID<IDTYPE, UNIQUE>>
	{
		size_t operator ()(const Cpf::Hash::HashID<IDTYPE, UNIQUE>& id) const
		{
			return size_t(id.GetID());
		}
	};
}
