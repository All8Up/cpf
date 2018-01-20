//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Math/Vector3v.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename VTYPE>
		struct AABB
		{
			VTYPE mMin;
			VTYPE mMax;
		};

		using AABBfv = AABB<Vector3fv>;

		template<typename AABB_TYPE, typename VECTOR_TYPE>
		void Add(AABB<AABB_TYPE>* outBounds, const Vector3<VECTOR_TYPE>& v)
		{
			CPF_ASSERT(outBounds != nullptr);
			outBounds->mMin = Min(outBounds->mMin, v);
			outBounds->mMax = Max(outBounds->mMax, v);
		}
	}
}
