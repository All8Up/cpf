//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#include "Math/Math.hpp"

namespace Cpf
{
	namespace Math
	{
		/**
		 * @brief A swizzle 2.
		 * @tparam TYPE Type of the type.
		 * @tparam x    Generic type parameter.
		 * @tparam y    Generic type parameter.
		 */
		template<typename TYPE, const int x, const int y>
		class Swizzle2
		{
		public:
			operator Vector2<TYPE>() const;
			Swizzle2& operator = (const Vector2<TYPE>& rhs);

		private:
			TYPE* _Data() { return reinterpret_cast<TYPE*>(mBuffer); }
			const TYPE* _Data() const { return reinterpret_cast<const TYPE*>(mBuffer); }
			char mBuffer[1];
		};
	}
}
