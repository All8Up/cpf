//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"


namespace Cpf
{
	namespace Graphics
	{
		struct iSampler : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iSampler"_crc64);
		};
	}
}
