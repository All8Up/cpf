//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector3.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		class AABB
		{
		public:
			AABB();
			AABB(Vector3v<TYPE> point);
			AABB(const Std::Array<Vector3v<TYPE>>& points);
			AABB(const AABB& rhs);

			AABB& operator += (const Vector3v<TYPE>& rhs);

		private:
			Vector3v<TYPE> mMin;
			Vector3v<TYPE> mMax;
		};
	}
}

#include "Math/Detail/AABB.inl"
