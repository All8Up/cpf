//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iCommandPool : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iCommandPool"_crc64);

			virtual void Reset() = 0;
		};
	}
}
