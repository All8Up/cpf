//////////////////////////////////////////////////////////////////////////
#include "Adapter/WindowedApp.hpp"
#include "Adapter/Window.hpp"
#include "Logging/Logging.hpp"
#include "Application/MouseButton.hpp"
#include "Application/WindowFlags.hpp"
#include "SDL_syswm.h"

using namespace Cpf;
using namespace Adapter;

//////////////////////////////////////////////////////////////////////////
int32_t WindowFlags(int32_t flags)
{
	int32_t result = 0;
	if (flags&WindowFlags::eFullscreen)			result |= SDL_WINDOW_FULLSCREEN;
	if (flags&WindowFlags::eSupportOpenGL)		result |= SDL_WINDOW_OPENGL;
	if (flags&WindowFlags::eShown)				result |= SDL_WINDOW_SHOWN;
	if (flags&WindowFlags::eHidden)				result |= SDL_WINDOW_HIDDEN;
	if (flags&WindowFlags::eBorderless)			result |= SDL_WINDOW_BORDERLESS;
	if (flags&WindowFlags::eResizable)			result |= SDL_WINDOW_RESIZABLE;
	if (flags&WindowFlags::eMinimized)			result |= SDL_WINDOW_MINIMIZED;
	if (flags&WindowFlags::eMaximized)			result |= SDL_WINDOW_MAXIMIZED;
	if (flags&WindowFlags::eInputGrabbed)		result |= SDL_WINDOW_INPUT_GRABBED;
	if (flags&WindowFlags::eInputFocus)			result |= SDL_WINDOW_INPUT_FOCUS;
	if (flags&WindowFlags::eMouseFocus)			result |= SDL_WINDOW_MOUSE_FOCUS;
	if (flags&WindowFlags::eFullscreenDesktop)	result |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (flags&WindowFlags::eAllowHDPI)			result |= SDL_WINDOW_ALLOW_HIGHDPI;
	if (flags&WindowFlags::eMouseCapture)		result |= SDL_WINDOW_MOUSE_CAPTURE;

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

	// TODO: Should move into the render device abstraction.  I.e. this should not be done for DX based devices.
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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
	iWindow* win = new Window(
		SDL_CreateWindow(
			desc.mTitle.c_str(),
			desc.mPosition.x,
			desc.mPosition.y,
			desc.mSize.x,
			desc.mSize.y,
			Uint32(desc.mFlags)
		)
	);
	if (win)
		*outWindow = win;
	else
		*outWindow = nullptr;
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
		break;

	case SDL_MOUSEMOTION:
	{
		iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.motion.windowID), "iWindow"));
		window->GetEmitter().Emit<iWindow::OnMouseMove>(event.motion.x, event.motion.y);
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
		window->GetEmitter().Emit<iWindow::OnButtonDown>(id, event.button.x, event.button.y);

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
		window->GetEmitter().Emit<iWindow::OnButtonUp>(id, event.button.x, event.button.y);

		char buffer[1024];
		::sprintf(buffer, "Mouse up: Button(%d) X(%d) Y(%d)", event.button.button, event.button.x, event.button.y);
		CPF_LOG(Application, Trace) << buffer;
	}
	break;

	case SDL_MOUSEWHEEL:
	{
		iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.wheel.windowID), "iWindow"));
		window->GetEmitter().Emit<iWindow::OnMouseWheel>();

		char buffer[1024];
		::sprintf(buffer, "Mouse up: Direction(%d) X(%d) Y(%d)", event.wheel.direction, event.wheel.x, event.wheel.y);
		CPF_LOG(Application, Trace) << buffer;
	}
	break;

	case SDL_KEYDOWN:
	{
		iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.key.windowID), "iWindow"));
		window->GetEmitter().Emit<iWindow::OnKeyDown>((KeyCode)event.key.keysym.sym);
	}
	break;

	case SDL_WINDOWEVENT:
	{
		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			Quit();
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
			CPF_LOG(Application, Trace) << "Window moved.";
			break;

		case SDL_WINDOWEVENT_RESIZED:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			window->GetEmitter().Emit<iWindow::OnResized>(event.window.data1, event.window.data2);
		}
		break;

		case SDL_WINDOWEVENT_SIZE_CHANGED:
			CPF_LOG(Application, Trace) << "Window size changed.";
			break;

		case SDL_WINDOWEVENT_MINIMIZED:
			CPF_LOG(Application, Trace) << "Window minimized.";
			break;

		case SDL_WINDOWEVENT_MAXIMIZED:
			CPF_LOG(Application, Trace) << "Window maximized.";
			break;

		case SDL_WINDOWEVENT_RESTORED:
			CPF_LOG(Application, Trace) << "Window restored.";
			break;

		case SDL_WINDOWEVENT_ENTER:
			CPF_LOG(Application, Trace) << "Window entered.";
			break;

		case SDL_WINDOWEVENT_LEAVE:
			CPF_LOG(Application, Trace) << "Window left.";
			break;

		case SDL_WINDOWEVENT_FOCUS_GAINED:
			CPF_LOG(Application, Trace) << "Window focus gained.";
			break;

		case SDL_WINDOWEVENT_FOCUS_LOST:
			CPF_LOG(Application, Trace) << "Window focus lost.";
			break;
		}
	}
	}
}
