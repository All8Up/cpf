//////////////////////////////////////////////////////////////////////////
#include "InstanceSystem.hpp"
#include "ExperimentalD3D12.hpp"

using namespace Cpf;


void InstanceSystem::_Begin(Concurrency::ThreadContext&, void* context)
{
	InstanceSystem* system = static_cast<InstanceSystem*>(context);
	system->mpApp->GetCurrentInstanceBuffer()->Map(reinterpret_cast<void**>(&system->mpInstances));
}

void InstanceSystem::_End(Concurrency::ThreadContext&, void* context)
{
	InstanceSystem* system = static_cast<InstanceSystem*>(context);
	system->mpApp->GetCurrentInstanceBuffer()->Unmap();
}
