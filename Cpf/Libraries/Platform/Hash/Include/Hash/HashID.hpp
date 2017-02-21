//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Hash/Crc.hpp"

using namespace Cpf
{
	using namespace Hash
	{
		template <typename TYPE>
		struct HashID
		{
			HashID& operator =(const HashID& rhs);
			bool operator ==(const HashID& rhs) const;
			bool operator !=(const HashID& rhs) const;
			bool operator <(const HashID& rhs) const;
			bool operator <=(const HashID& rhs) const;
			bool operator >(const HashID& rhs) const;
			bool operator >=(const HashID& rhs) const;

			const char* mpName;
			TYPE mID;
		};

		template <typename TYPE>
		HashID& operator =(const HashID& rhs)
		{
			mpName = rhs.mpName;
			mID = rhs.mID;
			return *this;
		}

		template <typename TYPE>
		bool operator ==(const HashID& rhs) const;
		template <typename TYPE>
		bool operator !=(const HashID& rhs) const;
		template <typename TYPE>
		bool operator <(const HashID& rhs) const;
		template <typename TYPE>
		bool operator <=(const HashID& rhs) const;
		template <typename TYPE>
		bool operator >(const HashID& rhs) const;
		template <typename TYPE>
		bool operator >=(const HashID& rhs) const;
	}
}