//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"
#include "Graphics/SubPassDesc.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct iRenderPass : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iRenderPass"_crc64);
		};
	}
}
