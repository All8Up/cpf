//////////////////////////////////////////////////////////////////////////
#include "KeyboardDevice.hpp"
#include "Application/KeyModifier.hpp"
#include "SDL.h"

using namespace Cpf;
using namespace SDL2;


KeyboardDevice::KeyboardDevice(COM::iUnknown*)
{}

KeyboardDevice::~KeyboardDevice()
{}

COM::Result CPF_STDCALL KeyboardDevice::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iInputDevice::kIID.GetID():
			*outIface = static_cast<iInputDevice*>(this);
			break;
		case iKeyboardDevice::kIID.GetID():
			*outIface = static_cast<iKeyboardDevice*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL KeyboardDevice::GetModifiers(KeyModifier* modifiers)
{
	if (modifiers)
	{
		*modifiers = KeyModifier::eNone;
		SDL_Keymod mods = SDL_GetModState();
		if (mods & KMOD_LSHIFT) *modifiers |= KeyModifier::eLeftShift;
		if (mods & KMOD_RSHIFT) *modifiers |= KeyModifier::eRightShift;
		if (mods & KMOD_LALT) *modifiers |= KeyModifier::eLeftAlt;
		if (mods & KMOD_RALT) *modifiers |= KeyModifier::eRightAlt;
		if (mods & KMOD_LCTRL) *modifiers |= KeyModifier::eLeftControl;
		if (mods & KMOD_RCTRL) *modifiers |= KeyModifier::eRightControl;
		if (mods & KMOD_LGUI) *modifiers |= KeyModifier::eLeftOS;
		if (mods & KMOD_RGUI) *modifiers |= KeyModifier::eRightOS;
		if (mods & KMOD_NUM) *modifiers |= KeyModifier::eNumLock;
		if (mods & KMOD_CAPS) *modifiers |= KeyModifier::eCaps;
		if (mods & KMOD_MODE) *modifiers |= KeyModifier::eMode;
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}
