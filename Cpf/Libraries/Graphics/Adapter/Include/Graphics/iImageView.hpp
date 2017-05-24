//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iImage.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iImageView : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iImageView"_crc64);
		};
	}
}
