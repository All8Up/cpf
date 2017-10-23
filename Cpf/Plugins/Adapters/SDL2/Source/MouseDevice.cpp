//////////////////////////////////////////////////////////////////////////
#include "MouseDevice.hpp"
#include "CPF/Application/MouseButton.hpp"
#include "SDL.h"

using namespace CPF;
using namespace SDL2;


MouseDevice::MouseDevice(Plugin::iRegistry*, GOM::iUnknown*)
{}

MouseDevice::~MouseDevice()
{}

GOM::Result CPF_STDCALL MouseDevice::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;
		case iInputDevice::kIID.GetID():
			*outIface = static_cast<iInputDevice*>(this);
			break;
		case iMouseDevice::kIID.GetID():
			*outIface = static_cast<iMouseDevice*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL MouseDevice::GetButtonState(MouseButton* state)
{
	if (state)
	{
		*state = MouseButton::eNone;
		uint32_t button = SDL_GetMouseState(nullptr, nullptr);
		if (button & SDL_BUTTON(SDL_BUTTON_LEFT)) *state |= MouseButton::eLeft;
		if (button & SDL_BUTTON(SDL_BUTTON_RIGHT)) *state |= MouseButton::eRight;
		if (button & SDL_BUTTON(SDL_BUTTON_MIDDLE)) *state |= MouseButton::eMiddle;
		if (button & SDL_BUTTON(SDL_BUTTON_X1)) *state |= MouseButton::eX1;
		if (button & SDL_BUTTON(SDL_BUTTON_X2)) *state |= MouseButton::eX2;
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL MouseDevice::GetPosition(int32_t* x, int32_t* y)
{
	if (x == nullptr && y == nullptr)
		return GOM::kInvalidParameter;

	int xx, yy;
	SDL_GetMouseState(&xx, &yy);
	if (x) *x = int32_t(xx);
	if (y) *y = int32_t(yy);

	return GOM::kOK;
}
