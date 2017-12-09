//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
{
	namespace SIMD
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int I0, int I1>
		class LaneRef_2 : public Accessor<TYPE>
		{
		public:
			// TODO: Enable assign through such as: a.yz = b.xy;
			operator typename TYPE::Lanes_2() const;
		};


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int I0, int I1>
		LaneRef_2<TYPE, I0, I1>::operator typename TYPE::Lanes_2() const
		{
			return (*GetType()).template GetLanes<I0, I1>();
		}

	}
}
