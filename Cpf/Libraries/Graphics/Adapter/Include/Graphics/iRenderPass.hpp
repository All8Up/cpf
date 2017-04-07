//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "Graphics/SubPassDesc.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class iRenderPass : public iRefCounted
		{
		public:
			virtual ~iRenderPass();
		};
	}
}
