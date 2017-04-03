//////////////////////////////////////////////////////////////////////////
#include "InstanceSystem.hpp"
#include "ExperimentalD3D12.hpp"

using namespace Cpf;

InstanceSystem::InstanceSystem(Plugin::iRegistry* rgy, MultiCore::iPipeline* owner, const char* name, const Desc* desc)
	: mpApp(desc->mpApplication)
	, mRenderID(desc->mRenderSystemID)
	, mpInstances(nullptr)
{
	System::Initialize(rgy, owner, name);

	// Build the stages and set the update function.
	IntrusivePtr<MultiCore::iSingleUpdateStage> instanceBegin;
	rgy->Create(nullptr, MultiCore::kSingleUpdateStageCID, MultiCore::iSingleUpdateStage::kIID, instanceBegin.AsVoidPP());
	instanceBegin->Initialize(this, kBegin.GetString());
	instanceBegin->SetUpdate(&InstanceSystem::_Begin, this, MultiCore::BlockOpcode::eLast);

	IntrusivePtr<MultiCore::iSingleUpdateStage> instanceEnd;
	rgy->Create(nullptr, MultiCore::kSingleUpdateStageCID, MultiCore::iSingleUpdateStage::kIID, instanceEnd.AsVoidPP());
	instanceEnd->Initialize(this, kEnd.GetString());
	instanceEnd->SetUpdate(&InstanceSystem::_End, this, MultiCore::BlockOpcode::eLast);

	// Add the stages to this system.
	AddStage(instanceBegin);
	AddStage(instanceEnd);

	// Add the default dependencies.
	AddDependency({
		{ GetID(), instanceEnd->GetID(), MultiCore::iStage::kExecute },
		{ GetID(), instanceBegin->GetID(), MultiCore::iStage::kExecute },
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
