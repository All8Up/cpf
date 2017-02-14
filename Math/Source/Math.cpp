//////////////////////////////////////////////////////////////////////////
#include "Math/Math.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector3v.hpp"
#include "Math/Vector4.hpp"
#include "Math/Vector4v.hpp"

namespace Cpf
{
	namespace Math
	{
		// Force instantiate the templates.
		//template class Vector2<Half>;
		template
		class Vector2<float>;
		template
		class Vector2<double>;
		template
		class Vector2<int32_t>;
		template
		class Vector3<int32_t>;
		template
		class Vector3<float>;
		template
		class Vector3v<Simd::Float32x4>;
		template
		class Vector4<int32_t>;
		template
		class Vector4<float>;
		template
		class Vector4v<Simd::Float32x4>;

#undef CPF_MATH_DETAIL_SWIZZLEMACROS_HPP
#undef SWIZZLE_PREFIX
#undef SWIZZLE_NAME

#define SWIZZLE_PREFIX template class
#define SWIZZLE_NAME(a)
#include "Math/Detail/SwizzleMacros.hpp"

		SWIZZLE2_XYZW(float)
		SWIZZLE3_XYZW(float)
		SWIZZLE4_XYZW(float)
	}
}
