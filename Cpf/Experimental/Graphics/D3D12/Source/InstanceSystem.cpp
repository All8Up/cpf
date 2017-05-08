//////////////////////////////////////////////////////////////////////////
#include "InstanceSystem.hpp"
#include "ExperimentalD3D12.hpp"
#include "Graphics/iImage.hpp"
#include "Graphics/iImageView.hpp"

using namespace Cpf;

InstanceSystem::InstanceSystem(COM::iUnknown*)
{}

void InstanceSystem::_Begin(const Concurrency::WorkContext*, void* context)
{
	InstanceSystem* system = static_cast<InstanceSystem*>(context);
	system->mpApp->GetCurrentInstanceBuffer()->Map(reinterpret_cast<void**>(&system->mpInstances));
}

void InstanceSystem::_End(const Concurrency::WorkContext*, void* context)
{
	InstanceSystem* system = static_cast<InstanceSystem*>(context);
	system->mpApp->GetCurrentInstanceBuffer()->Unmap();
}


// iUnknown
COM::Result CPF_STDCALL InstanceSystem::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case InstanceSystem::kIID.GetID():
			*outIface = static_cast<InstanceSystem*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

// iSystem
COM::Result CPF_STDCALL InstanceSystem::Initialize(Plugin::iRegistry* rgy, const char* name, const MultiCore::iSystem::Desc* desc)
{
	if (rgy && name)
	{
		const InstanceSystem::Desc* theDesc = static_cast<const InstanceSystem::Desc*>(desc);
		mpApp = theDesc->mpApplication;
		mRenderID = theDesc->mRenderSystemID;
		mpInstances = nullptr;
		mID = MultiCore::SystemID(name, strlen(name));
		auto result = rgy->Create(this, MultiCore::kStageListCID, MultiCore::iStageList::kIID, mpStages.AsVoidPP());

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

		return result;
	}
	return COM::kInvalidParameter;
}

MultiCore::SystemID CPF_STDCALL InstanceSystem::GetID() const
{
	return mID;
}

// iStageList
COM::Result CPF_STDCALL InstanceSystem::FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const
{
	return mpStages->FindStage(id, outStage);
}

COM::Result CPF_STDCALL InstanceSystem::GetStages(int32_t* count, MultiCore::iStage** outStages) const
{
	return mpStages->GetStages(count, outStages);
}

COM::Result CPF_STDCALL InstanceSystem::GetInstructions(int32_t* count, MultiCore::Instruction* instrs)
{
	return mpStages->GetInstructions(count, instrs);
}

void CPF_STDCALL InstanceSystem::AddDependency(MultiCore::BlockDependency dep)
{
	mpStages->AddDependency(dep);
}

COM::Result CPF_STDCALL InstanceSystem::GetDependencies(MultiCore::iPipeline* owner, int32_t* count, MultiCore::BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}

COM::Result CPF_STDCALL InstanceSystem::AddStage(MultiCore::iStage* stage)
{
	return mpStages->AddStage(stage);
}

COM::Result CPF_STDCALL InstanceSystem::RemoveStage(MultiCore::StageID id)
{
	return mpStages->RemoveStage(id);
}
