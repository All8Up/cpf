//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iResource.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct Range;
		struct ImageDesc;

		struct iImage : Graphics::iResource
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iImage"_crc64);

			virtual const ImageDesc& GetDesc() const = 0;
		};
	}
}
