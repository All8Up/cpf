//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"


namespace Cpf
{
	namespace Graphics
	{
		struct iDevice;
		struct iBlob;

		struct iShader : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iShader"_crc64);

			virtual bool LoadFrom(iDevice* device, iBlob*) = 0;
		};
	}
}
