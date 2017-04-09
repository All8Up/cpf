//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct ImageDesc;

		struct iImage : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iImage"_crc64);

			virtual const ImageDesc& GetDesc() const = 0;
		};
	}
}
