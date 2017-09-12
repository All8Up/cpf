//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iImage.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct iImageView : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iImageView"_crc64);
		};
	}
}
