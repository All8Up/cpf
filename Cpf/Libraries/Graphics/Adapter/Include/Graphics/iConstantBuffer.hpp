//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iResource.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class iCommandBuffer;

		class iConstantBuffer : public iResource
		{
		public:
			virtual ~iConstantBuffer() = 0;

			virtual void Update(size_t offset, size_t size, const void* data) = 0;
		};
	}
}
