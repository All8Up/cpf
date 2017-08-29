//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace Math
	{
		template <typename VTYPE, typename DTYPE = float>
		struct Plane
		{
			VTYPE Normal;
			DTYPE Distance;
		};
	}
}
