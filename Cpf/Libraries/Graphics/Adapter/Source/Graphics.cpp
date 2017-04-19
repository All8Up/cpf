//////////////////////////////////////////////////////////////////////////
#include "Graphics.hpp"
#include "DebugUI.hpp"
#include "Graphics/Plugin.hpp"
#include "Plugin/iClassInstance.hpp"

using namespace Cpf;
using namespace Graphics;


int CPF_EXPORT_GRAPHICS_DRIVER GraphicsInitializer::Install(Plugin::iRegistry* regy)
{
	if (gContext.AddRef() == 1)
	{
		gContext.SetRegistry(regy);
		regy->Install(kDebugUICID, new Plugin::tClassInstance<DebugUI>());
	}
	return gContext.GetRefCount();
}

int CPF_EXPORT_GRAPHICS_DRIVER GraphicsInitializer::Remove()
{
	if (gContext.Release() == 0)
	{
		gContext.GetRegistry()->Remove(kDebugUICID);
		gContext.SetRegistry(nullptr);
		return 0;
	}
	return gContext.GetRefCount();
}
