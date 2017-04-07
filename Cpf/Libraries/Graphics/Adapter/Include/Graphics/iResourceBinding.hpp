//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class iResourceBinding : public iRefCounted
		{
		public:
			virtual ~iResourceBinding() = 0;
		};
	}
}
