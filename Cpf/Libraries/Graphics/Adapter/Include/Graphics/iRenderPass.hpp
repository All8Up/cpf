//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "Graphics/SubPassDesc.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iRenderPass : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iRenderPass"_crc64);
		};
	}
}
