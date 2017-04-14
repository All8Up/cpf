//////////////////////////////////////////////////////////////////////////
#include "Adapter/WindowedApp.hpp"
#include "Adapter/Window.hpp"
#include "Logging/Logging.hpp"
#include "Application/MouseButton.hpp"
#include "Application/WindowFlags.hpp"
#include "Application/WindowDesc.hpp"
#include "Adapter/Window.hpp"
#include "Plugin/iClassInstance.hpp"
#include "SDL_syswm.h"

using namespace Cpf;
using namespace Adapter;

//////////////////////////////////////////////////////////////////////////
int32_t WindowFlags(Cpf::WindowFlags flags)
{
	int32_t result = 0;
	if ((flags&WindowFlags::eFullscreen) == WindowFlags::eFullscreen)				result |= SDL_WINDOW_FULLSCREEN;
	if ((flags&WindowFlags::eSupportOpenGL) == WindowFlags::eSupportOpenGL)			result |= SDL_WINDOW_OPENGL;
	if ((flags&WindowFlags::eShown) == WindowFlags::eShown)							result |= SDL_WINDOW_SHOWN;
	if ((flags&WindowFlags::eHidden) == WindowFlags::eHidden)						result |= SDL_WINDOW_HIDDEN;
	if ((flags&WindowFlags::eBorderless) == WindowFlags::eBorderless)				result |= SDL_WINDOW_BORDERLESS;
	if ((flags&WindowFlags::eResizable) == WindowFlags::eResizable)					result |= SDL_WINDOW_RESIZABLE;
	if ((flags&WindowFlags::eMinimized) == WindowFlags::eMinimized)					result |= SDL_WINDOW_MINIMIZED;
	if ((flags&WindowFlags::eMaximized) == WindowFlags::eMaximized)					result |= SDL_WINDOW_MAXIMIZED;
	if ((flags&WindowFlags::eInputGrabbed) == WindowFlags::eInputGrabbed)			result |= SDL_WINDOW_INPUT_GRABBED;
	if ((flags&WindowFlags::eInputFocus) == WindowFlags::eInputFocus)				result |= SDL_WINDOW_INPUT_FOCUS;
	if ((flags&WindowFlags::eMouseFocus) == WindowFlags::eMouseFocus)				result |= SDL_WINDOW_MOUSE_FOCUS;
	if ((flags&WindowFlags::eFullscreenDesktop) == WindowFlags::eFullscreenDesktop)	result |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if ((flags&WindowFlags::eAllowHDPI) == WindowFlags::eAllowHDPI)					result |= SDL_WINDOW_ALLOW_HIGHDPI;
	if ((flags&WindowFlags::eMouseCapture) == WindowFlags::eMouseCapture)			result |= SDL_WINDOW_MOUSE_CAPTURE;

	return result;
}

//////////////////////////////////////////////////////////////////////////
WindowedApp::WindowedApp()
{
	CPF_INIT_LOG(Application)
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

	GetRegistry()->Install(kSDL2WindowCID, new Plugin::tSimpleClassInstance<Window>());
}

WindowedApp::~WindowedApp()
{
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	SDL_Quit();
	CPF_DROP_LOG(Application);
}

bool WindowedApp::Poll()
{
	if (IsRunning())
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)==1)
		{
			_HandleEvent(event);
		}
		return true;
	}
	return false;
}

bool WindowedApp::Wait()
{
	if (IsRunning())
	{
		SDL_Event event;
		if (SDL_WaitEvent(&event))
		{
			_HandleEvent(event);
			return true;
		}
	}
	return false;
}

bool WindowedApp::Create(const WindowDesc& desc, iWindow** outWindow)
{
	Window* win = nullptr;
	if (COM::Succeeded(GetRegistry()->Create(nullptr, kSDL2WindowCID, iWindow::kIID, reinterpret_cast<void**>(&win))))
	{
		int px = (desc.mPosition.x & 0xFF100000) != 0xFF100000 ? desc.mPosition.x : SDL_WINDOWPOS_CENTERED_DISPLAY(desc.mPosition.x & 15);
		int py = (desc.mPosition.y & 0xFF100000) != 0xFF100000 ? desc.mPosition.y : SDL_WINDOWPOS_CENTERED_DISPLAY(desc.mPosition.y & 15);

		auto sdlwin = SDL_CreateWindow(
			desc.mTitle.c_str(),
			px,
			py,
			desc.mSize.x,
			desc.mSize.y,
			Uint32(desc.mFlags)
		);
		if (win && sdlwin && win->Initialize(sdlwin))
			*outWindow = win;
		else
			*outWindow = nullptr;
	}
	return win != nullptr;
}

void WindowedApp::AddRawInputHook(RawInputHook hook, void* userContext)
{
	mInputHooks.push_back(HookPair(hook, userContext));
}

void WindowedApp::RemoveRawInputHook(RawInputHook hook)
{
	for (auto ibegin = mInputHooks.begin(), iend = mInputHooks.end(); ibegin != iend; ++ibegin)
	{
		if (ibegin->first == hook)
		{
			mInputHooks.erase(ibegin);
			return;
		}
	}
}

