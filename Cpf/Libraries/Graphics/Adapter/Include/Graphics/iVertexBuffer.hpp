//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iResource.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct Range;

		class iVertexBuffer : public iResource
		{
		public:
			virtual ~iVertexBuffer() = 0;

			virtual bool Map(void**, const Range* = nullptr) = 0;
			virtual void Unmap(const Range* = nullptr) = 0;
		};
	}
}
