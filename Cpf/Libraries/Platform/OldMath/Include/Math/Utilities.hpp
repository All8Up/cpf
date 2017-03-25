//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Math.hpp"
#include "Math/Vector3v.hpp"

namespace Cpf
{
	namespace Math
	{
		float RadiansBetween(const Vector3fv& direction, const Vector3fv target);
		float ClosestRotationTo(const Vector3fv& start, const Vector3fv& end, const Vector3fv& axis);
		float DirectionTowards(const Vector3fv& start, const Vector3fv& end, const Vector3fv& axis, float tolerance = 0.01f);
		Vector3fv HeadingOnAxis(float heading, const Vector3fv& axis);
	}
}
