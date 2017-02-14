//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class iShader;

		class iPipeline : public iRefCounted
		{
		public:
			virtual ~iPipeline() = 0;
		};
	}
}
