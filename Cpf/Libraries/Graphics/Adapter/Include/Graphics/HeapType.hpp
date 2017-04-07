//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class HeapType : int32_t
		{
			eDefault = 1,
			eUpload = 2,
			eReadback = 3,
			eCustom = 4
		};
	}
}
