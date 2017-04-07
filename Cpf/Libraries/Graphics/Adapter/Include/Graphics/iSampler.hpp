//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"


namespace Cpf
{
	namespace Graphics
	{
		class iSampler : public tRefCounted<iRefCounted>
		{
		public:
			virtual ~iSampler() = 0;
		};
	}
}
