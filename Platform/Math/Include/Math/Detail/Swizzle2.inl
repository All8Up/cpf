//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "Math/Detail/Swizzle2.hpp"

namespace Cpf
{
	namespace Math
	{
		template<typename TYPE, const int x, const int y>
		Swizzle2<TYPE, x, y>::operator Vector2<TYPE>() const
		{
			return Vector2<TYPE>(_Data()[x], _Data()[y]);
		};

		template<typename TYPE, const int x, const int y>
		Swizzle2<TYPE, x, y>& Swizzle2<TYPE, x, y>::operator = (const Vector2<TYPE>& rhs)
		{
			_Data()[x] = rhs.x;
			_Data()[y] = rhs.y;
			return *this;
		}
	}
}
