//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Math
	{
		template <int TYPESIZE>
		struct FPSize;
		template <>
		struct FPSize<32>
		{
			using ValueType = int32_t;
			using FloatType = float;
			using Intermediate = int64_t;
		};
		template <>
		struct FPSize<64>
		{
			using ValueType = int64_t;
			using FloatType = double;
			using Intermediate = int64_t;
		};

		//////////////////////////////////////////////////////////////////////////
		template <int TYPESIZE, int FRACBITS>
		class FixedPoint
		{
		public:
			using SizeType = FPSize<TYPESIZE>;
			using ValueType = typename SizeType::ValueType;
			using FloatType = typename SizeType::FloatType;
			using Intermediate = typename SizeType::Intermediate;
			static constexpr size_t kShift = FRACBITS;
			static constexpr ValueType kMaxWhole = ValueType(-1) >> FRACBITS;
			static constexpr ValueType kOneFrac = 1 << FRACBITS;
			static constexpr ValueType kMaxFrac = (1 << FRACBITS) - 1;

			FixedPoint(const FixedPoint<TYPESIZE, FRACBITS>& rhs);
			FixedPoint(ValueType whole, ValueType fraction);
			explicit FixedPoint(ValueType value);
			explicit FixedPoint(FloatType value);

			explicit operator ValueType () const;
			explicit operator FloatType () const;

			FixedPoint<TYPESIZE, FRACBITS>& operator = (FixedPoint<TYPESIZE, FRACBITS> value);

			FixedPoint<TYPESIZE, FRACBITS>& operator += (FixedPoint<TYPESIZE, FRACBITS> value);
			FixedPoint<TYPESIZE, FRACBITS>& operator -= (FixedPoint<TYPESIZE, FRACBITS> value);
			FixedPoint<TYPESIZE, FRACBITS>& operator *= (FixedPoint<TYPESIZE, FRACBITS> value);
			FixedPoint<TYPESIZE, FRACBITS>& operator /= (FixedPoint<TYPESIZE, FRACBITS> value);

		private:
			ValueType mData;
		};


		//////////////////////////////////////////////////////////////////////////
		template <int TYPESIZE, int FRACBITS>
		FixedPoint<TYPESIZE, FRACBITS>::FixedPoint(const FixedPoint<TYPESIZE, FRACBITS>& rhs)
			: mData(rhs.mData)
		{
		}

		template <int TYPESIZE, int FRACBITS>
		FixedPoint<TYPESIZE, FRACBITS>::FixedPoint(ValueType whole, ValueType fraction)
			: mData((whole << kShift) | (fraction))
		{
			CPF_ASSERT((whole & ~kMaxWhole) == 0);
			CPF_ASSERT(fraction <= kMaxFrac)
		}

		template <int TYPESIZE, int FRACBITS>
		FixedPoint<TYPESIZE, FRACBITS>::FixedPoint(ValueType value)
			: mData(value)
		{}
		template <int TYPESIZE, int FRACBITS>
		FixedPoint<TYPESIZE, FRACBITS>::FixedPoint(FloatType value)
		{
			FloatType v = value > FloatType(0) ? value : -value;
			mData = (ValueType(v) << kShift) |
				ValueType((v - ValueType(v)) * kOneFrac);
			mData = value < FloatType(0) ? -mData : mData;
		}

		template <int TYPESIZE, int FRACBITS>
		FixedPoint<TYPESIZE, FRACBITS>::operator ValueType () const
		{
			return mData;
		}

		template <int TYPESIZE, int FRACBITS>
		FixedPoint<TYPESIZE, FRACBITS>::operator FloatType () const
		{
			return FloatType(mData) / FloatType(kOneFrac);
		}

		template <int TYPESIZE, int FRACBITS>
		FixedPoint<TYPESIZE, FRACBITS>& FixedPoint<TYPESIZE, FRACBITS>::operator = (FixedPoint<TYPESIZE, FRACBITS> value)
		{
			mData = value.mData;
			return *this;
		}

		template <int TYPESIZE, int FRACBITS>
		FixedPoint<TYPESIZE, FRACBITS>& FixedPoint<TYPESIZE, FRACBITS>::operator += (FixedPoint<TYPESIZE, FRACBITS> value)
		{
			*this = *this + value;
			return *this;
		}

		template <int TYPESIZE, int FRACBITS>
		FixedPoint<TYPESIZE, FRACBITS>& FixedPoint<TYPESIZE, FRACBITS>::operator -= (FixedPoint<TYPESIZE, FRACBITS> value)
		{
			*this = *this - value;
			return *this;
		}

		template <int TYPESIZE, int FRACBITS>
		FixedPoint<TYPESIZE, FRACBITS>& FixedPoint<TYPESIZE, FRACBITS>::operator *= (FixedPoint<TYPESIZE, FRACBITS> value)
		{
			*this = *this * value;
			return *this;
		}

		template <int TYPESIZE, int FRACBITS>
		FixedPoint<TYPESIZE, FRACBITS>& FixedPoint<TYPESIZE, FRACBITS>::operator /= (FixedPoint<TYPESIZE, FRACBITS> value)
		{
			*this = *this / value;
			return *this;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename FPTYPE>
		FPTYPE operator - (const FPTYPE value)
		{
			using ValueType = typename FPTYPE::ValueType;
			return FPTYPE(-ValueType(value));
		}

		template <typename FPTYPE>
		FPTYPE operator + (const FPTYPE lhs, const FPTYPE rhs)
		{
			using ValueType = typename FPTYPE::ValueType;
			return FPTYPE(ValueType(lhs) + ValueType(rhs));
		}

		template <typename FPTYPE>
		FPTYPE operator - (const FPTYPE lhs, const FPTYPE rhs)
		{
			using ValueType = typename FPTYPE::ValueType;
			return FPTYPE(ValueType(lhs) - ValueType(rhs));
		}

		template <typename FPTYPE>
		FPTYPE operator * (const FPTYPE lhs, const FPTYPE rhs)
		{
			using ValueType = typename FPTYPE::ValueType;
			using Intermediate = typename FPTYPE::Intermediate;
			Intermediate result = Intermediate(ValueType(lhs)) * Intermediate(ValueType(rhs));
			return FPTYPE(ValueType(result >> FPTYPE::kShift));
		}

		template <typename FPTYPE>
		FPTYPE operator / (const FPTYPE lhs, const FPTYPE rhs)
		{
			using ValueType = typename FPTYPE::ValueType;
			using Intermediate = typename FPTYPE::Intermediate;
			Intermediate result = (Intermediate(ValueType(lhs)) << FPTYPE::kShift) / Intermediate(ValueType(rhs));
			return FPTYPE(ValueType(result));
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename FPTYPE>
		bool operator == (const FPTYPE lhs, const FPTYPE rhs)
		{
			using ValueType = typename FPTYPE::ValueType;
			return ValueType(lhs) == ValueType(rhs);
		}

		template <typename FPTYPE>
		bool operator != (const FPTYPE lhs, const FPTYPE rhs)
		{
			using ValueType = typename FPTYPE::ValueType;
			return ValueType(lhs) != ValueType(rhs);
		}

		template <typename FPTYPE>
		bool operator > (const FPTYPE lhs, const FPTYPE rhs)
		{
			using ValueType = typename FPTYPE::ValueType;
			return ValueType(lhs) > ValueType(rhs);
		}

		template <typename FPTYPE>
		bool operator >= (const FPTYPE lhs, const FPTYPE rhs)
		{
			using ValueType = typename FPTYPE::ValueType;
			return ValueType(lhs) >= ValueType(rhs);
		}

		template <typename FPTYPE>
		bool operator < (const FPTYPE lhs, const FPTYPE rhs)
		{
			using ValueType = typename FPTYPE::ValueType;
			return ValueType(lhs) < ValueType(rhs);
		}

		template <typename FPTYPE>
		bool operator <= (const FPTYPE lhs, const FPTYPE rhs)
		{
			using ValueType = typename FPTYPE::ValueType;
			return ValueType(lhs) <= ValueType(rhs);
		}
	}
}
