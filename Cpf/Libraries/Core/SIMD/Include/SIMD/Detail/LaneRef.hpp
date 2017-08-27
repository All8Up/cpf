//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Accessor.hpp"

namespace Cpf
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
