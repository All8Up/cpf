//////////////////////////////////////////////////////////////////////////
#include <SDL_syswm.h>
#include "Window.hpp"
#include "Application/WindowDesc.hpp"
#include "Logging/Logging.hpp"
#include "SDL_syswm.h"
#include "Application/OSWindowData.hpp"

using namespace Cpf;
using namespace SDL2;

//////////////////////////////////////////////////////////////////////////
Window::Window()
	: mpWindow(nullptr)
{
}

Window::~Window()
{
	SDL_DestroyWindow(mpWindow);
}

COM::Result CPF_STDCALL Window::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iWindow::kIID.GetID():
			*outIface = static_cast<iWindow*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

bool Window::Initialize(const WindowDesc* desc)
{
	int px = (desc->mPosition.x & 0xFF100000) != 0xFF100000 ? desc->mPosition.x : SDL_WINDOWPOS_CENTERED_DISPLAY(desc->mPosition.x & 15);
	int py = (desc->mPosition.y & 0xFF100000) != 0xFF100000 ? desc->mPosition.y : SDL_WINDOWPOS_CENTERED_DISPLAY(desc->mPosition.y & 15);

	auto sdlwin = SDL_CreateWindow(
		desc->mTitle.c_str(),
		px,
		py,
		desc->mSize.x,
		desc->mSize.y,
		Uint32(desc->mFlags)
	);

	SDL_SetWindowData(sdlwin, "iWindow", static_cast<iWindow*>(this));
	mpWindow = sdlwin;
	return mpWindow != nullptr;
}

void CPF_STDCALL Window::SetTitle(const char* title)
{
	SDL_SetWindowTitle(mpWindow, title);
}

void CPF_STDCALL Window::SetPosition(int32_t x, int32_t y)
{
	SDL_SetWindowPosition(mpWindow, x, y);
}

void CPF_STDCALL Window::GetPosition(int32_t* x, int32_t* y)
{
	int xx, yy;
	SDL_GetWindowPosition(mpWindow, &xx, &yy);
	*x = xx;
	*y = yy;
}

void CPF_STDCALL Window::SetSize(int32_t x, int32_t y)
{
	SDL_SetWindowSize(mpWindow, x, y);
}

void CPF_STDCALL Window::GetSize(int32_t* w, int32_t* h)
{
	int ww, hh;
	SDL_GetWindowSize(mpWindow, &ww, &hh);
	*w = ww;
	*h = hh;
}

void CPF_STDCALL Window::Minimize()
{
	SDL_MinimizeWindow(mpWindow);
}

void CPF_STDCALL Window::Maximize()
{
	SDL_MaximizeWindow(mpWindow);
}

void CPF_STDCALL Window::Restore()
{
	SDL_RestoreWindow(mpWindow);
}

COM::Result CPF_STDCALL Window::GetClientAreaSize(int32_t* w, int32_t* h)
{
	if (w && h)
	{
		int hw, hh;
		SDL_GL_GetDrawableSize(mpWindow, &hw, &hh);
		*w = hw;
		*h = hh;
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Window::GetOSData(OSWindowData* outData)
{
	if (outData)
	{
		SDL_SysWMinfo windowInfo;

#if CPF_TARGET_WINDOWS
		SDL_VERSION(&windowInfo.version);
		SDL_GetWindowWMInfo(mpWindow, &windowInfo);
		outData->mHwnd = windowInfo.info.win.window;
		outData->mHDC = windowInfo.info.win.hdc;
#endif
#if CPF_TARGET_DARWIN
		SDL_VERSION(&windowInfo.version);
		SDL_GetWindowWMInfo(mpWindow, &windowInfo);
		result.mpView = windowInfo.info.cocoa.window;
#endif
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

SDL_Window* Window::GetSDLWindow() const
{
	return mpWindow;
}
