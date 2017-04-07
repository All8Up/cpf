//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct SampleDesc
		{
			SampleDesc();
			SampleDesc(int32_t count, int32_t quality);

			int32_t mCount;
			int32_t mQuality;
		};
	}
}
