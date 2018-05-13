//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
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

		/**
		@brief Static function to return current counter value of now.
		@return A value representing the counter at this time.
		*/
		inline Value Value::Now()
		{
			Value result;
			result.m_Ticks = Time::GetCounter();
			return result;
		}

		/**
		* @brief Gets the zero value.
		* @return A Value.
		*/
		inline Value Value::Zero()
		{
			return Value();
		}

		//////////////////////////////////////////////////////////////////////////
		/**
		@brief Default zeroing constructor.
		*/
		inline Value::Value()
			: m_Ticks(0)
		{}

		/**
		@brief Copy constructor.
		@param rhs Value to copy from.
		*/
		inline Value::Value(const Value& rhs)
			: m_Ticks(rhs.m_Ticks)
		{}

		/**
		@brief Equality operator.
		@param rhs Value to compare against.
		@return True if the values are equal.
		*/
		inline bool Value::operator ==(Value rhs) const
		{
			return m_Ticks == rhs.m_Ticks;
		}

		/**
		@brief Not equal operator.
		@param rhs Value to compare against.
		@return True if the values are not equivalent.
		*/
		inline bool Value::operator !=(Value rhs) const
		{
			return m_Ticks != rhs.m_Ticks;
		}

		/**
		@brief Greater than operator.
		@param rhs Value to compare against.
		@return True if this value is more than rhs.
		*/
		inline bool Value::operator >(Value rhs) const
		{
			return m_Ticks > rhs.m_Ticks;
		}

		/**
		@brief Greater than or equal operator.
		@param rhs Value to compare against.
		@return True if this value is more than or equal to rhs.
		*/
		inline bool Value::operator >=(Value rhs) const
		{
			return m_Ticks >= rhs.m_Ticks;
		}

		/**
		@brief Less than operator.
		@param rhs Value to compare against.
		@return True if this value is less than rhs.
		*/
		inline bool Value::operator <(Value rhs) const
		{
			return m_Ticks < rhs.m_Ticks;
		}

		/**
		@brief Less than or equals operator.
		@param rhs Value to compare against.
		@return True if this value is less than or equal to rhs.
		*/
		inline bool Value::operator <=(Value rhs) const
		{
			return m_Ticks <= rhs.m_Ticks;
		}

		/**
		@brief Addition operator.
		@param rhs Value to add to this.
		@return The resulting value of this plus rhs.
		*/
		inline Value Value::operator +(Value rhs) const
		{
			Value result;
			result.m_Ticks = ValueType_t(m_Ticks + rhs.m_Ticks);
			return result;
		}

		/**
		@brief Addition and assign operator.
		@param rhs Value to add to this.
		@return Reference to this.
		*/
		inline Value& Value::operator += (Value rhs)
		{
			m_Ticks += rhs.m_Ticks;
			return *this;
		}

		/**
		@brief Subtraction operator.
		@param rhs Value to subtract from this.
		@return The result of subtracting rhs from this.
		*/
		inline Value Value::operator -(Value rhs) const
		{
			Value result;
			result.m_Ticks = ValueType_t(m_Ticks - rhs.m_Ticks);
			return result;
		}

		/**
		@brief Subtract and assign operator.
		@param rhs The value to subtract from this.
		@return The result of subtracting rhs from this.
		*/
		inline Value& Value::operator -=(Value rhs)
		{
			m_Ticks -= rhs.m_Ticks;
			return *this;
		}

		/**
		@brief Multiplication operator.
		@param rhs The scalar value to multiply this by.
		@return The result of multiplying this by rhs.
		*/
		inline Value Value::operator *(float rhs) const
		{
			Value result;
			result.m_Ticks = ValueType_t(m_Ticks*rhs);
			return result;
		}

		/**
		@brief Multiplication and assignment operator.
		@param rhs The scalar value to multiply this by.
		@return Reference to this.
		*/
		inline Value& Value::operator *=(float rhs)
		{
			m_Ticks = ValueType_t(m_Ticks*rhs);
			return *this;
		}

		/**
		@brief Division operator.
		@param rhs The scalar value to divide this by.
		@return The result of dividing this by rhs.
		*/
		inline Value Value::operator /(float rhs) const
		{
			Value result;
			result.m_Ticks = ValueType_t(m_Ticks / rhs);
			return result;
		}

		/**
		@brief Division and assignment operator.
		@param rhs The scalar value to divide this by.
		@return Reference to this.
		*/
		inline Value& Value::operator /=(float rhs)
		{
			m_Ticks = ValueType_t(m_Ticks*rhs);
			return *this;
		}

		/**
		@brief Assignment operator.
		@param rhs The value to assign to this.
		@return Reference to this.
		*/
		inline Value& Value::operator =(Value rhs)
		{
			m_Ticks = rhs.m_Ticks;
			return *this;
		}

		/**
		@brief Get the untranslated underlying OS time value.
		@return The OS specific time value as a reference.
		*/
		inline Value::ValueType_t& Value::GetTicks()
		{
			return m_Ticks;
		}

		/**
		@brief Get the untranslated underlying OS time value.
		@return The OS specific time value.
		*/
		inline Value::ValueType_t Value::GetTicks() const
		{
			return m_Ticks;
		}

		/**
		@brief Get the ratio which can translate the OS time value to seconds.
		@return A ratio object with the appropriate numerator and denominator.
		*/
		inline Ratio Value::GetRatio()
		{
			return Time::GetCounterFrequency();
		}
	}
}
