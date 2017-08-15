//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace SIMD
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int INDEX>
		Ref32x4_1<TYPE, INDEX>& Ref32x4_1<TYPE, INDEX>::operator =(typename TYPE::LaneType value)
		{
			_Data()->SetLane(INDEX, value);
			return *this;
		}

		template <typename TYPE, int INDEX>
		Ref32x4_1<TYPE, INDEX>::operator typename TYPE::LaneType() const
		{
			auto data = *_Data();
			return data.template GetLane<INDEX>();
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
		Ref32x4_Index<TYPE>::Ref32x4_Index(TYPE& v, int idx)
			: mVector(v)
			, mIndex(idx)
		{};

		template <typename TYPE>
		Ref32x4_Index<TYPE>::Ref32x4_Index(const Ref32x4_Index& rhs)
			: mVector(rhs.mVector)
			, mIndex(rhs.mIndex)
		{}

		template <typename TYPE>
		Ref32x4_Index<TYPE>& Ref32x4_Index<TYPE>::operator = (typename TYPE::LaneType value)
		{
			mVector.SetLane(mIndex, value);
			return *this;
		}

		template <typename TYPE>
		Ref32x4_Index<TYPE>::operator typename TYPE::LaneType() const
		{
			switch (mIndex)
			{
			case 0: return mVector.template GetLane<0>();
			case 1: return mVector.template GetLane<1>();
			case 2: return mVector.template GetLane<2>();
			case 3: return mVector.template GetLane<3>();
			default:
				CPF_ASSERT_ALWAYS;
				return mVector.template GetLane<3>();
			}
		}
	}
}
