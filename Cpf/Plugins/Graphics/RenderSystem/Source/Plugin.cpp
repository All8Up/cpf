//////////////////////////////////////////////////////////////////////////
#include "RenderSystem.hpp"
#include "Renderable.hpp"
#include "Plugin/tClassInstance.hpp"

using namespace CPF;


extern "C"
GOM::Result CPF_EXPORT CPF_STDCALL Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->Install(kRenderableCID.GetID(), new Plugin::tClassInstance<Renderable>());
		registry->Install(kRenderSystemCID.GetID(), new Plugin::tClassInstance<RenderSystem>());
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT CPF_STDCALL Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->Remove(kRenderSystemCID.GetID());
		registry->Remove(kRenderableCID.GetID());
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
