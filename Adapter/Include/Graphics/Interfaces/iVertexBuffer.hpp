//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Interfaces/iResource.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class iVertexBuffer : public iResource
		{
		public:
			virtual ~iVertexBuffer() = 0;

			virtual bool Map(int32_t start, int32_t end, void**) = 0;
			virtual bool Unmap() = 0;
		};
	}
}
