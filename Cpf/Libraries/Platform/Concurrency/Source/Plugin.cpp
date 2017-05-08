#include "Plugin/iRegistry.hpp"
#include "Concurrency/Queue.hpp"
#include "Plugin/iClassInstance.hpp"

using namespace Cpf;

extern "C"
COM::Result CPF_EXPORT Install(Plugin::iRegistry* registry)
{
	if (registry)
	{
//		registry->Install(Concurrency::kQueueCID, new Plugin::tClassInstance<Concurrency::Scheduler::Queue>());
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
//		registry->Remove(Concurrency::kQueueCID);
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}
