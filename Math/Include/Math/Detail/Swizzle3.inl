//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "Math/Detail/Swizzle3.hpp"
#include "Math/Vector3v.hpp"

namespace Cpf
{
	namespace Math
	{
		template<typename TYPE, const int x, const int y, const int z>
		TYPE* Swizzle3<TYPE, x, y, z>::_Data()
		{
			return reinterpret_cast<TYPE*>(mBuffer);
		}

		template<typename TYPE, const int x, const int y, const int z>
		const TYPE* Swizzle3<TYPE, x, y, z>::_Data() const
		{
			return reinterpret_cast<const TYPE*>(mBuffer);
		}

		template<typename TYPE, const int x, const int y, const int z>
		Swizzle3<TYPE, x, y, z>::operator Vector3v<Simd::Float32x4>() const
		{
			return Vector3v<Simd::Float32x4>(_Data()[x], _Data()[y], _Data()[z]);
		}

		template<typename TYPE, const int x, const int y, const int z>
		Swizzle3<TYPE, x, y, z>::operator Vector3<TYPE>() const
		{
			return Vector3<TYPE>(_Data()[x], _Data()[y], _Data()[z]);
		};

		template<typename TYPE, const int x, const int y, const int z>
		Swizzle3<TYPE, x, y, z>& Swizzle3<TYPE, x, y, z>::operator = (const Vector3<TYPE>& rhs)
		{
			_Data()[x] = rhs.x;
			_Data()[y] = rhs.y;
			_Data()[z] = rhs.z;
			return *this;
		}
	}
}
