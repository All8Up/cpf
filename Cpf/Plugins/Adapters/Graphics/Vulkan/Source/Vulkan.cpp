//////////////////////////////////////////////////////////////////////////
#include "Vulkan.hpp"
#include "Graphics.hpp"
#include "Plugin/tClassInstance.hpp"
#include "Logging/Logging.hpp"

using namespace CPF;

//////////////////////////////////////////////////////////////////////////
static Plugin::IID_CID sImplementations[] =
{
	{0}
//	{ Graphics::iInstance::kIID.GetID(), Vulkan::kVulkanInstanceCID.GetID() }
};


//////////////////////////////////////////////////////////////////////////
extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
