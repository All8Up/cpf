//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
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
