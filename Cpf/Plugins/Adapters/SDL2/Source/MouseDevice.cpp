//////////////////////////////////////////////////////////////////////////
#include "MouseDevice.hpp"
#include "Application/MouseButton.hpp"
#include "SDL.h"

using namespace Cpf;
using namespace SDL2;


MouseDevice::MouseDevice(COM::iUnknown*)
{}

MouseDevice::~MouseDevice()
{}

COM::Result CPF_STDCALL MouseDevice::QueryInterface(COM::InterfaceID id, void** outIface)
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
		case iMouseDevice::kIID.GetID():
			*outIface = static_cast<iMouseDevice*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL MouseDevice::GetButtonState(MouseButton* state)
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
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL MouseDevice::GetPosition(int32_t* x, int32_t* y)
{
	if (x == nullptr && y == nullptr)
		return COM::kInvalidParameter;

	int xx, yy;
	SDL_GetMouseState(&xx, &yy);
	if (x) *x = int32_t(xx);
	if (y) *y = int32_t(yy);

	return COM::kOK;
}
