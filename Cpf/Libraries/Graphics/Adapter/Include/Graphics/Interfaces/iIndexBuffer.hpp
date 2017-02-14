//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Interfaces/iResource.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class iIndexBuffer : public iResource
		{
		public:
			virtual ~iIndexBuffer() = 0;
		};
	}
}
