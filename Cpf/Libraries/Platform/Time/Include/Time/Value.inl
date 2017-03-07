//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Time/Unit.hpp"
#include "Time/Ratio.hpp"


namespace Cpf
{
	namespace Time
	{
		/**
		@brief Conversion constructor.
		@param value is the source time value to convert from.
		*/
		template<typename UNIT_TYPE>
		Value::Value(const UNIT_TYPE value)
		{
			double numerator = double(UNIT_TYPE::Numerator * GetRatio().GetDenominator());
			double denominator = double(UNIT_TYPE::Denominator * GetRatio().GetNumerator());
			m_Ticks = ValueType_t(typename UNIT_TYPE::ValueType_t(value) * (numerator / denominator));
		}


		/**
		@brief Conversion assignment.
		@param value is the source time value to convert from.
		*/
		template<typename UNIT_TYPE>
		Value& Value::operator =(UNIT_TYPE& value)
		{
			double numerator = double(UNIT_TYPE::Numerator * GetRatio().GetDenominator());
			double denominator = double(UNIT_TYPE::Denominator * GetRatio().GetNumerator());
			m_Ticks = ValueType_t(typename UNIT_TYPE::ValueType_t(value) * (numerator / denominator));
			return *this;
		}
	}
}
