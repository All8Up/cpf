//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class EnumMode : int32_t
		{
			eNone = 0,
			eInterlaced = 1 << 0,
			eScaling = 1 << 1,
			eStereo = 1 << 2,
			eDisabledStereo = 1 << 3
		};
		CPF_ENUM_FLAG_TYPE(EnumMode);
	}
}
