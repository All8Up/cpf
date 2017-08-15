//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RayTracer/RayTracer.hpp"
#include "RayTracer/Model.hpp"


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
		Vector3 mPosition;
		float mRadius;
	};
}
