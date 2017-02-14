//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Math.hpp"

namespace Cpf
{
	namespace Math
	{
		template<typename TYPE>
		Matrix33v<TYPE> GetOrientation(const Matrix44v<TYPE>& rhs)
		{
			Vector3v<TYPE> c0 = Normalize(Vector3v<TYPE>(rhs.Column(0).xyz));
			Vector3v<TYPE> c1 = Normalize(Vector3v<TYPE>(rhs.Column(1).xyz));
			Vector3v<TYPE> c2 = Normalize(Vector3v<TYPE>(rhs.Column(2).xyz));
			return Matrix33v<TYPE>(
				c0.x, c1.x, c2.x,
				c0.y, c1.y, c2.y,
				c0.z, c1.z, c2.z);
		}

		template<typename TYPE>
		Vector3v<TYPE> GetScale(const Matrix44v<TYPE>& rhs)
		{
			Vector3v<TYPE> result(
				Magnitude(Vector3v<TYPE>(rhs.Column(0).xyz)),
				Magnitude(Vector3v<TYPE>(rhs.Column(1).xyz)),
				Magnitude(Vector3v<TYPE>(rhs.Column(2).xyz)));
			return result;
		}

		template<typename TYPE>
		Vector3v<TYPE> GetTranslation(const Matrix44v<TYPE>& rhs)
		{
			Vector3v<TYPE> result(rhs(3, 0), rhs(3, 1), rhs(3, 2));
			return result;
		}
	}
}
