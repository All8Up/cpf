//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "Simd/Simd.hpp"
#include "Math/Detail/SwizzleMacros.hpp"


//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_MATH
#		define CPF_EXPORT_MATH
#	else // CPF_STATIC_MATH
#		if CPF_BUILD_MATH
#			define CPF_EXPORT_MATH CPF_EXPORT
#		else
#			define CPF_EXPORT_MATH CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_MATH CPF_EXPORT
#	else
#		define CPF_EXPORT_MATH
#	endif
#endif // CPF_TARGET_WINDOWS


namespace Cpf
{
	namespace Math
	{
		template<typename TYPE>
		TYPE Clamp(TYPE v, TYPE a, TYPE b)
		{
			return (v > a) ? (v < b) ? v : b : a;
		}

		class Color3f;
		template<typename T> struct Constants;
		class Half;

		template<typename TYPE> class Quaternion;

		template<typename TYPE> class Rectangle;
		using Rectanglei = Rectangle<int>;

		template<typename TYPE> class Vector2;
		using Vector2h = Vector2<Half>;
		using Vector2f = Vector2<float>;
		using Vector2d = Vector2<double>;
		using Vector2i32 = Vector2<int32_t>;
		using Vector2i = Vector2<int>;

		template<typename TYPE> class Vector3;
		using Vector3f = Vector3<float>;
		template<typename TYPE> class Vector3v;
		using Vector3fv = Vector3v<Simd::Float32x4>;

		template<typename TYPE> class Vector4;
		using Vector4f = Vector4<float>;
		template<typename TYPE> class Vector4v;
		using Vector4fv = Vector4v<Simd::Float32x4>;

		template<typename TYPE> class Matrix33v;
		using Matrix33fv = Matrix33v<Simd::Float32x4>;
		template<typename TYPE> class Matrix44v;
		using Matrix44fv = Matrix44v<Simd::Float32x4>;

		template<typename TYPE> class Quaternionv;
		using Quaternionfv = Quaternionv<Simd::Float32x4>;

		template<typename TYPE, const int x, const int y>
		class Swizzle2;
		template<typename TYPE, const int x, const int y, const int z>
		class Swizzle3;
		template<typename TYPE, const int x, const int y, const int z, const int w>
		class Swizzle4;
	}
}
