//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int INDEX>
		class Ref32x4_1
		{
		public:
			using Element = typename TYPE::Element;

			Ref32x4_1& operator = (float value);
			operator Element() const;

		private:
			TYPE* _Data() { return reinterpret_cast<TYPE*>(mData); }
			const TYPE* _Data() const { return reinterpret_cast<const TYPE*>(mData); }

			uint8_t mData[1];
		};

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int INDEX>
		Ref32x4_1<TYPE, INDEX>& Ref32x4_1<TYPE, INDEX>::operator =(float value)
		{
			_Data()->SetLane(INDEX, value);
			return *this;
		}

		template <typename TYPE, int INDEX>
		Ref32x4_1<TYPE, INDEX>::operator typename Ref32x4_1<TYPE, INDEX>::Element () const
		{
			Element result = _Data()->GetLane<INDEX>();
			return result;
		}


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		class Ref32x4_Index
		{
		public:
			using Element = typename TYPE::Element;

			Ref32x4_Index(TYPE& v, int idx) : mVector(v), mIndex(idx) {};
			Ref32x4_Index(const Ref32x4_Index& rhs) : mVector(rhs.mVector), mIndex(rhs.mIndex) {}

			Ref32x4_Index& operator = (Element value) { mVector.SetLane(mIndex, value); return *this; }
			operator Element() const { return mVector.GetLane(mIndex); }

		private:
			TYPE& mVector;
			const int mIndex;
		};
	}
}

#define REF32X4_1_SWIZZLE(t)		\
	Cpf::SIMD::Ref32x4_1<t, 0> x;	\
	Cpf::SIMD::Ref32x4_1<t, 1> y;	\
	Cpf::SIMD::Ref32x4_1<t, 2> z;	\
	Cpf::SIMD::Ref32x4_1<t, 3> w;
