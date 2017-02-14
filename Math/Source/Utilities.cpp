//////////////////////////////////////////////////////////////////////////
#include "Math/Utilities.hpp"

using namespace Cpf;
using namespace Math;

float Math::RadiansBetween(const Vector3fv& direction, const Vector3fv target)
{
	if (direction == target)
		return 0.0f;

	float dot = Clamp(Dot(Normalize(direction), Normalize(target)), -1.0f, 1.0f);
	return acosf(dot);
}

float Math::ClosestRotationTo(const Vector3fv& start, const Vector3fv& end, const Vector3fv& axis)
{
	float angle = RadiansBetween(start, end);

	Vector3fv nstart = Normalize(start);
	Vector3fv naxis = Normalize(axis);
	Vector3fv right = Cross(naxis, nstart);

	Vector3fv nend = Normalize(end);
	float dotRight = Dot(nend, right);
	return dotRight >= 0.0f ? angle : -angle;
}

float Math::DirectionTowards(const Vector3fv& start, const Vector3fv& end, const Vector3fv& axis, float tolerance)
{
	Vector3fv
		ns = Normalize(start),
		ne = Normalize(end),
		na = Normalize(axis);

	Vector3fv right = Cross(na, ns);
	float dotRight = Dot(ne, right);
	if (fabs(dotRight) < tolerance)
		return 0.0f;
	return dotRight >= 0.0f ? 1.0f : -1.0f;
}

Vector3fv Math::HeadingOnAxis(float heading, const Vector3fv& axis)
{
	Vector3fv na = Normalize(axis);
	Vector3fv right;

	if (fabs(Dot(na, Vector3fv::YAxis())) > 0.99f)
		right = Cross(na, Vector3fv::ZAxis());
	else
		right = Cross(na, Vector3fv::YAxis());
	Vector3fv up = Cross(right, na);

	right *= sinf(heading);
	up *= cosf(heading);
	Vector3fv result = right + up;
	return result;
}
