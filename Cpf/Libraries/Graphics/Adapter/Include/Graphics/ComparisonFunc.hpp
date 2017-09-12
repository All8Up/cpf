//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class ComparisonFunc : int32_t
		{
			eNever = 1,
			eLess,
			eEqual,
			eLessEqual,
			eGreater,
			eNotEqual,
			eGreaterEqual,
			eAlways
		};
	}
}
