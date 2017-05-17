//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iResource.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct Range;

		struct iVertexBuffer : iResource
		{
			static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Graphics::iVertexBuffer"_crc64);

			virtual bool Map(void**, const Range* = nullptr) = 0;
			virtual void Unmap(const Range* = nullptr) = 0;
		};
	}
}
