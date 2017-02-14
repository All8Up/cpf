//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Math/Math.hpp"

namespace Cpf
{
	namespace Math
	{
		/**
		* @brief A swizzle 4.
		* @tparam TYPE Type of the type.
		* @tparam x    Generic type parameter.
		* @tparam y    Generic type parameter.
		* @tparam z    Generic type parameter.
		* @tparam w    Generic type parameter.
		*/
		template<typename TYPE, const int x, const int y, const int z, const int w>
		class Swizzle4
		{
		public:
			operator Vector4<TYPE>() const;

		private:
			TYPE* _Data() { return reinterpret_cast<TYPE*>(mBuffer); }
			const TYPE* _Data() const { return reinterpret_cast<const TYPE*>(mBuffer); }

			char mBuffer[1];
		};
	}
}
