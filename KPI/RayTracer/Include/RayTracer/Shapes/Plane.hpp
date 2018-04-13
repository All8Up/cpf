//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RayTracer/RayTracer.hpp"
#include "RayTracer/Model.hpp"
#include "CPF/Math/Geometry/Plane.hpp"

namespace RayTracer
{
	class CPF_ALIGN(16) Plane  : public Model
	{
	public:
		bool Parse( Scene& s, JSONValue* v ) override;
		bool CPF_VECTORCALL Intersect(const Ray3& ray, float& t) const override;
		Vector3 CPF_VECTORCALL Normal(Vector3Param hp) const override;

	private:
		CPF::Math::Plane<Vector3> mPlane;
	};
}
