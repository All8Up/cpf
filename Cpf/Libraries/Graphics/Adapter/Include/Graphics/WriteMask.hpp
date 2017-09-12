//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		/** @brief Write mask for render targets. */
		enum class WriteMask : uint8_t
		{
			eRed = 1,
			eGreen = 2,
			eBlue = 4,
			eAlpha = 8,
			eAll = (eRed | eGreen | eBlue | eAlpha)
		};
	}
}
