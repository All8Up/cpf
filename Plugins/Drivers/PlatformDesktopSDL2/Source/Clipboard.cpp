//////////////////////////////////////////////////////////////////////////
#include "Clipboard.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include <SDL.h>

using namespace CPF;
using namespace Platform;
using namespace SDL2;

GOM::Result CPF_STDCALL Clipboard::GetClipboardText(int32_t* count, char* chars)
{
	if (count)
	{
		const char* clipText = SDL_GetClipboardText();
		int32_t len = int32_t(strlen(clipText));
		if (chars)
		{
			if (*count < len)
				return GOM::kNotEnoughSpace;
			strcpy(chars, clipText);
		}
		else
			*count = len;
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Clipboard::SetClipboardText(const char* chars)
{
	if (chars)
	{
		SDL_SetClipboardText(chars);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
