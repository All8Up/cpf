//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iResource.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct Range;

		class iIndexBuffer : public iResource
		{
		public:
			virtual ~iIndexBuffer() = 0;

			virtual bool Map(void**, Range* = nullptr) = 0;
			virtual void Unmap(Range* = nullptr) = 0;
		};
	}
}
