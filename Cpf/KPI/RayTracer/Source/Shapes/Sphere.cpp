#include "RayTracer/Shapes/Sphere.hpp"
#include "RayTracer/ParseTypes.hpp"
#include "Math/Intersection/Ray3_Sphere.hpp"


using namespace RayTracer;


Sphere::Sphere()
:	mSphere{Vector3(0.0f), 1.0f}
{
}


bool Sphere::Parse( Scene& s, JSONValue* v )
{
	if( !::Parse( v, "Position", mSphere.Position ) )
		return false;

	if( !::Parse( v, "Radius", mSphere.Radius ) )
		return false;

	return Model::Parse( s, v );
}


bool CPF_VECTORCALL Sphere::Intersect(const Ray3& ray, float& t) const
{
	float result = 0.0f;
	if (Cpf::Math::Intersect(ray, mSphere, result))
	{
		if (result < t)
		{
			t = result;
			return true;
		}
	}
	return false;
}


Vector3 CPF_VECTORCALL Sphere::Normal(Vector3Param hp) const
{
	Vector3	result(Vector3(hp) - mSphere.Position);
	return Normalize(result);
}
