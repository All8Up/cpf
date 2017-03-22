//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		class Vector3;

		/**
		* @brief A swizzle 3.
		* @tparam TYPE Type of the type.
		* @tparam x    Generic type parameter.
		* @tparam y    Generic type parameter.
		* @tparam z    Generic type parameter.
		*/
		template<typename TYPE, const int x, const int y, const int z>
		class Swizzle3
		{
		public:
			operator Vector3<TYPE>() const;
			Swizzle3& operator = (const Vector3<TYPE>& rhs);

		private:
			TYPE* _Data();
			const TYPE* _Data() const;

			char mBuffer[1];
		};
	}
}
