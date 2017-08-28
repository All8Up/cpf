//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector3v.hpp"

namespace Cpf
{
	namespace Math
	{
		namespace Geometry
		{
			template <typename VTYPE, typename RTYPE=float>
			struct Sphere
			{
				VTYPE mPosition;
				RTYPE mRadius;
			};
		}
	}
}
