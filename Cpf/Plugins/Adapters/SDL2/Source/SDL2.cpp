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
		{ iWindowedApplication::kIID.GetID(), SDL2::kWindowedApplicationCID.GetID() },
		{ iWindow::kIID.GetID(), SDL2::kWindowCID.GetID() },
		{ iInputManager::kIID.GetID(), SDL2::kInputManagerCID.GetID() },
		{ iMouseDevice::kIID.GetID(), SDL2::kMouseDeviceCID.GetID() },
		{ iKeyboardDevice::kIID.GetID(), SDL2::kKeyboardDeviceCID.GetID() },
		{ iClipboard::kIID.GetID(), SDL2::kClipboardCID.GetID() }
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
			registry->Install(SDL2::kWindowCID.GetID(), new Plugin::tClassInstance<SDL2::Window>());
			registry->Install(SDL2::kWindowedApplicationCID.GetID(), new Plugin::tClassInstance<SDL2::WindowedApp>());
			registry->Install(SDL2::kInputManagerCID.GetID(), new Plugin::tClassInstance<SDL2::InputManager>());
			registry->Install(SDL2::kMouseDeviceCID.GetID(), new Plugin::tClassInstance<SDL2::MouseDevice>());
			registry->Install(SDL2::kKeyboardDeviceCID.GetID(), new Plugin::tClassInstance<SDL2::KeyboardDevice>());
			registry->Install(SDL2::kClipboardCID.GetID(), new Plugin::tClassInstance<SDL2::Clipboard>());
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
			registry->Remove(SDL2::kClipboardCID.GetID());
			registry->Remove(SDL2::kKeyboardDeviceCID.GetID());
			registry->Remove(SDL2::kMouseDeviceCID.GetID());
			registry->Remove(SDL2::kInputManagerCID.GetID());
			registry->Remove(SDL2::kWindowedApplicationCID.GetID());
			registry->Remove(SDL2::kWindowCID.GetID());
			SDL2::g_Context.SetRegistry(nullptr);
		}
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
