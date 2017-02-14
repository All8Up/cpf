//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class BufferUsage : int32_t
		{
			eDefault,
			eImmutable,
			eDynamic,
			eReadback
		};
	}
}
