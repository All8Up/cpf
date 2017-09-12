//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EnumFlagType.hpp"

namespace CPF
{
	enum class KeyModifier : int32_t
	{
		eNone = 0,
		eLeftShift = 1<<0,
		eRightShift = 1<<1,
		eLeftControl = 1<<2,
		eRightControl = 1<<3,
		eLeftAlt = 1<<4,
		eRightAlt = 1<<5,
		eLeftOS = 1<<6,
		eRightOS = 1<<7,
		eNumLock = 1<<8,
		eCaps = 1<<9,
		eMode = 1<<10,
		eControl = eLeftControl | eRightControl,
		eShift = eLeftShift | eRightShift,
		eAlt = eLeftAlt | eRightAlt,
		eOS = eLeftOS | eRightOS
	};
	CPF_ENUM_FLAG_TYPE(KeyModifier);
}
