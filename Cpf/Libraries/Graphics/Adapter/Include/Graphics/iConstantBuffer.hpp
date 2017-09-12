//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iResource.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct iConstantBuffer : iResource
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iConstantBuffer"_crc64);

			virtual void Update(size_t offset, size_t size, const void* data) = 0;
		};
	}
}
