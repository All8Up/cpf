//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	struct OSWindowData
	{
#if CPF_TARGET_WINDOWS
		HWND mHwnd;
		HDC mHDC;
#endif
#if CPF_TARGET_DARWIN
		void* mpView;
#endif
	};
}
