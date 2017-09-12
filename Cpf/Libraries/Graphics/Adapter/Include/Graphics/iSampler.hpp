//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"


namespace CPF
{
	namespace Graphics
	{
		struct iSampler : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iSampler"_crc64);
		};
	}
}
