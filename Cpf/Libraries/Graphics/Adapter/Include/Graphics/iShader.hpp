//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"


namespace Cpf
{
	namespace Graphics
	{
		struct iDevice;
		struct iBlob;

		struct iShader : GOM::iBase
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iShader"_crc64);

			virtual bool LoadFrom(iDevice* device, iBlob*) = 0;
		};
	}
}
