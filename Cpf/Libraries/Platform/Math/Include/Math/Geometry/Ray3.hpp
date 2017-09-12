//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector3v.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename VTYPE>
		struct Ray3
		{
			Ray3(VTYPE origin, VTYPE direction);

			VTYPE Origin;
			VTYPE Direction;
		};

		template <typename VTYPE>
		Ray3<VTYPE>::Ray3(VTYPE origin, VTYPE direction)
			: Origin(origin)
			, Direction(direction)
		{}


		using Ray3fv = Ray3<Vector3fv>;
	}
}
