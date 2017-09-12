//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class SwapEffect : int32_t
		{
			eDiscard,
			eSequential,
			eFlipSequential,
			eFlipDiscard
		};
	}
}
