//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class TopologyType : int32_t
		{
			eUndefined = 0,
			ePoint,
			eLine,
			eTriangle,
			ePatch,
			eCount
		};

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
