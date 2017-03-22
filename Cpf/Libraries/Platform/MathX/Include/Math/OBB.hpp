//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector3.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		class OBB
		{
		public:
			OBB();

		private:
			Vector3<TYPE> mAxis[3];
		};
	}
}
