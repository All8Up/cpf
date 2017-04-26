//////////////////////////////////////////////////////////////////////////
#include "RenderSystem.hpp"
#include "Renderable.hpp"
#include "Plugin/Context.hpp"
#include "Plugin/iClassInstance.hpp"

using namespace Cpf;

namespace
{
	Plugin::Context g_Context;
}


extern "C"
COM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (g_Context.AddRef() == 1)
		{
			CPF_ASSERT(g_Context.GetRegistry() == nullptr);
			g_Context.SetRegistry(registry);
			registry->Install(kRenderableCID, new Plugin::tClassInstance<Renderable>());
			registry->Install(kRenderSystemCID, new Plugin::tClassInstance<RenderSystem>());
		}
		CPF_ASSERT(g_Context.GetRegistry() == registry);
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

extern "C"
bool CPF_EXPORT CanUnload()
{
	return g_Context.GetRefCount() == 0;
}

extern "C"
COM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (g_Context.Release() == 0)
		{
			registry->Remove(kRenderSystemCID);
			registry->Remove(kRenderableCID);
			g_Context.SetRegistry(nullptr);
		}
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}
