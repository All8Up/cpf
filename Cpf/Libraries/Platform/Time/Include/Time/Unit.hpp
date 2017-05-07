//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Time
	{
		// Forward references.
		class Ratio;
		class Value;


		/**
		@class UnitBase
		@brief Provides a common base type for all time units.
		@tparam UNIT_TYPE The underlying storage type.
		@tparam NUMERATOR The numerator of the ratio which converts the unit to seconds.
		@tparam DENOMINATOR The denominator of the ratio which converts the unit to seconds.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		class UnitBase
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using Type_t = UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>;
			using ValueType_t = UNIT_TYPE;
			static const int64_t Numerator = NUMERATOR;
			static const int64_t Denominator = DENOMINATOR;

			//////////////////////////////////////////////////////////////////////////
			UnitBase();
			template<typename SRC_TYPE, const int64_t SRC_NUMERATOR, const int64_t SRC_DENOMINATOR>
			explicit UnitBase(const UnitBase<SRC_TYPE, SRC_NUMERATOR, SRC_DENOMINATOR>& value);
			UnitBase(const Value& value);
			UnitBase(UNIT_TYPE value);
			UnitBase(const Type_t& rhs);

			//////////////////////////////////////////////////////////////////////////
			Type_t& operator =(const Type_t& rhs);
			Type_t& operator =(const Value rhs);

			//////////////////////////////////////////////////////////////////////////
			template<typename RHS_TYPE>
			bool operator ==(const RHS_TYPE& rhs) const;
			template<typename RHS_TYPE>
			bool operator !=(const RHS_TYPE& rhs) const;
			template<typename RHS_TYPE>
			bool operator >(const RHS_TYPE& rhs) const;
			template<typename RHS_TYPE>
			bool operator >=(const RHS_TYPE& rhs) const;
			template<typename RHS_TYPE>
			bool operator <(const RHS_TYPE& rhs) const;
			template<typename RHS_TYPE>
			bool operator <=(const RHS_TYPE& rhs) const;


			//////////////////////////////////////////////////////////////////////////
			Type_t operator +(const Type_t& rhs) const;
			Type_t operator -(const Type_t& rhs) const;
			Type_t operator *(double rhs) const;
			Type_t operator /(double rhs) const;

			//////////////////////////////////////////////////////////////////////////
			template<typename TARGET> TARGET Cast() const;
			operator UNIT_TYPE () const;

			//////////////////////////////////////////////////////////////////////////
			const Ratio GetRatio() const;

		protected:
			UNIT_TYPE m_Value;
		};

		/**
		 * @brief A unit base specialization for int64.  This implements a rounding
		 * system for int64_t types to make conversions more accurate.
		 * @tparam NUMERATOR   Type of the numerator.
		 * @tparam DENOMINATOR Type of the denominator.
		 */
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		class UnitBase<int64_t, NUMERATOR, DENOMINATOR>
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using Type_t = UnitBase<int64_t, NUMERATOR, DENOMINATOR>;
			using ValueType_t = int64_t;
			static const int64_t Numerator = NUMERATOR;
			static const int64_t Denominator = DENOMINATOR;

			//////////////////////////////////////////////////////////////////////////
			UnitBase();
			template<typename SRC_TYPE, const int64_t SRC_NUMERATOR, const int64_t SRC_DENOMINATOR>
			explicit UnitBase(const UnitBase<SRC_TYPE, SRC_NUMERATOR, SRC_DENOMINATOR>& value);
			UnitBase(const Value& value);
			UnitBase(int64_t value);
			UnitBase(const Type_t& rhs);

			//////////////////////////////////////////////////////////////////////////
			Type_t& operator =(const Type_t& rhs);
			Type_t& operator =(const Value rhs);

			//////////////////////////////////////////////////////////////////////////
			template<typename RHS_TYPE>
			bool operator ==(const RHS_TYPE& rhs) const;
			template<typename RHS_TYPE>
			bool operator !=(const RHS_TYPE& rhs) const;
			template<typename RHS_TYPE>
			bool operator >(const RHS_TYPE& rhs) const;
			template<typename RHS_TYPE>
			bool operator >=(const RHS_TYPE& rhs) const;
			template<typename RHS_TYPE>
			bool operator <(const RHS_TYPE& rhs) const;
			template<typename RHS_TYPE>
			bool operator <=(const RHS_TYPE& rhs) const;


			//////////////////////////////////////////////////////////////////////////
			Type_t operator +(const Type_t& rhs) const;
			Type_t operator -(const Type_t& rhs) const;
			Type_t operator *(double rhs) const;
			Type_t operator /(double rhs) const;

			//////////////////////////////////////////////////////////////////////////
			template<typename TARGET> TARGET Cast() const;
			operator int64_t () const;

			//////////////////////////////////////////////////////////////////////////
			const Ratio GetRatio() const;

		protected:
			int64_t m_Value;
		};


		//////////////////////////////////////////////////////////////////////////
		using Ns = UnitBase<int64_t, 1, 1000000000>;
		using Us = UnitBase<int64_t, 1, 1000000>;
		using Ms = UnitBase<int64_t, 1, 1000>;
		using Seconds = UnitBase<double, 1, 1>;
		using Minutes = UnitBase<double, 60, 1>;
		using Hours = UnitBase<double, 60 * 60, 1>;
		using Days = UnitBase<double, 24 * 60 * 60, 1>;
		using Years = UnitBase<double, 365 * 24 * 60 * 60, 1>;
	}
}

//////////////////////////////////////////////////////////////////////////
#include "Time/Unit.inl"
