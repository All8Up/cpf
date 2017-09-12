//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EnumFlagType.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class DepthStencilClearFlag : int32_t
		{
			eDepth = 1 << 0,
			eStencil = 1 << 1
		};
		CPF_ENUM_FLAG_TYPE(DepthStencilClearFlag);
	}
}
