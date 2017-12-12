//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Intersection.hpp"
#include "Math.hpp"
#include "Math/Geometry/Ray3.hpp"
#include "Math/Geometry/Sphere.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename VTYPE>
		bool Intersect(const Ray3<VTYPE>& ray, const Sphere<VTYPE>& sphere, typename VTYPE::LaneType& t);


		template <typename VTYPE>
		bool Intersect(const Ray3<VTYPE>& ray, const Sphere<VTYPE>& sphere, typename VTYPE::LaneType& t)
		{
			auto dist = sphere.Position - ray.Origin;
			auto b = Dot(ray.Direction, dist);
			auto d = b*b - Dot(dist, dist) + sphere.Radius*sphere.Radius;

			if (d < 0)
				return false;

			auto t0 = b - Sqrt(d);
			auto t1 = b + Sqrt(d);
			if (t0 > 0 && t0 <= t1)
				t = t0;
			else if (t1 > 0)
				t = t1;
			else
				return false;
			return true;
		}
	}
}
