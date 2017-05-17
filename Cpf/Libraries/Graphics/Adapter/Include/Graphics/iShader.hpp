//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"


namespace Cpf
{
	namespace Graphics
	{
		struct iDevice;
		struct iBlob;

		struct iShader : GOM::iUnknown
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iShader"_crc64);

			virtual bool LoadFrom(iDevice* device, iBlob*) = 0;
		};
	}
}
