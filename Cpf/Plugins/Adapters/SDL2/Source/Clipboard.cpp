//////////////////////////////////////////////////////////////////////////
#include "Clipboard.hpp"
#include "SDL.h"

using namespace Cpf;
using namespace SDL2;

Clipboard::Clipboard(COM::iUnknown*)
{}

Clipboard::~Clipboard()
{}

COM::Result CPF_STDCALL Clipboard::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iClipboard::kIID.GetID():
			*outIface = static_cast<iClipboard*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Clipboard::GetClipboardText(int32_t* count, char* chars)
{
	if (count)
	{
		const char* clipText = SDL_GetClipboardText();
		int32_t len = int32_t(strlen(clipText));
		if (chars)
		{
			if (*count < len)
				return COM::kNotEnoughSpace;
			strcpy(chars, clipText);
		}
		else
			*count = len;
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Clipboard::SetClipboardText(const char* chars)
{
	if (chars)
	{
		SDL_SetClipboardText(chars);
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}
