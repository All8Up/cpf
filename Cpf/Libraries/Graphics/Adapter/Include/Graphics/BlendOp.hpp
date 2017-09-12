//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class BlendOp : int32_t
		{
			eAdd = 1,
			eSubtract,
			eReverseSubtract,
			eMin,
			eMax
		};
	}
}
