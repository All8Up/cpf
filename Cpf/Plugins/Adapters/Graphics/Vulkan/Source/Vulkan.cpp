//////////////////////////////////////////////////////////////////////////
#include "Vulkan.hpp"
#include "Graphics.hpp"
#include "Plugin/tClassInstance.hpp"
#include "Vulkan/Instance.hpp"

using namespace CPF;

//////////////////////////////////////////////////////////////////////////
static Plugin::IID_CID sImplementations[] =
{
	{ Graphics::iInstance::kIID.GetID(), Vulkan::kVulkanInstanceCID.GetID() }
};


//////////////////////////////////////////////////////////////////////////
extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		if (GOM::Succeeded(registry->Install(Graphics::iInstance::kIID.GetID(), new Plugin::tClassInstance<Vulkan::Instance>())) &&
			GOM::Succeeded(registry->ClassInstall(1, sImplementations)))
			return GOM::kOK;
		return GOM::kError;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->ClassRemove(1, sImplementations);
		registry->Remove(Graphics::iInstance::kIID.GetID());
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
