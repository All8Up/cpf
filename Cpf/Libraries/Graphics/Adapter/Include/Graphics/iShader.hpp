//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"


namespace Cpf
{
	namespace Graphics
	{
		struct iDevice;

		class BinaryBlob;
		enum class ShaderType : int32_t;

		struct iShader : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iShader"_crc64);

			virtual bool LoadFrom(iDevice* device, const BinaryBlob*) = 0;
		};
	}
}
