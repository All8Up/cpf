//////////////////////////////////////////////////////////////////////////
#include "Window.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/Std/Move.hpp"
#include "CPF/Platform/Desktop/OSWindowData.hpp"
#include <SDL_syswm.h>

using namespace CPF;
using namespace SDL2;

Window::~Window()
{
	SDL_DestroyWindow(mpWindow);
}

GOM::Result Window::Initialize(const Platform::Desktop::WindowDesc* desc)
{
	int px = (desc->mX & Platform::Desktop::kDesktopCentered) != Platform::Desktop::kDesktopCentered ? desc->mX : SDL_WINDOWPOS_CENTERED_DISPLAY(desc->mX & 15);
	int py = (desc->mY & Platform::Desktop::kDesktopCentered) != Platform::Desktop::kDesktopCentered ? desc->mY : SDL_WINDOWPOS_CENTERED_DISPLAY(desc->mY & 15);

	auto sdlwin = SDL_CreateWindow(
		desc->mpTitle,
		px,
		py,
		desc->mWidth,
		desc->mHeight,
		Uint32(desc->mFlags)
	);

	SDL_SetWindowData(sdlwin, "iWindow", static_cast<iWindow*>(this));
	mpWindow = sdlwin;

	// TODO: Uses generic error, be more specific.
	return (mpWindow != nullptr) ? GOM::kOK : GOM::kError;
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
	SDL_GetWindowPosition(mpWindow, x, y);
}

void CPF_STDCALL Window::SetSize(int32_t x, int32_t y)
{
	SDL_SetWindowSize(mpWindow, x, y);
}

void CPF_STDCALL Window::GetSize(int32_t* x, int32_t* y)
{
	SDL_GetWindowSize(mpWindow, x, y);
}

void CPF_STDCALL Window::GetClientArea(int32_t* x, int32_t* y)
{
	SDL_GL_GetDrawableSize(mpWindow, x, y);
}

GOM::Result CPF_STDCALL Window::GetOSData(Platform::Desktop::OSWindowData* data)
{
	if (data)
	{
		struct SDL_SysWMinfo windowInfo;

#if CPF_TARGET_WINDOWS
		SDL_VERSION(&windowInfo.version);
		SDL_GetWindowWMInfo(mpWindow, &windowInfo);
		data->mHwnd = windowInfo.info.win.window;
		data->mHDC = windowInfo.info.win.hdc;
#endif
#if CPF_TARGET_DARWIN
		SDL_VERSION(&windowInfo.version);
		SDL_GetWindowWMInfo(mpWindow, &windowInfo);
		result.mpView = windowInfo.info.cocoa.window;
#endif
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
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

GOM::Result CPF_STDCALL Window::OnEvent(int64_t id, GOM::EventHandler cb, void* context)
{
	return mEmitter.OnEvent(id, cb, context);
}

GOM::Result CPF_STDCALL Window::RemoveEvent(int64_t id, GOM::EventHandler cb, void* context)
{
	return mEmitter.RemoveEvent(id, cb, context);
}

GOM::Result CPF_STDCALL Window::EmitEvent(int64_t id, size_t eventSize, const void* eventData) const
{
	return mEmitter.EmitEvent(id, eventSize, eventData);
}

GOM::Result CPF_STDCALL Window::SetEventSink(GOM::iEventSink* sink)
{
    return mEmitter.SetEventSink(sink);
}
