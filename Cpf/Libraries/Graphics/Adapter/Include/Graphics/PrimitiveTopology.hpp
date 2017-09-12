//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class PrimitiveTopology : int32_t
		{
			eUndefined = 0,
			ePointList = 1,
			eLineList = 2,
			eLineStrip = 3,
			eTriangleList = 4,
			eTriangleStrip = 5,
			// TODO: Add more as needed.
		};
	}
}
