//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"
#include "Graphics/SubPassDesc.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iRenderPass : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iRenderPass"_crc64);
		};
	}
}
