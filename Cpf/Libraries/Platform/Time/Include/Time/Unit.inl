//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Time/Value.hpp"
#include "Time/Ratio.hpp"


namespace CPF
{
	namespace Time
	{
		/**
		@brief Default constructor, zero's the time value.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::UnitBase()
			: m_Value(UNIT_TYPE(0))
		{}


		/**
		@brief Conversion constructor to move between time unit representations.
		@param value The source time value to convert from.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename SRC_TYPE, const int64_t SRC_NUMERATOR, const int64_t SRC_DENOMINATOR>
		UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::UnitBase(const UnitBase<SRC_TYPE, SRC_NUMERATOR, SRC_DENOMINATOR>& value)
			: m_Value(UNIT_TYPE((value.template Cast<double>() * double(SRC_NUMERATOR * DENOMINATOR)) / double(SRC_DENOMINATOR * NUMERATOR)))
		{
		}


		/**
		@brief Conversion constructor from a value to a specific time unit representation.
		@param value The source time value representing OS specific time units.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::UnitBase(const Value& value)
		{
			double numerator = double(value.GetRatio().GetNumerator() * DENOMINATOR);
			double denominator = double(value.GetRatio().GetDenominator() * NUMERATOR);
			m_Value = ValueType_t(double(value.GetTicks() * numerator) / denominator);
		}


		/**
		@brief Constructor from OS specific counter.
		@param value The OS specific counter value.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::UnitBase(UNIT_TYPE value)
			: m_Value(value)
		{}


		/**
		@brief Copy constructor.
		@param rhs The source of the copy.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::UnitBase(const Type_t& rhs)
			: m_Value(rhs.m_Value)
		{}


		//////////////////////////////////////////////////////////////////////////

		/**
		@brief Assignment operator from same time unit.
		@param rhs The source of the assignment.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>& UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::operator =(const Type_t& rhs)
		{
			m_Value = rhs.m_Value;
			return *this;
		}


		/**
		@brief Assignment operator with time unit conversions.
		@param rhs The source of the assignment.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>& UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::operator =(const Value rhs)
		{
			double numerator = double(rhs.GetRatio().GetNumerator() * DENOMINATOR);
			double denominator = double(rhs.GetRatio().GetDenominator() * NUMERATOR);
			m_Value = ValueType_t((rhs.GetTicks() * numerator) / denominator);
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////

		/**
		@brief Equality operator.
		@param rhs Value to compare against.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename RHS_TYPE>
		bool UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::operator ==(const RHS_TYPE& rhs) const
		{
			return m_Value == UNIT_TYPE(Type_t(rhs).m_Value);
		}


		/**
		@brief Inequality operator.
		@param rhs Value to compare against.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename RHS_TYPE>
		bool UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::operator !=(const RHS_TYPE& rhs) const
		{
			return m_Value != UNIT_TYPE(Type_t(rhs).m_Value);
		}


		/**
		@brief Greater than operator.
		@param rhs Value to compare against.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename RHS_TYPE>
		bool UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::operator >(const RHS_TYPE& rhs) const
		{
			return m_Value > UNIT_TYPE(Type_t(rhs).m_Value);
		}


		/**
		@brief Greater than or equal to operator.
		@param rhs Value to compare against.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename RHS_TYPE>
		bool UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::operator >=(const RHS_TYPE& rhs) const
		{
			return m_Value >= UNIT_TYPE(Type_t(rhs).m_Value);
		}


		/**
		@brief Less than operator.
		@param rhs Value to compare against.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename RHS_TYPE>
		bool UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::operator <(const RHS_TYPE& rhs) const
		{
			return m_Value < UNIT_TYPE(Type_t(rhs).m_Value);
		}


		/**
		@brief Less than or equal operator.
		@param rhs Value to compare against.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename RHS_TYPE>
		bool UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::operator <=(const RHS_TYPE& rhs) const
		{
			return m_Value <= UNIT_TYPE(Type_t(rhs).m_Value);
		}


		//////////////////////////////////////////////////////////////////////////

		/**
		@brief Addition operator.
		@param rhs Value to add.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR> UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::operator +(const Type_t& rhs) const
		{
			return Type_t(m_Value + rhs.m_Value);
		}


		/**
		@brief Subtraction operator.
		@param rhs Value to subtract.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR> UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::operator -(const Type_t& rhs) const
		{
			return Type_t(m_Value - rhs.m_Value);
		}


		/**
		@brief Multiplication operator.
		@param rhs Scalar value to multiply by.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR> UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::operator *(double rhs) const
		{
			return Type_t(UNIT_TYPE(m_Value * rhs));
		}


		/**
		@brief Division operator.
		@param rhs Scalar value to divide by.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR> UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::operator /(double rhs) const
		{
			return Type_t(UNIT_TYPE(m_Value / rhs));
		}


		//////////////////////////////////////////////////////////////////////////

		/**
		@brief Cast the internal representation to the given type.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename TARGET>
		TARGET UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::Cast() const
		{
			return TARGET(m_Value);
		}


		/**
		@brief Internal value operator.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::operator UNIT_TYPE () const
		{
			return UNIT_TYPE(m_Value);
		}


		//////////////////////////////////////////////////////////////////////////

		/**
		@brief Get the internal representation of one second.
		*/
		template<typename UNIT_TYPE, const int64_t NUMERATOR, const int64_t DENOMINATOR>
		const Ratio UnitBase<UNIT_TYPE, NUMERATOR, DENOMINATOR>::GetRatio() const
		{
			return Ratio(NUMERATOR, DENOMINATOR);
		}



		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		/**
		@brief Default constructor, zero's the time value.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<int64_t, NUMERATOR, DENOMINATOR>::UnitBase()
			: m_Value(int64_t(0))
		{}


		/**
		@brief Conversion constructor to move between time unit representations.
		@param value The source time value to convert from.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename SRC_TYPE, const int64_t SRC_NUMERATOR, const int64_t SRC_DENOMINATOR>
		UnitBase<int64_t, NUMERATOR, DENOMINATOR>::UnitBase(const UnitBase<SRC_TYPE, SRC_NUMERATOR, SRC_DENOMINATOR>& value)
			: m_Value(int64_t((value.template Cast<double>() * double(SRC_NUMERATOR * DENOMINATOR)) / double(SRC_DENOMINATOR * NUMERATOR)))
		{
		}


		/**
		@brief Conversion constructor from a value to a specific time unit representation.
		@param value The source time value representing OS specific time units.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<int64_t, NUMERATOR, DENOMINATOR>::UnitBase(const Value& value)
		{
			double numerator = double(value.GetRatio().GetNumerator() * DENOMINATOR);
			double denominator = double(value.GetRatio().GetDenominator() * NUMERATOR);
			double roundUp = (denominator / numerator)*0.5;
			double top = (value.GetTicks() + roundUp) * numerator;
			m_Value = ValueType_t(top / denominator);
		}


		/**
		@brief Constructor from OS specific counter.
		@param value The OS specific counter value.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<int64_t, NUMERATOR, DENOMINATOR>::UnitBase(int64_t value)
			: m_Value(value)
		{}


		/**
		@brief Copy constructor.
		@param rhs The source of the copy.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<int64_t, NUMERATOR, DENOMINATOR>::UnitBase(const Type_t& rhs)
			: m_Value(rhs.m_Value)
		{}


		//////////////////////////////////////////////////////////////////////////

		/**
		@brief Assignment operator from same time unit.
		@param rhs The source of the assignment.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<int64_t, NUMERATOR, DENOMINATOR>& UnitBase<int64_t, NUMERATOR, DENOMINATOR>::operator =(const Type_t& rhs)
		{
			m_Value = rhs.m_Value;
			return *this;
		}


		/**
		@brief Assignment operator with time unit conversions.
		@param rhs The source of the assignment.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<int64_t, NUMERATOR, DENOMINATOR>& UnitBase<int64_t, NUMERATOR, DENOMINATOR>::operator =(const Value rhs)
		{
			double numerator = double(rhs.GetRatio().GetNumerator() * DENOMINATOR);
			double denominator = double(rhs.GetRatio().GetDenominator() * NUMERATOR);
			m_Value = ValueType_t((rhs.GetTicks() * numerator) / denominator);
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////

		/**
		@brief Equality operator.
		@param rhs Value to compare against.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename RHS_TYPE>
		bool UnitBase<int64_t, NUMERATOR, DENOMINATOR>::operator ==(const RHS_TYPE& rhs) const
		{
			return m_Value == int64_t(Type_t(rhs).m_Value);
		}


		/**
		@brief Inequality operator.
		@param rhs Value to compare against.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename RHS_TYPE>
		bool UnitBase<int64_t, NUMERATOR, DENOMINATOR>::operator !=(const RHS_TYPE& rhs) const
		{
			return m_Value != int64_t(Type_t(rhs).m_Value);
		}


		/**
		@brief Greater than operator.
		@param rhs Value to compare against.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename RHS_TYPE>
		bool UnitBase<int64_t, NUMERATOR, DENOMINATOR>::operator >(const RHS_TYPE& rhs) const
		{
			return m_Value > int64_t(Type_t(rhs).m_Value);
		}


		/**
		@brief Greater than or equal to operator.
		@param rhs Value to compare against.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename RHS_TYPE>
		bool UnitBase<int64_t, NUMERATOR, DENOMINATOR>::operator >=(const RHS_TYPE& rhs) const
		{
			return m_Value >= int64_t(Type_t(rhs).m_Value);
		}


		/**
		@brief Less than operator.
		@param rhs Value to compare against.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename RHS_TYPE>
		bool UnitBase<int64_t, NUMERATOR, DENOMINATOR>::operator <(const RHS_TYPE& rhs) const
		{
			return m_Value < int64_t(Type_t(rhs).m_Value);
		}


		/**
		@brief Less than or equal operator.
		@param rhs Value to compare against.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename RHS_TYPE>
		bool UnitBase<int64_t, NUMERATOR, DENOMINATOR>::operator <=(const RHS_TYPE& rhs) const
		{
			return m_Value <= int64_t(Type_t(rhs).m_Value);
		}


		//////////////////////////////////////////////////////////////////////////

		/**
		@brief Addition operator.
		@param rhs Value to add.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<int64_t, NUMERATOR, DENOMINATOR> UnitBase<int64_t, NUMERATOR, DENOMINATOR>::operator +(const Type_t& rhs) const
		{
			return Type_t(m_Value + rhs.m_Value);
		}


		/**
		@brief Subtraction operator.
		@param rhs Value to subtract.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<int64_t, NUMERATOR, DENOMINATOR> UnitBase<int64_t, NUMERATOR, DENOMINATOR>::operator -(const Type_t& rhs) const
		{
			return Type_t(m_Value - rhs.m_Value);
		}


		/**
		@brief Multiplication operator.
		@param rhs Scalar value to multiply by.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<int64_t, NUMERATOR, DENOMINATOR> UnitBase<int64_t, NUMERATOR, DENOMINATOR>::operator *(double rhs) const
		{
			return Type_t(int64_t(m_Value * rhs));
		}


		/**
		@brief Division operator.
		@param rhs Scalar value to divide by.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<int64_t, NUMERATOR, DENOMINATOR> UnitBase<int64_t, NUMERATOR, DENOMINATOR>::operator /(double rhs) const
		{
			return Type_t(int64_t(m_Value / rhs));
		}


		//////////////////////////////////////////////////////////////////////////

		/**
		@brief Cast the internal representation to the given type.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		template<typename TARGET>
		TARGET UnitBase<int64_t, NUMERATOR, DENOMINATOR>::Cast() const
		{
			return TARGET(m_Value);
		}


		/**
		@brief Internal value operator.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		UnitBase<int64_t, NUMERATOR, DENOMINATOR>::operator int64_t () const
		{
			return int64_t(m_Value);
		}


		//////////////////////////////////////////////////////////////////////////

		/**
		@brief Get the internal representation of one second.
		*/
		template<const int64_t NUMERATOR, const int64_t DENOMINATOR>
		const Ratio UnitBase<int64_t, NUMERATOR, DENOMINATOR>::GetRatio() const
		{
			return Ratio(NUMERATOR, DENOMINATOR);
		}
	}
}
