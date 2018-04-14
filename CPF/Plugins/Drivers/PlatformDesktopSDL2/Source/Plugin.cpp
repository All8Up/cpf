//////////////////////////////////////////////////////////////////////////
#include "CPF/Plugin/tClassFactory.hpp"
#include "CPF/Plugin.hpp"
#include "Platform.hpp"
#include "EventLoop.hpp"
#include "Window.hpp"
#include "Clipboard.hpp"
#include "MouseDevice.hpp"
#include "KeyboardDevice.hpp"
#include "SDL.h"

using namespace CPF;
using namespace Platform;

//////////////////////////////////////////////////////////////////////////
static Plugin::IID_CID sImplementations[] =
{
	{GOM::IID::eInvalid, GOM::CID::eInvalid}
};


//////////////////////////////////////////////////////////////////////////
static GOM::Result CPF_STDCALL Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		SDL_Init(SDL_INIT_VIDEO);
		if (GOM::Succeeded(registry->Install(iDesktop::kCID, new Plugin::tClassFactory<DesktopSDL2>())) &&
			GOM::Succeeded(registry->Install(Desktop::iEventLoop::kCID, new Plugin::tClassFactory<SDL2::EventLoop>())) &&
			GOM::Succeeded(registry->Install(Desktop::iClipboard::kCID, new Plugin::tClassFactory<SDL2::Clipboard>())) &&
			GOM::Succeeded(registry->Install(Desktop::iMouseDevice::kCID, new Plugin::tClassFactory<SDL2::MouseDevice>())) &&
			GOM::Succeeded(registry->Install(Desktop::iKeyboardDevice::kCID, new Plugin::tClassFactory<SDL2::KeyboardDevice>())))
		{
			return GOM::kOK;
		}
		return GOM::kError;
	}
	return GOM::kInvalidParameter;
}

static GOM::Result CPF_STDCALL Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->Remove(Desktop::iKeyboardDevice::kCID);
		registry->Remove(Desktop::iMouseDevice::kCID);
		registry->Remove(Desktop::iClipboard::kCID);
		registry->Remove(Desktop::iEventLoop::kCID);
		registry->Remove(iDesktop::kCID);
		SDL_Quit();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

CPF_REGISTER_PLUGIN(PlatformDesktopSDL2)
	&Install,
	&Remove
};
