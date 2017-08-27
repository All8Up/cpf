//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector3.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		struct OBB
		{
			Vector3v<TYPE> mXAxis;
			Vector3v<TYPE> mYAxis;
			Vector3v<TYPE> mZAxis;
		};
	}
}
