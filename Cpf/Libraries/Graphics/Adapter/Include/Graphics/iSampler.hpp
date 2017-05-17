//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"


namespace Cpf
{
	namespace Graphics
	{
		struct iSampler : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iSampler"_crc64);
		};
	}
}
