//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace SIMD
	{
		template <typename TYPE>
		class LaneIndex
		{
		public:
			LaneIndex(TYPE& v, int idx);
			LaneIndex(const LaneIndex& rhs);

			LaneIndex& operator = (typename TYPE::LaneType value);
			operator typename TYPE::LaneType() const;

		private:
			TYPE& mVector;
			const int mIndex;
		};

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		LaneIndex<TYPE>::LaneIndex(TYPE& v, int idx)
			: mVector(v)
			, mIndex(idx)
		{};

		template <typename TYPE>
		LaneIndex<TYPE>::LaneIndex(const LaneIndex& rhs)
			: mVector(rhs.mVector)
			, mIndex(rhs.mIndex)
		{}

		template <typename TYPE>
		LaneIndex<TYPE>& LaneIndex<TYPE>::operator = (typename TYPE::LaneType value)
		{
			mVector.SetLane(mIndex, value);
			return *this;
		}

		template <typename TYPE>
		LaneIndex<TYPE>::operator typename TYPE::LaneType() const
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
