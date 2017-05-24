//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iResourceBinding : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iResourceBinding"_crc64);
		};
	}
}
