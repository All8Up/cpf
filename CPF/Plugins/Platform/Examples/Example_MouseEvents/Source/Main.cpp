//////////////////////////////////////////////////////////////////////////
#include "CPF/Plugin.hpp"
#include "CPF/Logging.hpp"
#include "CPF/Application.hpp"
#include "CPF/IO/File.hpp"
#include "CPF/IO/Directory.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "CPF/Platform/iDesktop.hpp"
#include "CPF/Platform/Desktop/iWindow.hpp"
#include "CPF/Platform/Desktop/iEventLoop.hpp"

using namespace CPF;

/** @brief A basic windowed application. */
class MouseEventsApp : public GOM::tUnknown<iApplication>
{
public:
	MouseEventsApp(Plugin::iRegistry* registry)
		: mpRegistry(registry)
	{}

	// Run your application here and return the integral value the process will exit with.
	int32_t Run() override
	{
		// Setup initial working directory to be in the
		// resources directory.
		{
			auto exePath = IO::File::GetExecutableFilePath();
			exePath += "../resources/";
			IO::Directory::SetWorkingDirectory(exePath);
		}

		// Load the platform plugin, create a platform and event loop then a window.
		IntrusivePtr<Platform::iDesktop> platform;
		IntrusivePtr<Platform::Desktop::iEventLoop> events;
		IntrusivePtr<Platform::Desktop::iWindow> window;

		Platform::Desktop::WindowDesc desc = {
			"Hello Mouse Events",
			50, 50,
			400, 400,
			Platform::Desktop::WindowFlags::eNone
		};

		if (GOM::Succeeded(mpRegistry->Load("./plugins/PlatformDesktopSDL2.cfp")) &&
			GOM::Succeeded(mpRegistry->Create(nullptr, Platform::iDesktop::kCID, Platform::iDesktop::kIID, platform.AsVoidPP())) &&
			GOM::Succeeded(mpRegistry->Create(nullptr, Platform::Desktop::iEventLoop::kCID, Platform::Desktop::iEventLoop::kIID, events.AsVoidPP())) &&
			(window = IntrusivePtr<Platform::Desktop::iWindow>(platform->CreateWindow(&desc).TryOK()))
			)
		{
			// Hook the window events.
			window->OnEvent(Platform::Desktop::iWindow::MouseMove::kID, &MouseEventsApp::OnMouseMove, this);
			window->OnEvent(Platform::Desktop::iWindow::MouseButtonDown::kID, &MouseEventsApp::OnMouseButtonDown, this);
			window->OnEvent(Platform::Desktop::iWindow::MouseButtonUp::kID, &MouseEventsApp::OnMouseButtonUp, this);
			window->OnEvent(Platform::Desktop::iWindow::MouseWheel::kID, &MouseEventsApp::OnMouseWheel, this);

			// Run the application event loop until quit is received.
			events->Run();
			return 0;
		}
		return -1;
	}

private:
	static void OnMouseMove(void*, const void* data)
	{
		//MouseEventsApp& self = *reinterpret_cast<MouseEventsApp*>(context);
		const Platform::Desktop::iWindow::MouseMove& mouseMove = *reinterpret_cast<const Platform::Desktop::iWindow::MouseMove*>(data);
		CPF_LOG(MouseEvent, Info) << "Mouse Position: " << mouseMove.x << ", " << mouseMove.y;
	}
	static void OnMouseButtonDown(void*, const void* data)
	{
		const Platform::Desktop::iWindow::MouseButtonDown& mouseDown = *reinterpret_cast<const Platform::Desktop::iWindow::MouseButtonDown*>(data);
		CPF_LOG(MouseEvent, Info) << "Mouse Button Down: " << mouseDown.x << ", " << mouseDown.y << " - " << int32_t(mouseDown.button);
	}
	static void OnMouseButtonUp(void*, const void* data)
	{
		const Platform::Desktop::iWindow::MouseButtonUp& mouseUp = *reinterpret_cast<const Platform::Desktop::iWindow::MouseButtonUp*>(data);
		CPF_LOG(MouseEvent, Info) << "Mouse Button Up: " << mouseUp.x << ", " << mouseUp.y << " - " << int32_t(mouseUp.button);
	}
	static void OnMouseWheel(void*, const void* data)
	{
		const Platform::Desktop::iWindow::MouseWheel& mouseWheel = *reinterpret_cast<const Platform::Desktop::iWindow::MouseWheel*>(data);
		CPF_LOG(MouseEvent, Info) << "Mouse Wheel Change: " << mouseWheel.x << ", " << mouseWheel.y;
	}

	IntrusivePtr<Plugin::iRegistry> mpRegistry;
};

// Register the application plugin.
CPF_APPLICATION(MouseEventsApp);
