#include "Plugin/iRegistry.hpp"
#include "Plugin/Context.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Window.hpp"
#include "WindowedApplication.hpp"
#include "InputManager.hpp"
#include "MouseDevice.hpp"
#include "KeyboardDevice.hpp"
#include "Clipboard.hpp"
#include "SDL2/CIDs.hpp"

using namespace Cpf;

namespace Cpf
{
	namespace SDL2
	{
		Plugin::Context g_Context;
	}
}
namespace
{
	Plugin::IID_CID sImplementations[] =
	{
		{ iWindowedApplication::kIID, SDL2::kWindowedApplicationCID },
		{ iWindow::kIID, SDL2::kWindowCID },
		{ iInputManager::kIID, SDL2::kInputManagerCID },
		{ iMouseDevice::kIID, SDL2::kMouseDeviceCID },
		{ iKeyboardDevice::kIID, SDL2::kKeyboardDeviceCID },
		{ iClipboard::kIID, SDL2::kClipboardCID }
	};
}


//////////////////////////////////////////////////////////////////////////
extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (SDL2::g_Context.AddRef() == 1)
		{
			SDL2::g_Context.SetRegistry(registry);
			registry->Install(SDL2::kWindowCID, new Plugin::tClassInstance<SDL2::Window>());
			registry->Install(SDL2::kWindowedApplicationCID, new Plugin::tClassInstance<SDL2::WindowedApp>());
			registry->Install(SDL2::kInputManagerCID, new Plugin::tClassInstance<SDL2::InputManager>());
			registry->Install(SDL2::kMouseDeviceCID, new Plugin::tClassInstance<SDL2::MouseDevice>());
			registry->Install(SDL2::kKeyboardDeviceCID, new Plugin::tClassInstance<SDL2::KeyboardDevice>());
			registry->Install(SDL2::kClipboardCID, new Plugin::tClassInstance<SDL2::Clipboard>());
			registry->ClassInstall(int32_t(sizeof(sImplementations) / sizeof(Plugin::IID_CID)), sImplementations);
		}
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT CanUnload()
{
	return SDL2::g_Context.GetRefCount() == 0 ? GOM::kOK : GOM::kInUse;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (SDL2::g_Context.Release() == 0)
		{
			registry->ClassRemove(int32_t(sizeof(sImplementations) / sizeof(Plugin::IID_CID)), sImplementations);
			registry->Remove(SDL2::kClipboardCID);
			registry->Remove(SDL2::kKeyboardDeviceCID);
			registry->Remove(SDL2::kMouseDeviceCID);
			registry->Remove(SDL2::kInputManagerCID);
			registry->Remove(SDL2::kWindowedApplicationCID);
			registry->Remove(SDL2::kWindowCID);
			SDL2::g_Context.SetRegistry(nullptr);
		}
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
