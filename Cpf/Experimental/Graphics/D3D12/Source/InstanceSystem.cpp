//////////////////////////////////////////////////////////////////////////
#include "InstanceSystem.hpp"
#include "ExperimentalD3D12.hpp"

using namespace Cpf;

InstanceSystem::InstanceSystem(MultiCore::iPipeline* owner, const char* name, const Desc* desc)
	: mpApp(desc->mpApplication)
	, mRenderID(desc->mRenderSystemID)
	, mpInstances(nullptr)
{
	System::Initialize(owner, name);

	// Build the stages and set the update function.
	IntrusivePtr<MultiCore::SingleUpdateStage> instanceBegin(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, kBegin.GetString()));
	instanceBegin->SetUpdate(&InstanceSystem::_Begin, this, MultiCore::BlockOpcode::eLast);

	IntrusivePtr<MultiCore::SingleUpdateStage> instanceEnd(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, kEnd.GetString()));
	instanceEnd->SetUpdate(&InstanceSystem::_End, this, MultiCore::BlockOpcode::eLast);

	// Add the stages to this system.
	AddStage(instanceBegin);
	AddStage(instanceEnd);

	// Add the default dependencies.
	AddDependency({
		{ GetID(), instanceEnd->GetID(), MultiCore::Stage::kExecute },
		{ GetID(), instanceBegin->GetID(), MultiCore::Stage::kExecute },
		MultiCore::DependencyPolicy::eAfter
	});
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
