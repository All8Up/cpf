#include "Plugin/iRegistry.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;

extern "C"
GOM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		CPF_INIT_LOG(Scene);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		CPF_DROP_LOG(Scene);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
