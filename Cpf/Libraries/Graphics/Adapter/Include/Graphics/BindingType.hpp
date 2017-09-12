//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class BindingType : int32_t
		{
			eConstants,
			eConstantBuffer,
			eResourceBuffer,
			eUnorderedBuffer,
			eRange,
			eSampler,
			eTexture
		};
	}
}
