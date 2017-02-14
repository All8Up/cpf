//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class iCommandPool : public iRefCounted
		{
		public:
			virtual ~iCommandPool() = 0;

			virtual void Reset() = 0;
		};
	}
}
