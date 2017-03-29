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
			Vector3v<TYPE> mMin;
			Vector3v<TYPE> mMax;
		};
	}
}
