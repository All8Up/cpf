//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EnumFlagType.hpp"

namespace Cpf
{
	enum class WindowFlags : int32_t
	{
		eNone = 0,
		eFullscreen = 1 << 0,
		eSupportOpenGL = 1 << 1,
		eShown = 1 << 2,
		eHidden = 1 << 3,
		eBorderless = 1 << 4,
		eResizable = 1 << 5,
		eMinimized = 1 << 6,
		eMaximized = 1 << 7,
		eInputGrabbed = 1 << 8,
		eInputFocus = 1 << 9,
		eMouseFocus = 1 << 10,
		eFullscreenDesktop = 1 << 11,
		eAllowHDPI = 1 << 12,
		eMouseCapture = 1 << 13
	};
	CPF_ENUM_FLAG_TYPE(WindowFlags);
}
