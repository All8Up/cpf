//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		AABB<TYPE>::AABB()
			: mMin(kFloatMax)
			, mMax(-kFloatMax)
		{}

		template <typename TYPE>
		AABB<TYPE>::AABB(Vector3v<TYPE> point)
			: mMin(point)
			, mMax(point)
		{}

		template <typename TYPE>
		AABB<TYPE>::AABB(const Std::Array<Vector3v<TYPE>>& points)
		{
			if (points.empty())
			{
				mMin = kFloatMax;
				mMax = -kFloatMax;
			}
			else
			{
				mMin = points[0];
				mMax = points[0];
				for (int i=1; i<points.size(); ++i)
				{
					*this += points[i];
				}
			}
		}

		template <typename TYPE>
		AABB<TYPE>::AABB(const AABB& rhs)
			: mMin(rhs.mMin)
			, mMax(rhs.mMax)
		{}

		template <typename TYPE>
		AABB<TYPE>& AABB<TYPE>::operator += (const Vector3v<TYPE>& rhs)
		{
			mMin = Min(mMin, rhs);
			mMax = Max(mMax, rhs);
			return *this;
		}
	}
}
