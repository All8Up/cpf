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
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iIndexBuffer"_crc64);
		};
	}
}
