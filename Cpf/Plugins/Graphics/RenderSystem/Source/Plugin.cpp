//////////////////////////////////////////////////////////////////////////
#include "RenderSystem.hpp"
#include "Renderable.hpp"
#include "Plugin/Context.hpp"
#include "Plugin/iClassInstance.hpp"

using namespace CPF;

namespace
{
	Plugin::Context g_Context;
}


extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (g_Context.AddRef() == 1)
		{
			CPF_ASSERT(g_Context.GetRegistry() == nullptr);
			g_Context.SetRegistry(registry);
			registry->Install(kRenderableCID.GetID(), new Plugin::tClassInstance<Renderable>());
			registry->Install(kRenderSystemCID.GetID(), new Plugin::tClassInstance<RenderSystem>());
		}
		CPF_ASSERT(g_Context.GetRegistry() == registry);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (g_Context.Release() == 0)
		{
			registry->Remove(kRenderSystemCID.GetID());
			registry->Remove(kRenderableCID.GetID());
			g_Context.SetRegistry(nullptr);
		}
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
