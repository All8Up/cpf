//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector3.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		class AABB
		{
		public:
			AABB();

		private:
			Vector3<TYPE> mMin;
			Vector3<TYPE> mMax;
		};
	}
}
