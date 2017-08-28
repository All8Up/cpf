#include "RayTracer/Shapes/Sphere.hpp"
#include "RayTracer/ParseTypes.hpp"


using namespace RayTracer;


Sphere::Sphere()
:	mSphere{Vector3(0.0f), 1.0f}
{
}


bool Sphere::Parse( Scene& s, JSONValue* v )
{
	if( !::Parse( v, "Position", mSphere.mPosition ) )
		return false;

	if( !::Parse( v, "Radius", mSphere.mRadius ) )
		return false;

	return Model::Parse( s, v );
}


bool CPF_VECTORCALL Sphere::Intersect(Vector3Param origin, Vector3Param dir, float& t) const
{
	Vector3 dist = mSphere.mPosition - Vector3(origin);
	auto B = Dot(Vector3(dir), dist);
	auto D = B*B - Dot(dist, dist) + mSphere.mRadius*mSphere.mRadius;

	if (D < 0.0f)
		return false;

	auto t0 = B - std::sqrt(D);
	auto t1 = B + std::sqrt(D);
	bool retvalue = false;

	if ((t0 > 0.0f) && (t0 < t))
	{
		t = t0;
		retvalue = true;
	}
	if ((t1 > 0.0f) && (t1 < t))
	{
		t = t1;
		retvalue = true;
	}
	return retvalue;
}


Vector3 CPF_VECTORCALL Sphere::Normal(Vector3Param hp) const
{
	Vector3	result(Vector3(hp) - mSphere.mPosition);
	return Normalize(result);
}
