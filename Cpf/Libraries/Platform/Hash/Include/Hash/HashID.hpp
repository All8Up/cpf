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
		 @tparam UNIQUE_TAG Since this is often used to wrap up the same type,
			providing a unique tag type makes sure they are not interchangeable
			when not desired.
		 */
		template <typename TYPE, typename TAG>
		struct HashID
		{
			using TagType = TAG;

			HashID();
			constexpr HashID(const HashID& rhs);
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

		template <typename TYPE, typename TAG>
		HashID<TYPE, TAG>::HashID()
			: mID(TYPE(-1))
		{}

		template <typename TYPE, typename TAG>
		constexpr HashID<TYPE, TAG>::HashID(const HashID& rhs)
			: mID(rhs.mID)
		{}

		template <typename TYPE, typename TAG>
		constexpr HashID<TYPE, TAG>::HashID(TYPE rhs)
			: mID(rhs)
		{}

		template <typename TYPE, typename TAG>
		constexpr TYPE HashID<TYPE, TAG>::GetID() const
		{
			return mID;
		}

		template <typename TYPE, typename TAG>
		HashID<TYPE, TAG>& HashID<TYPE, TAG>::operator =(const HashID<TYPE, TAG>& rhs)
		{
			mID = rhs.mID;
			return *this;
		}

		template <typename TYPE, typename TAG>
		bool HashID<TYPE, TAG>::operator ==(const HashID<TYPE, TAG>& rhs) const
		{
			return mID == rhs.mID;
		}

		template <typename TYPE, typename TAG>
		bool HashID<TYPE, TAG>::operator !=(const HashID<TYPE, TAG>& rhs) const
		{
			return mID != rhs.mID;
		}

		template <typename TYPE, typename TAG>
		bool HashID<TYPE, TAG>::operator <(const HashID<TYPE, TAG>& rhs) const
		{
			return mID < rhs.mID;
		}

		template <typename TYPE, typename TAG>
		bool HashID<TYPE, TAG>::operator <=(const HashID<TYPE, TAG>& rhs) const
		{
			return mID <= rhs.mID;
		}

		template <typename TYPE, typename TAG>
		bool HashID<TYPE, TAG>::operator >(const HashID<TYPE, TAG>& rhs) const
		{
			return mID > rhs.mID;
		}

		template <typename TYPE, typename TAG>
		bool HashID<TYPE, TAG>::operator >=(const HashID<TYPE, TAG>& rhs) const
		{
			return mID >= rhs.mID;
		}
	}
}

namespace CPF_STL_NAMESPACE
{
	template <typename IDTYPE, typename TAG>
	struct hash<Cpf::Hash::HashID<IDTYPE, TAG>>
	{
		size_t operator ()(const Cpf::Hash::HashID<IDTYPE, TAG>& id) const
		{
			return size_t(id.GetID());
		}
	};
}
