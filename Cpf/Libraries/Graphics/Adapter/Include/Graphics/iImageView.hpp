//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iImage.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iImageView : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iImageView"_crc64);
		};
	}
}
