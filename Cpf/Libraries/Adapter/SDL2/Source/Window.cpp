//////////////////////////////////////////////////////////////////////////
#include <SDL_syswm.h>
#include "Adapter/Window.hpp"
#include "Logging/Logging.hpp"
#include "SDL_syswm.h"

using namespace Cpf;
using namespace Adapter;

//////////////////////////////////////////////////////////////////////////
Window::Window()
	: mpWindow(nullptr)
{
	CPF_LOG(Application, Info) << "Creating window.";
}

Window::~Window()
{
	CPF_LOG(Application, Info) << "Destroying window.";
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

bool Window::Initialize(SDL_Window* win)
{
	mpWindow = win;
	SDL_SetWindowData(win, "iWindow", this);
	return win!=nullptr;
}

Math::Vector2i Window::GetClientArea() const
{
	int hw, hh;
	SDL_GL_GetDrawableSize(mpWindow, &hw, &hh);
	return Math::Vector2i(hw, hh);
}

OSWindowData Window::GetOSWindowData() const
{
	OSWindowData result;
	SDL_SysWMinfo windowInfo;

#if CPF_TARGET_WINDOWS
	SDL_VERSION(&windowInfo.version);
	SDL_GetWindowWMInfo(mpWindow, &windowInfo);
	result.mHwnd = windowInfo.info.win.window;
	result.mHDC = windowInfo.info.win.hdc;
#endif
#if CPF_TARGET_DARWIN
	SDL_VERSION(&windowInfo.version);
	SDL_GetWindowWMInfo(mpWindow, &windowInfo);
	result.mpView = windowInfo.info.cocoa.window;
#endif

	return result;
}

SDL_Window* Window::GetSDLWindow() const
{
	return mpWindow;
}
