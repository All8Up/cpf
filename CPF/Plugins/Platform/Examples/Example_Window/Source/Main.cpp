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
class WindowedApp : public GOM::tUnknown<iApplication>
{
public:
	WindowedApp(Plugin::iRegistry* registry)
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

		// Load the platform driver, get the event loop and then create a window.
		IntrusivePtr<Platform::iDesktop> desktop;
		IntrusivePtr<Platform::Desktop::iEventLoop> events;
		IntrusivePtr<Platform::Desktop::iWindow> window;

		Platform::Desktop::WindowDesc windowDesc = {
			"Hello Window",
			50, 50,
			400, 400,
			Platform::Desktop::WindowFlags::eNone
		};

		if (GOM::Succeeded(mpRegistry->Load("./plugins/PlatformDesktopSDL2.cfp")) &&
			GOM::Succeeded(mpRegistry->Create(nullptr, Platform::iDesktop::kCID, Platform::iDesktop::kIID, desktop.AsVoidPP())) &&
			GOM::Succeeded(mpRegistry->Create(nullptr, Platform::Desktop::iEventLoop::kCID, Platform::Desktop::iEventLoop::kIID, events.AsVoidPP()))
			)
		{
			if (window = IntrusivePtr<Platform::Desktop::iWindow>(desktop->CreateWindow(&windowDesc).TryOK()))
			{
				// Run the application event loop until quit is received.
				events->Run();
				return 0;
			}
		}
		return -1;
	}

private:
	IntrusivePtr<Plugin::iRegistry> mpRegistry;
};

// Register the application plugin.
CPF_APPLICATION(WindowedApp);
