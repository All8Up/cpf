//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Desktop/iClipboard.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace SDL2
	{
		struct Clipboard : public GOM::tUnknown<Platform::Desktop::iClipboard>
		{
			GOM::Result CPF_STDCALL GetClipboardText(int32_t* count, char* text) override;
			GOM::Result CPF_STDCALL SetClipboardText(const char* text) override;
		};
	}
}
