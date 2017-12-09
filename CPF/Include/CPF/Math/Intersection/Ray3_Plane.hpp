//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Intersection.hpp"
#include "Math.hpp"
#include "Math/Geometry/Ray3.hpp"
#include "Math/Geometry/Plane.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename VTYPE>
		bool Intersect(const Ray3<VTYPE>& ray, const Plane<VTYPE>& plane, typename VTYPE::LaneType& t);


		template <typename VTYPE>
		bool Intersect(const Ray3<VTYPE>& ray, const Plane<VTYPE>& plane, typename VTYPE::LaneType& t)
		{
			auto test = Dot(plane.Normal, ray.Direction);
			if (test >= 0)
				return false;
			auto dist = (-Dot(plane.Normal, ray.Origin) + plane.Distance) / test;

			if (dist > 0)
			{
				t = dist;
				return true;
			}

			return false;
		}
	}
}
