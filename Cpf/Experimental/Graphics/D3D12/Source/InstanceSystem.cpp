//////////////////////////////////////////////////////////////////////////
#include "InstanceSystem.hpp"
#include "ExperimentalD3D12.hpp"

using namespace Cpf;

InstanceSystem::InstanceSystem(const String& name, const EntityService::SystemDependencies& deps, const Desc* desc)
	: System(name, deps)
	, mpApp(desc->mpApplication)
	, mRenderID(desc->mRenderSystemID)
	, mpInstances(nullptr)
{
	// Build the stages and set the update function.
	IntrusivePtr<MultiCore::SingleUpdateStage> instanceBegin(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, kBegin.GetString()));
	instanceBegin->SetUpdate(&InstanceSystem::_Begin, this);

	IntrusivePtr<MultiCore::SingleUpdateStage> instanceEnd(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, kEnd.GetString()));
	instanceEnd->SetUpdate(&InstanceSystem::_End, this);

	// Add the stages to this system.
	AddStage(instanceBegin);
	AddStage(instanceEnd);

	// Add the default dependencies.
	AddDependency({ instanceEnd->GetID(),{ GetID(), instanceBegin->GetID() } });
}


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
