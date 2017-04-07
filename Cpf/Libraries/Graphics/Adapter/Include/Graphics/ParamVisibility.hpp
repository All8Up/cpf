//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EnumFlagType.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class ParamVisibility : int32_t
		{
			eVisibilityAll = 0,
			eVertex = 1,
			eHull = 2,
			eDomain = 3,
			eGeometry = 4,
			ePixel = 5
		};
		CPF_ENUM_FLAG_TYPE(ParamVisibility);
	}
}
