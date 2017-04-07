//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EnumFlagType.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class ParamFlags : int32_t
		{
			eVolatile = 0x02,
			eStaticWhileSet = 0x04,
			eStatic = 0x08
		};
		CPF_ENUM_FLAG_TYPE(ParamFlags);
	}
}
