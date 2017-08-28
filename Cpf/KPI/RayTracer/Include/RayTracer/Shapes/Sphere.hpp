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
		bool CPF_VECTORCALL Intersect(Vector3Param origin, Vector3Param dir, float& t) const override;
		Vector3 CPF_VECTORCALL Normal(Vector3Param hp) const override;

	private:
		Cpf::Math::Geometry::Sphere<Vector3> mSphere;
	};
}
