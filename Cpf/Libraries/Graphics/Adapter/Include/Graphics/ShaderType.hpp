//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class ShaderType : int32_t
		{
			eVertex,
			ePixel,
			eCompute,
			eDomain,
			eGeometry,
			eHull
		};
	}
}
