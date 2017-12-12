//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
{
	namespace SIMD
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int I0, int I1, int I2>
		class LaneRef_3 : public Accessor<TYPE>
		{
		public:
			// TODO: Enable assign through such as: a.yzx = b.xyz;
			operator typename TYPE::Lanes_3() const;
		};


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int I0, int I1, int I2>
		LaneRef_3<TYPE, I0, I1, I2>::operator typename TYPE::Lanes_3() const
		{
			return (*GetType()).template GetLanes<I0, I1, I2>();
		}

	}
}
