//////////////////////////////////////////////////////////////////////////
#include "EventLoop.hpp"
#include "CPF/Logging.hpp"
#include "CPF/Platform/Desktop/iWindow.hpp"
#include "CPF/Platform/Desktop/MouseButton.hpp"
#include "CPF/Platform/Desktop/ScanCode.hpp"

using namespace CPF;
using namespace Platform;
using namespace Desktop;
using namespace SDL2;

GOM::Result EventLoop::Run()
{
	for (;;)
	{
		SDL_Event event;
		if (SDL_WaitEvent(&event) == 0)
			return GOM::kError;
		if (event.type == SDL_QUIT)
			return kQuit;
		_HandleEvent(event);
	}
}

GOM::Result EventLoop::Poll()
{
	SDL_Event event;
	const auto result = SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
		return kQuit;
	if (result != 0)
	{
		_HandleEvent(event);
		return GOM::kOK;
	}
	return GOM::kNone;
}

GOM::Result CPF_STDCALL EventLoop::PollTillEmpty()
{
	GOM::Result loopResult;
	while ((loopResult = Poll()) == GOM::kOK)
		;
	return loopResult;
}

void EventLoop::_HandleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
	{
		iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.motion.windowID), "iWindow"));
		iWindow::MouseMove data{ event.motion.x, event.motion.y };
		window->EmitEvent(iWindow::MouseMove::kID, sizeof(iWindow::MouseMove), &data);
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

		iWindow::MouseButtonDown data{ event.button.x, event.button.y, id };
		window->EmitEvent(iWindow::MouseButtonDown::kID, sizeof(iWindow::MouseButtonDown), &data);
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

		iWindow::MouseButtonUp data{ event.button.x, event.button.y, id };
		window->EmitEvent(iWindow::MouseButtonUp::kID, sizeof(iWindow::MouseButtonUp), &data);
	}
	break;

	case SDL_MOUSEWHEEL:
	{
		iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.wheel.windowID), "iWindow"));
		int32_t x = event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED ? -event.wheel.x : event.wheel.x;
		int32_t y = event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED ? -event.wheel.y : event.wheel.y;
		iWindow::MouseWheel data{ x, y };
		window->EmitEvent(iWindow::MouseWheel::kID, sizeof(iWindow::MouseWheel), &data);
	}
	break;

	case SDL_KEYUP:
	{
		iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.key.windowID), "iWindow"));
		iWindow::KeyDown data{ (ScanCode)event.key.keysym.scancode };
		window->EmitEvent(iWindow::KeyDown::kID, sizeof(iWindow::KeyDown), &data);
	}
	break;

	case SDL_KEYDOWN:
	{
		iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.key.windowID), "iWindow"));
		iWindow::KeyUp data{ (ScanCode)event.key.keysym.scancode };
		window->EmitEvent(iWindow::KeyUp::kID, sizeof(iWindow::KeyUp), &data);
	}
	break;

	case SDL_WINDOWEVENT:
	{
		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			window->EmitEvent(iWindow::Close::kID, sizeof(iWindow::Close), nullptr);
		}
		break;
		case SDL_WINDOWEVENT_SHOWN:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			window->EmitEvent(iWindow::Shown::kID, sizeof(iWindow::Shown), nullptr);
		}
		break;

		case SDL_WINDOWEVENT_HIDDEN:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			window->EmitEvent(iWindow::Hidden::kID, sizeof(iWindow::Hidden), nullptr);
		}
		break;

		case SDL_WINDOWEVENT_EXPOSED:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			window->EmitEvent(iWindow::Exposed::kID, sizeof(iWindow::Exposed), nullptr);
		}
		break;

		case SDL_WINDOWEVENT_MOVED:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			iWindow::Moved data{ event.window.data1, event.window.data2 };
			window->EmitEvent(iWindow::Moved::kID, sizeof(iWindow::Moved), &data);
		}
		break;

		case SDL_WINDOWEVENT_RESIZED:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			iWindow::Resized data{ event.window.data1, event.window.data2 };
			window->EmitEvent(iWindow::Resized::kID, sizeof(iWindow::Resized), &data);
		}
		break;

		case SDL_WINDOWEVENT_SIZE_CHANGED:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			iWindow::Resized data{ event.window.data1, event.window.data2 };
			window->EmitEvent(iWindow::Resized::kID, sizeof(iWindow::Resized), &data);
		}
		break;

		case SDL_WINDOWEVENT_MINIMIZED:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			window->EmitEvent(iWindow::Minimized::kID, sizeof(iWindow::Minimized), nullptr);
		}
		break;

		case SDL_WINDOWEVENT_MAXIMIZED:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			window->EmitEvent(iWindow::Maximized::kID, sizeof(iWindow::Maximized), nullptr);
		}
		break;

		case SDL_WINDOWEVENT_RESTORED:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			window->EmitEvent(iWindow::Restored::kID, sizeof(iWindow::Restored), nullptr);
		}
		break;

		case SDL_WINDOWEVENT_ENTER:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			window->EmitEvent(iWindow::Enter::kID, sizeof(iWindow::Enter), nullptr);
		}
		break;

		case SDL_WINDOWEVENT_LEAVE:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			window->EmitEvent(iWindow::Leave::kID, sizeof(iWindow::Leave), nullptr);
		}
		break;

		case SDL_WINDOWEVENT_FOCUS_GAINED:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			window->EmitEvent(iWindow::Focused::kID, sizeof(iWindow::Focused), nullptr);
		}
		break;

		case SDL_WINDOWEVENT_FOCUS_LOST:
		{
			iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
			window->EmitEvent(iWindow::Unfocused::kID, sizeof(iWindow::Unfocused), nullptr);
		}
		break;
		}
	}
	}
}
