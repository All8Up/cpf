//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Time.hpp"


namespace Cpf
{
	namespace Time
	{
		class Ratio;


		/**
		A value represents the os specific high(est) resolution time possible as represented in 64 bits.
		The static ratio represents the os timer granularity, used in converting to human usable values.
		*/
		class CPF_EXPORT_TIME Value
		{
		public:
			// Internal representation.
			typedef int64_t ValueType_t;

			// Construction.
			Value();
			template<typename UNIT_TYPE>
			Value(const UNIT_TYPE);
			Value(const Value&);

			// Comparisons.
			bool operator ==(Value) const;
			bool operator !=(Value) const;
			bool operator >(Value) const;
			bool operator >=(Value) const;
			bool operator <(Value) const;
			bool operator <=(Value) const;

			// Basic math.
			Value operator +(Value) const;
			Value& operator +=(Value);
			Value operator -(Value) const;
			Value& operator -=(Value);
			Value operator *(float) const;
			Value& operator *=(float);
			Value operator /(float) const;
			Value& operator /=(float);

			// Assignment.
			Value& operator =(Value);
			template<typename UNIT_TYPE>
			Value& operator =(UNIT_TYPE&);

			// Internal time representation.
			ValueType_t& GetTicks();
			ValueType_t GetTicks() const;
			static Ratio GetRatio();

			// System timer.
			static Value Now();
			static Value Zero();

		private:
			// Instance data.
			ValueType_t m_Ticks;
		};

		/**
		 * @brief Gets the now time.  Shortcut to the Value::Now.
		 * @return A Value.
		 */
		inline Value Now()
		{
			return Value::Now();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
#include "Time/Value.inl"
