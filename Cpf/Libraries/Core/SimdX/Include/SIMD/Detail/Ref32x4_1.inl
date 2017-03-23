//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace SIMD
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int INDEX>
		Ref32x4_1<TYPE, INDEX>& Ref32x4_1<TYPE, INDEX>::operator =(float value)
		{
			_Data()->SetLane(INDEX, value);
			return *this;
		}

		template <typename TYPE, int INDEX>
		Ref32x4_1<TYPE, INDEX>::operator typename Ref32x4_1<TYPE, INDEX>::Element() const
		{
			Element result = _Data()->GetLane<INDEX>();
			return result;
		}

		template <typename TYPE, int INDEX>
		TYPE* Ref32x4_1<TYPE, INDEX>::_Data()
		{
			return reinterpret_cast<TYPE*>(mData);
		}

		template <typename TYPE, int INDEX>
		const TYPE* Ref32x4_1<TYPE, INDEX>::_Data() const
		{
			return reinterpret_cast<const TYPE*>(mData);
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Ref32x4_Index<TYPE>::Ref32x4_Index(TYPE& v, int idx) : mVector(v), mIndex(idx) {};

		template <typename TYPE>
		Ref32x4_Index<TYPE>::Ref32x4_Index(const Ref32x4_Index& rhs) : mVector(rhs.mVector), mIndex(rhs.mIndex) {}

		template <typename TYPE>
		Ref32x4_Index<TYPE>& Ref32x4_Index<TYPE>::operator = (Element value) { mVector.SetLane(mIndex, value); return *this; }

		template <typename TYPE>
		Ref32x4_Index<TYPE>::operator Element() const { return mVector.GetLane(mIndex); }
	}
}
