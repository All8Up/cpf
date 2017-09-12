//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class ScanlineOrder : int32_t
		{
			eUnspecified,
			eProgressive,
			eUpperFieldFirst,
			eLowerFieldFirst
		};
	}
}
