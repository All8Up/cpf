//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct iCommandPool : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iCommandPool"_crc64);

			virtual void Reset() = 0;
		};
	}
}
