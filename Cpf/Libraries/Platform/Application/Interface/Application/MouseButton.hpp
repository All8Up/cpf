//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EnumFlagType.hpp"

namespace Cpf
{
	enum class MouseButton : int32_t
	{
		eLeft,
		eMiddle,
		eRight,
		eX1,
		eX2
	};
	CPF_ENUM_FLAG_TYPE(MouseButton);
}
