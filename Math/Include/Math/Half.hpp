//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Math.hpp"


namespace Cpf
{
	namespace Math
	{
		class CPF_EXPORT_MATH Half
		{
		public:
			//
			Half();
			Half(const Half& rhs);
			explicit Half(const float rhs);

			//
			Half& operator =(const Half& rhs);
			Half& Set(const Half& rhs);
			Half& Set(const float rhs);

			//
			bool operator ==(const Half rhs) const;
			bool operator !=(const Half rhs) const;
			bool operator >(const Half rhs) const;
			bool operator <(const Half rhs) const;

			//
			operator uint16_t() const;
			operator float() const;

		private:
			//
			uint16_t			mHalf;
		};


		//////////////////////////////////////////////////////////////////////////
		inline Half::Half()
		{
		}

		inline Half::Half(const Half& rhs)
			: mHalf(rhs.mHalf)
		{
		}


		inline Half::Half(const float rhs)
		{
			Set(rhs);
		}


		//////////////////////////////////////////////////////////////////////////
		inline Half& Half::Set(const float rhs)
		{
			uint32_t iValue = *(uint32_t*)&rhs & 0x7FFFFFFF;
			uint32_t sign = (*(uint32_t*)&rhs & 0x80000000) >> 16;

			if (iValue > 0x47FFEFFF)
			{
				// The number is too large to be represented as a half.  Saturate to infinity.
				mHalf = (uint16_t)(sign | 0x7FFF);
			}
			else
			{
				if (iValue < 0x38800000)
				{
					// The number is too small to be represented as a normalized half.
					// Convert it to a denormalized value.
					uint32_t shift = 113 - (iValue >> 23);
					iValue = (0x800000 | (iValue & 0x7FFFFF)) >> shift;
				}
				else
				{
					// Rebias the exponent to represent the value as a normalized half.
					iValue += 0xC8000000;
				}

				mHalf = (uint16_t)(sign | ((iValue + 0x0FFF + ((iValue >> 13) & 1)) >> 13));
			}

			return *this;
		}

		inline Half& Half::operator =(const Half& rhs)
		{
			mHalf = rhs.mHalf;
			return *this;
		}

		//***********************************************************************
		//	Accessors.
		//***********************************************************************

		inline Half::operator float() const
		{
			uint32_t mantissa = (uint32_t)(mHalf & 0x03FF);
			uint32_t exponent;
			uint32_t result;

			if ((mHalf & 0x7C00) != 0)  // The value is normalized
			{
				exponent = (uint32_t)((mHalf >> 10) & 0x1F);
			}
			else if (mantissa != 0)     // The value is denormalized
			{
				// Normalize the value in the resulting float
				exponent = 1;

				do
				{
					exponent--;
					mantissa <<= 1;
				} while ((mantissa & 0x0400) == 0);

				mantissa &= 0x03FF;
			}
			else                        // The value is zero
			{
				exponent = (uint32_t)-112;
			}

			result = ((mHalf & 0x8000) << 16) | // Sign
				((exponent + 112) << 23) | // Exponent
				(mantissa << 13);          // Mantissa

			return *(float*)&result;
		}
	}
}
