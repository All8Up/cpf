//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class iResource : public tRefCounted<iRefCounted>
		{
		public:
			virtual ~iResource() = 0;
		};
	}
}
