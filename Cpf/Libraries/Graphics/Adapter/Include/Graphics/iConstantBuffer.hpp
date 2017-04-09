//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iResource.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iCommandBuffer;

		struct iConstantBuffer : iResource
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iConstantBuffer"_crc64);

			virtual void Update(size_t offset, size_t size, const void* data) = 0;
		};
	}
}
