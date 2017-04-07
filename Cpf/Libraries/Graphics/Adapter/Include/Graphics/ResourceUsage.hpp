//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EnumFlagType.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class ResourceUsage : int32_t
		{
			eNone = 0,
			eRenderTarget = 0x01,
			eDepthStencil = 0x02,
			eUnorderedAccess = 0x04,
			eSimultaneous = 0x20
		};
		CPF_ENUM_FLAG_TYPE(ResourceUsage);
	}
}
