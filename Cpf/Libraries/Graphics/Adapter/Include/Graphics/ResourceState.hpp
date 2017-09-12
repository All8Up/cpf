//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class ResourceState : int32_t
		{
			eCommon = 0x00,
			ePresent = eCommon,
			eVertexAndConstant = 0x01,
			eIndex = 0x02,
			eRenderTarget = 0x04,
			eUnorderedAccess = 0x08,
			eDepthWrite = 0x10,
			eDepthRead = 0x20,
			eNonPixelShaderResource = 0x40,
			ePixelShaderResource = 0x80,
			eStreamOut = 0x100,
			eIndirectArgument = 0x200,
			eCopyDest = 0x400,
			eCopySource = 0x800,
			eResolveDest = 0x1000,
			eResolveSource = 0x2000,
			ePredication = eIndirectArgument,
			eGenericRead = (((((0x1 | 0x2) | 0x40) | 0x80) | 0x200) | 0x800)
		};
	}
}
