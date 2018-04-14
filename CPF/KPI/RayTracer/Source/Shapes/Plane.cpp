#include "RayTracer/Shapes/Plane.hpp"
#include "RayTracer/ParseTypes.hpp"
#include "CPF/Math/Intersection/Ray3_Plane.hpp"

using namespace RayTracer;


bool Plane::Parse( Scene& s, JSONValue* v )
{
	Vector3	position;
	if( !::Parse( v, "Position", position ) )
		return false;

	if( !::Parse( v, "Normal", mPlane.Normal ) )
		return false;
	mPlane.Normal = Normalize(mPlane.Normal);
	mPlane.Distance	=	Dot(position, mPlane.Normal);

	return Model::Parse( s, v );
}


bool CPF_VECTORCALL Plane::Intersect(const Ray3& ray, float& t) const
{
	float distance;
	if (CPF::Math::Intersect(ray, mPlane, distance))
	{
		if (distance < t)
		{
			t = distance;
			return true;
		}
	}
	return false;
}


Vector3 CPF_VECTORCALL Plane::Normal(Vector3Param /* hp */) const
{
	return mPlane.Normal;
}
