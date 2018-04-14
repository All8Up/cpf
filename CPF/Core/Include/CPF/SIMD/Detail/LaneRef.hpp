//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Accessor.hpp"

namespace CPF
{
	namespace SIMD
	{
		template <typename TYPE, int I0> class LaneRef_1;
		template <typename TYPE, int I0, int I1> class LaneRef_2;
		template <typename TYPE, int I0, int I1, int I2> class LaneRef_3;
		template <typename TYPE, int I0, int I1, int I2, int I3> class LaneRef_4;
	}
}

#include "CPF/SIMD/Detail/LaneRef_1.inl"
#include "CPF/SIMD/Detail/LaneRef_2.inl"
#include "CPF/SIMD/Detail/LaneRef_3.inl"
#include "CPF/SIMD/Detail/LaneRef_4.inl"
