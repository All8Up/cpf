//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iPipeline : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iPipeline"_crc64);
		};
	}
}
