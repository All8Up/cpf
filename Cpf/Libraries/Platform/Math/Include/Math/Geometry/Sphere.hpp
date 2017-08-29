//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector3v.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename VTYPE, typename RTYPE=float>
		struct Sphere
		{
			VTYPE Position;
			RTYPE Radius;
		};
	}
}
