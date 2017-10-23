#include "CPF/Plugin/iRegistry.hpp"
#include "CPF/Plugin/iClassInstance.hpp"
#include "CPF/Logging.hpp"

using namespace CPF;

extern "C"
GOM::Result CPF_EXPORT CPF_STDCALL Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
		CPF_INIT_LOG(Scene);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

extern "C"
GOM::Result CPF_EXPORT CPF_STDCALL Remove(Plugin::iRegistry* registry)
{
	if (registry)
	{
		CPF_DROP_LOG(Scene);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}
