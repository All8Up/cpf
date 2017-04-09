//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include <windows.h>

namespace Cpf
{
	namespace Graphics
	{
		struct WindowData
		{
#if CPF_TARGET_WINDOWS
			HWND mHWnd;
#endif
		};
	}
}
