#include "RayTracer/Shapes/Plane.hpp"
#include "RayTracer/ParseTypes.hpp"


using namespace RayTracer;


bool Plane::Parse( Scene& s, JSONValue* v )
{
	Vector3	position;
	if( !::Parse( v, "Position", position ) )
		return false;

	if( !::Parse( v, "Normal", mNormal ) )
		return false;
	mNormal = Normalize(mNormal);
	mDistance	=	Dot(position, mNormal);

	return Model::Parse( s, v );
}


bool CPF_VECTORCALL Plane::Intersect(const Ray3& ray, float& t) const
{
	auto test = Dot(mNormal, ray.Direction);

	if (test >= 0.0f)
		return false;
	auto dist = (-Dot(mNormal, ray.Origin) + mDistance) / test;

	if (dist > 0.0f && dist < t)
	{
		t = dist;
		return true;
	}

	return false;
}


Vector3 CPF_VECTORCALL Plane::Normal(Vector3Param /* hp */) const
{
	return mNormal;
}
