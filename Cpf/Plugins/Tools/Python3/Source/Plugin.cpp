#include "Plugin/iRegistry.hpp"
#include "Plugin/iClassInstance.hpp"
#include "Logging/Logging.hpp"
#include "Python3.hpp"

using namespace Cpf;

extern "C"
COM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		CPF_INIT_LOG(Python3);
		registry->Install(Tools::kPython3CID, new Plugin::tClassInstance<Tools::Python3>());
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

extern "C"
bool CPF_EXPORT CanUnload()
{
	return true;
}

extern "C"
COM::Result CPF_EXPORT Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		registry->Remove(Tools::kPython3CID);
		CPF_DROP_LOG(Python3);
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}
