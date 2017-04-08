//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class iFrameBuffer : public iRefCounted
		{
		public:
			virtual ~iFrameBuffer() = 0;
		};
	}
}
