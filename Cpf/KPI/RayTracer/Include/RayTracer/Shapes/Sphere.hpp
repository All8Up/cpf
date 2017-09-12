//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RayTracer/RayTracer.hpp"
#include "RayTracer/Model.hpp"
#include "Math/Geometry/Sphere.hpp"

namespace RayTracer
{
	class CPF_ALIGN(16) Sphere : public Model
	{
	public:
		Sphere();

		bool Parse(Scene& s, JSONValue* v) override;
		bool CPF_VECTORCALL Intersect(const Ray3& ray, float& t) const override;
		Vector3 CPF_VECTORCALL Normal(Vector3Param hp) const override;

	private:
		CPF::Math::Sphere<Vector3> mSphere;
	};
}
