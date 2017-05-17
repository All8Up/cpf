//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iResource.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct Range;

		struct iIndexBuffer : iResource
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iIndexBuffer"_crc64);
		};
	}
}
