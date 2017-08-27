//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector3.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		struct AABB
		{
			Vector3v<TYPE> mMin;
			Vector3v<TYPE> mMax;
		};
	}
}

#include "Math/Detail/AABB.inl"
