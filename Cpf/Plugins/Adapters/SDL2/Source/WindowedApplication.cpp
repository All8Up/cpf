//////////////////////////////////////////////////////////////////////////
#include "WindowedApplication.hpp"
#include "Application/MouseButton.hpp"
#include "Application/iApplicationMain.hpp"
#include "Application/iInputManager.hpp"
#include "Plugin/iRegistry.hpp"
#include "Logging/Logging.hpp"
#include "SDL2/CIDs.hpp"

using namespace Cpf;
using namespace SDL2;

WindowedApp::WindowedApp(COM::iUnknown*)
	: mRunning(false)
	, mpApplicationMain(nullptr)
	, mpRegistry(nullptr)
{
	CPF_INIT_LOG(Application);
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
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

COM::Result CPF_STDCALL WindowedApp::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iApplication::kIID.GetID():
			*outIface = static_cast<iApplication*>(this);
			break;
		case iWindowedApplication::kIID.GetID():
			*outIface = static_cast<iWindowedApplication*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL WindowedApp::Initialize(Plugin::iRegistry* regy, iApplicationMain* appMain)
{
	if (regy && appMain)
	{
		mpRegistry = regy;
		mpApplicationMain = appMain;

		regy->Create(nullptr, kInputManagerCID, iInputManager::kIID, mpInputManager.AsVoidPP());

		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL WindowedApp::Run()
{
	if (mpApplicationMain)
	{
		mRunning = true;
		auto result = mpApplicationMain->Main(this);
		mRunning = false;
		return result;
	}
	return COM::kNotInitialized;
}

COM::Result CPF_STDCALL WindowedApp::Shutdown()
{
	if (mpApplicationMain)
	{
		mpApplicationMain->Shutdown();
		return COM::kOK;
	}
	return COM::kNotInitialized;
}

Plugin::iRegistry* CPF_STDCALL WindowedApp::GetRegistry()
{
	return mpRegistry;
}

Events::Emitter* CPF_STDCALL WindowedApp::GetEmitter()
{
	return &mEmitter;
}

bool CPF_STDCALL WindowedApp::IsRunning()
{
	return mRunning;
}

void CPF_STDCALL WindowedApp::Quit()
{
	mRunning = false;
}

COM::Result CPF_STDCALL WindowedApp::Poll()
{
	if (IsRunning())
	{
		SDL_Event event;
		while (SDL_PollEvent(&event) == 1)
		{
			_HandleEvent(event);
		}
		return COM::kOK;
	}
	return COM::kNotRunning;
}

COM::Result CPF_STDCALL WindowedApp::Wait()
{
	if (IsRunning())
	{
		SDL_Event event;
		if (SDL_WaitEvent(&event))
		{
			_HandleEvent(event);
			return COM::kOK;
		}
	}
	return COM::kNotRunning;
}

COM::Result CPF_STDCALL WindowedApp::Create(const WindowDesc& desc, iWindow** outWindow)
{
	iWindow* win = nullptr;
	int32_t classCount = 0;
	GetRegistry()->GetClasses(iWindow::kIID, &classCount, nullptr);
	Vector<COM::ClassID> classes(classCount);
	GetRegistry()->GetClasses(iWindow::kIID, &classCount, classes.data());
	if (COM::Succeeded(GetRegistry()->Create(nullptr, classes[0], iWindow::kIID, reinterpret_cast<void**>(&win))))
	{
		if (win && win->Initialize(&desc))
			*outWindow = win;
		else
			*outWindow = nullptr;
	}
	return (win != nullptr) ? COM::kOK : COM::kOutOfMemory;
}

iInputManager* CPF_STDCALL WindowedApp::GetInputManager()
{
	return mpInputManager;
}

void WindowedApp::_HandleEvent(SDL_Event& event)
{
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
			int32_t x = event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED ? -event.wheel.x : event.wheel.x;
			int32_t y = event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED ? -event.wheel.y : event.wheel.y;
			window->GetEmitter()->Emit<iWindow::OnMouseWheel>(x, y);
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
				{
					iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
					window->GetEmitter()->Emit<iWindow::OnShow>();
					CPF_LOG(Application, Trace) << "Window shown.";
				}
				break;

			case SDL_WINDOWEVENT_HIDDEN:
				{
					iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
					window->GetEmitter()->Emit<iWindow::OnHide>();
					CPF_LOG(Application, Trace) << "Window hidden.";
				}
				break;

			case SDL_WINDOWEVENT_EXPOSED:
				{
					iWindow* window = reinterpret_cast<iWindow*>(SDL_GetWindowData(SDL_GetWindowFromID(event.window.windowID), "iWindow"));
					window->GetEmitter()->Emit<iWindow::OnExposed>();
					CPF_LOG(Application, Trace) << "Window exposed.";
				}
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
				break;

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
