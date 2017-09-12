//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class LogicOp : int32_t
		{
			eClear = 0,
			eSet,
			eCopy,
			eCopyInverted,
			eNoop,
			eInvert,
			eAnd,
			eNand,
			eOr,
			eNor,
			eXor,
			eEquiv,
			eAndReverse,
			eAndInverted,
			eOrReverse,
			eOrInverted
		};
	}
}
