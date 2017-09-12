//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EnumFlagType.hpp"

namespace CPF
{
	enum class MouseButton : int32_t
	{
		eNone = 0,
		eLeft = 1<<0,
		eMiddle = 1<<1,
		eRight = 1<<2,
		eX1 = 1<<3,
		eX2 = 1<<4
	};
	CPF_ENUM_FLAG_TYPE(MouseButton);
}
