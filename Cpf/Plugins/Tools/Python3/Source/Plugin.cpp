#include "Plugin/iRegistry.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Logging/Logging.hpp"
#include "Python3.hpp"

using namespace CPF;

extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		CPF_INIT_LOG(Python3);
		registry->Install(Tools::kPython3CID.GetID(), new Plugin::tClassInstance<Tools::Python3>());
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->Remove(Tools::kPython3CID.GetID());
		CPF_DROP_LOG(Python3);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
