//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct ResourceData
		{
			const void* mpData;
			size_t mPitch;
			size_t mSlicePitch;
		};
	}
}