void WindowedApp::_HandleEvent(SDL_Event& event)
{
	for (auto& it : mInputHooks)
	{
		if ((*it.first)(it.second, &event))
		{
			// Input chain used the input.
			return;
		}
	}
	switch (event.type)
	{
	case SDL_QUIT:
		Quit();
		break;

	case SDL_MOUSEMOTION:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.motion.windowID), "iWindow"));
			window->GetEmitter()->Emit<iWindow::OnMouseMove>(event.motion.x, event.motion.y);
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.button.windowID), "iWindow"));
			MouseButton id = MouseButton::eLeft;
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT: id = MouseButton::eLeft; break;
			case SDL_BUTTON_MIDDLE: id = MouseButton::eMiddle; break;
			case SDL_BUTTON_RIGHT: id = MouseButton::eRight; break;
			case SDL_BUTTON_X1: id = MouseButton::eX1; break;
			case SDL_BUTTON_X2: id = MouseButton::eX2; break;
			}
			window->GetEmitter()->Emit<iWindow::OnButtonDown>(id, event.button.x, event.button.y);

			char buffer[1024];
			::sprintf(buffer, "Mouse button: Button(%d) X(%d) Y(%d)", event.button.button, event.button.x, event.button.y);
			CPF_LOG(Application, Trace) << buffer;
		}
		break;

	case SDL_MOUSEBUTTONUP:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.button.windowID), "iWindow"));
			MouseButton id;
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT: id = MouseButton::eLeft; break;
			case SDL_BUTTON_MIDDLE: id = MouseButton::eMiddle; break;
			case SDL_BUTTON_RIGHT: id = MouseButton::eRight; break;
			case SDL_BUTTON_X1: id = MouseButton::eX1; break;
			case SDL_BUTTON_X2: id = MouseButton::eX2; break;
			default:
				id = MouseButton::eLeft;
				CPF_ASSERT_ALWAYS;
				break;
			}
			window->GetEmitter()->Emit<iWindow::OnButtonUp>(id, event.button.x, event.button.y);

			char buffer[1024];
			::sprintf(buffer, "Mouse up: Button(%d) X(%d) Y(%d)", event.button.button, event.button.x, event.button.y);
			CPF_LOG(Application, Trace) << buffer;
		}
		break;

	case SDL_MOUSEWHEEL:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.wheel.windowID), "iWindow"));
			window->GetEmitter()->Emit<iWindow::OnMouseWheel>();

			char buffer[1024];
			::sprintf(buffer, "Mouse up: Direction(%d) X(%d) Y(%d)", event.wheel.direction, event.wheel.x, event.wheel.y);
			CPF_LOG(Application, Trace) << buffer;
		}
		break;

	case SDL_KEYDOWN:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.key.windowID), "iWindow"));
			window->GetEmitter()->Emit<iWindow::OnKeyDown>((KeyCode)event.key.keysym.sym);
		}
		break;

	case SDL_WINDOWEVENT:
	{
		switch (event.window.event)
		{
			case SDL_WINDOWEVENT_CLOSE:
			{
				iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
				window->GetEmitter()->Emit<iWindow::OnClose>();
			}
			break;

		case SDL_WINDOWEVENT_SHOWN:
			CPF_LOG(Application, Trace) << "Window shown.";
			break;

		case SDL_WINDOWEVENT_HIDDEN:
			CPF_LOG(Application, Trace) << "Window hidden.";
			break;

		case SDL_WINDOWEVENT_EXPOSED:
			CPF_LOG(Application, Trace) << "Window exposed.";
			break;

		case SDL_WINDOWEVENT_MOVED:
			{
				iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
				window->GetEmitter()->Emit<iWindow::OnMoved>(event.window.data1, event.window.data2);
				CPF_LOG(Application, Trace) << "Window moved.";
			}
			break;

		case SDL_WINDOWEVENT_RESIZED:
			{
				iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
				window->GetEmitter()->Emit<iWindow::OnResize>(event.window.data1, event.window.data2);
			}
			break;

		case SDL_WINDOWEVENT_SIZE_CHANGED:
			{
				iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
				window->GetEmitter()->Emit<iWindow::OnResize>(event.window.data1, event.window.data2);
				CPF_LOG(Application, Trace) << "Window size changed.";
			}

		case SDL_WINDOWEVENT_MINIMIZED:
			{
				iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
				window->GetEmitter()->Emit<iWindow::OnMinimized>();
				CPF_LOG(Application, Trace) << "Window minimized.";
			}
			break;

		case SDL_WINDOWEVENT_MAXIMIZED:
			{
				iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
				window->GetEmitter()->Emit<iWindow::OnMinimized>();
				CPF_LOG(Application, Trace) << "Window minimized.";
			}
			break;

		case SDL_WINDOWEVENT_RESTORED:
			{
				iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
				window->GetEmitter()->Emit<iWindow::OnRestored>();
				CPF_LOG(Application, Trace) << "Window restored.";
			}
			break;

		case SDL_WINDOWEVENT_ENTER:
			{
				iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
				window->GetEmitter()->Emit<iWindow::OnMouseEnter>();
				CPF_LOG(Application, Trace) << "Mouse entered.";
			}
			break;

		case SDL_WINDOWEVENT_LEAVE:
			{
				iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
				window->GetEmitter()->Emit<iWindow::OnMouseLeave>();
				CPF_LOG(Application, Trace) << "Mouse left.";
			}
			break;

		case SDL_WINDOWEVENT_FOCUS_GAINED:
			{
				iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
				window->GetEmitter()->Emit<iWindow::OnFocusGained>();
				CPF_LOG(Application, Trace) << "Focus gained.";
			}
			break;

		case SDL_WINDOWEVENT_FOCUS_LOST:
			{
				iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
				window->GetEmitter()->Emit<iWindow::OnFocusLost>();
				CPF_LOG(Application, Trace) << "Focus lost.";
			}
			break;
		}
	}
	}
}
