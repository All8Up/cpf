#include "Plugin/iRegistry.hpp"
#include "Plugin/Context.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Window.hpp"
#include "WindowedApplication.hpp"
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
		{ iWindow::kIID, SDL2::kWindowCID }
	};
}

struct SDL2WindowClass : public Plugin::iClassInstance
{
	SDL2WindowClass(int32_t* externalRef = nullptr) : mRefCount(1), mExternalRef(externalRef) {}

	COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }
	int32_t CPF_STDCALL AddRef() override { return ++mRefCount; }
	int32_t CPF_STDCALL Release() override
	{
		if (--mRefCount == 0)
		{
			delete this;
			return 0;
		}
		return mRefCount;
	}

	COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown*, COM::iUnknown** outIface) override
	{
		if (outIface)
		{
			*outIface = new SDL2::Window();
			if (*outIface)
			{
				if (mExternalRef)
					++*mExternalRef;
				return COM::kOK;
			}
			return COM::kOutOfMemory;
		}
		return COM::kInvalidParameter;
	}

private:
	int32_t mRefCount;
	int32_t* mExternalRef;
};

//////////////////////////////////////////////////////////////////////////
extern "C"
COM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (SDL2::g_Context.AddRef() == 1)
		{
			SDL2::g_Context.SetRegistry(registry);
			registry->Install(SDL2::kWindowCID, new SDL2WindowClass());
			registry->Install(SDL2::kWindowedApplicationCID, new Plugin::tSimpleClassInstance<SDL2::WindowedApp>());

			registry->FactoryInstall(int32_t(sizeof(sImplementations) / sizeof(Plugin::IID_CID)), sImplementations);
		}
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

extern "C"
COM::Result CPF_EXPORT CanUnload()
{
	return SDL2::g_Context.GetRefCount() == 0 ? COM::kOK : COM::kInUse;
}

extern "C"
COM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (SDL2::g_Context.Release() == 0)
		{
			registry->FactoryRemove(int32_t(sizeof(sImplementations) / sizeof(Plugin::IID_CID)), sImplementations);
			registry->Remove(SDL2::kWindowedApplicationCID);
			registry->Remove(SDL2::kWindowCID);
			SDL2::g_Context.SetRegistry(nullptr);
		}
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}
