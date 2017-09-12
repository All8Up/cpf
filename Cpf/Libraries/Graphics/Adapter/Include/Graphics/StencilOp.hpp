//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class StencilOp : int32_t
		{
			eKeep = 1,
			eZero,
			eReplace,
			eIncSat,
			eDecSat,
			eInvert,
			eInc,
			eDec
		};
	}
}
