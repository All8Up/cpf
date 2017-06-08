//////////////////////////////////////////////////////////////////////////
#include "Clipboard.hpp"
#include "SDL.h"

using namespace Cpf;
using namespace SDL2;

Clipboard::Clipboard(GOM::iBase*)
{}

Clipboard::~Clipboard()
{}

GOM::Result CPF_STDCALL Clipboard::Cast(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iBase::kIID.GetID():
			*outIface = static_cast<GOM::iBase*>(this);
			break;
		case iClipboard::kIID.GetID():
			*outIface = static_cast<iClipboard*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

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
