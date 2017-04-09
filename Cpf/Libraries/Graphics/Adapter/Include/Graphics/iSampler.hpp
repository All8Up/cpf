//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"


namespace Cpf
{
	namespace Graphics
	{
		struct iSampler : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iSampler"_crc64);
		};
	}
}
