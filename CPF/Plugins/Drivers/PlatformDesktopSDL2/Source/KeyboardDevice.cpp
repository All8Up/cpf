//////////////////////////////////////////////////////////////////////////
#include "KeyboardDevice.hpp"
#include "CPF/Platform/Desktop/KeyModifier.hpp"
#include "SDL.h"

using namespace CPF;
using namespace SDL2;


KeyboardDevice::KeyboardDevice()
{}

KeyboardDevice::~KeyboardDevice()
{}

GOM::Result CPF_STDCALL KeyboardDevice::GetModifiers(Platform::Desktop::KeyModifier* modifiers)
{
	if (modifiers)
	{
		*modifiers = Platform::Desktop::KeyModifier::eNone;
		SDL_Keymod mods = SDL_GetModState();
		if (mods & KMOD_LSHIFT) *modifiers |= Platform::Desktop::KeyModifier::eLeftShift;
		if (mods & KMOD_RSHIFT) *modifiers |= Platform::Desktop::KeyModifier::eRightShift;
		if (mods & KMOD_LALT) *modifiers |= Platform::Desktop::KeyModifier::eLeftAlt;
		if (mods & KMOD_RALT) *modifiers |= Platform::Desktop::KeyModifier::eRightAlt;
		if (mods & KMOD_LCTRL) *modifiers |= Platform::Desktop::KeyModifier::eLeftControl;
		if (mods & KMOD_RCTRL) *modifiers |= Platform::Desktop::KeyModifier::eRightControl;
		if (mods & KMOD_LGUI) *modifiers |= Platform::Desktop::KeyModifier::eLeftOS;
		if (mods & KMOD_RGUI) *modifiers |= Platform::Desktop::KeyModifier::eRightOS;
		if (mods & KMOD_NUM) *modifiers |= Platform::Desktop::KeyModifier::eNumLock;
		if (mods & KMOD_CAPS) *modifiers |= Platform::Desktop::KeyModifier::eCaps;
		if (mods & KMOD_MODE) *modifiers |= Platform::Desktop::KeyModifier::eMode;
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
