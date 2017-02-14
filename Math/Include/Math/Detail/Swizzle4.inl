//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "Math/Detail/Swizzle4.hpp"

namespace Cpf
{
	namespace Math
	{
		template<typename TYPE, const int x, const int y, const int z, const int w>
		Swizzle4<TYPE, x, y, z, w>::operator Vector4<TYPE>() const
		{
			return Vector4<TYPE>(_Data()[x], _Data()[y], _Data()[z], _Data()[w]);
		};
	}
}
