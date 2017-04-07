//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class WrapMode : int32_t
		{
			eWrap = 1,
			eMirror = 2,
			eClamp = 3,
			eBorder = 4,
			eMirrorOnce = 5
		};
	}
}
