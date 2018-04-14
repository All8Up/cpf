//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
{
	namespace SIMD
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int I0>
		class LaneRef_1 : public Accessor<TYPE>
		{
		public:
			LaneRef_1& operator = (typename TYPE::LaneType value);
			operator typename TYPE::LaneType() const;
		};


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int I0>
		LaneRef_1<TYPE, I0>& LaneRef_1<TYPE, I0>::operator =(typename TYPE::LaneType value)
		{
			GetType()->SetLane(I0, value);
			return *this;
		}

		template <typename TYPE, int I0>
		LaneRef_1<TYPE, I0>::operator typename TYPE::LaneType() const
		{
			return (*GetType()).template GetLane<I0>();
		}
	}
}
