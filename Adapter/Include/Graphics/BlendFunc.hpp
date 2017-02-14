//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class BlendFunc : int32_t
		{
			eZero = 1,
			eOne,
			eSrcColor,
			eInvSrcColor,
			eSrcAlpha,
			eInvSrcAlpha,
			eDstAlpha,
			eInvDstAlpha,
			eDstColor,
			eInvDstColor,
			eSrcAlphaSat,
			eBlendFactor = 14,
			eInvBlendFactor,
			eSrc1Color,
			eInvSrc1Color,
			eSrc1Alpha,
			eInvSrc1Alpha
		};
	}
}
