//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"

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
