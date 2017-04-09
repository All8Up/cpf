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
			virtual bool Map(void**, Range* = nullptr) = 0;
			virtual void Unmap(Range* = nullptr) = 0;
		};
	}
}
