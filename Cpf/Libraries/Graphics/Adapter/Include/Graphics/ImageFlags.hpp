//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EnumFlagType.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class ImageFlags : int32_t
		{
			eNone = 0,
			eAllowRenderTarget = 1 << 0,
			eAllowDepthStencil = 1 << 1
		};
		CPF_ENUM_FLAG_TYPE(ImageFlags)
	}
}
