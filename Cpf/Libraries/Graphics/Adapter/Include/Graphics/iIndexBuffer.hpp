//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iResource.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct Range;

		struct iIndexBuffer : iResource
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iIndexBuffer"_crc64);

			virtual bool Map(void**, Range* = nullptr) = 0;
			virtual void Unmap(Range* = nullptr) = 0;
		};
	}
}
