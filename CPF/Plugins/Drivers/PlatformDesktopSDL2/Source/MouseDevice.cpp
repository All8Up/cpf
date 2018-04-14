//////////////////////////////////////////////////////////////////////////
#include "MouseDevice.hpp"
#include "CPF/Platform/Desktop/MouseButton.hpp"
#include "SDL.h"

using namespace CPF;
using namespace SDL2;


MouseDevice::MouseDevice(Plugin::iRegistry*, GOM::iUnknown*)
{}

MouseDevice::~MouseDevice()
{}

GOM::Result CPF_STDCALL MouseDevice::GetButtonState(Platform::Desktop::MouseButton* state)
{
	if (state)
	{
		*state = Platform::Desktop::MouseButton::eNone;
		uint32_t button = SDL_GetMouseState(nullptr, nullptr);
		if (button & SDL_BUTTON(SDL_BUTTON_LEFT)) *state |= Platform::Desktop::MouseButton::eLeft;
		if (button & SDL_BUTTON(SDL_BUTTON_RIGHT)) *state |= Platform::Desktop::MouseButton::eRight;
		if (button & SDL_BUTTON(SDL_BUTTON_MIDDLE)) *state |= Platform::Desktop::MouseButton::eMiddle;
		if (button & SDL_BUTTON(SDL_BUTTON_X1)) *state |= Platform::Desktop::MouseButton::eX1;
		if (button & SDL_BUTTON(SDL_BUTTON_X2)) *state |= Platform::Desktop::MouseButton::eX2;
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
