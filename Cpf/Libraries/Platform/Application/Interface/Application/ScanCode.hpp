//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	enum class ScanCode : int32_t
	{
		eReturn = 40,
		eEscape = 41,
		eBackspace = 42,
		eTab = 43,
		eSpace = 44,
		ePrintScreen = 70,
		eScrollLock = 71,
		ePause = 72,
		eInsert = 73,
		eHome = 74,
		ePageUp = 75,
		eDelete = 76,
		eEnd = 77,
		ePageDown = 78,
		eRight = 79,
		eLeft = 80,
		eDown = 81,
		eUp = 82,
		eBackspace = 187,
	};
}
