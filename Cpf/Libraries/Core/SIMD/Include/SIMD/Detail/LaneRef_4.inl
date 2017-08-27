//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace SIMD
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int I0, int I1, int I2, int I3>
		class LaneRef_4 : public Accessor<TYPE>
		{
		public:
			// TODO: Enable assign through such as: a.yzwx = b.xyzw;
			operator typename TYPE::Lanes_4() const;
		};


		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int I0, int I1, int I2, int I3>
		LaneRef_4<TYPE, I0, I1, I2, I3>::operator typename TYPE::Lanes_4() const
		{
			return (*GetType()).template GetLanes<I0, I1, I2, I3>();
		}
	}
}
