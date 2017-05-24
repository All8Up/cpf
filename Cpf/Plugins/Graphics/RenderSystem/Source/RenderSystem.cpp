//////////////////////////////////////////////////////////////////////////
#include "RenderSystem.hpp"

using namespace Cpf;

RenderSystem::RenderSystem(GOM::iBase*)
{
}

GOM::Result CPF_STDCALL RenderSystem::Cast(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch(id.GetID())
		{
		case GOM::iBase::kIID.GetID():
			*outIface = static_cast<GOM::iBase*>(this);
			break;

		case iStageList::kIID.GetID():
			*outIface = static_cast<iStageList*>(mpStages);
			break;

		case iSystem::kIID.GetID():
			*outIface = static_cast<iSystem*>(this);
			break;

		case iRenderSystem::kIID.GetID():
			*outIface = static_cast<iRenderSystem*>(this);
			break;

		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL RenderSystem::FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const
{
	return mpStages->FindStage(id, outStage);
}

GOM::Result CPF_STDCALL RenderSystem::GetStages(int32_t* count, MultiCore::iStage** outStages) const
{
	return mpStages->GetStages(count, outStages);
}

GOM::Result CPF_STDCALL RenderSystem::AddStage(MultiCore::iStage* stage)
{
	return mpStages->AddStage(stage);
}

GOM::Result CPF_STDCALL RenderSystem::RemoveStage(MultiCore::StageID id)
{
	return mpStages->RemoveStage(id);
}

GOM::Result CPF_STDCALL RenderSystem::GetInstructions(int32_t* count, MultiCore::Instruction* instructions)
{
	return mpStages->GetInstructions(count, instructions);
}

void CPF_STDCALL RenderSystem::AddDependency(MultiCore::BlockDependency dep)
{
	mpStages->AddDependency(dep);
}

GOM::Result CPF_STDCALL RenderSystem::GetDependencies(MultiCore::iPipeline* owner, int32_t* count, MultiCore::BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}

GOM::Result CPF_STDCALL RenderSystem::Initialize(Plugin::iRegistry* rgy, const char* name, const Desc* desc)
{
	(void)desc;
	mID = MultiCore::SystemID(name, strlen(name));
	rgy->Create(this, MultiCore::kStageListCID, iStageList::kIID, mpStages.AsVoidPP());

	return GOM::kOK;
}

MultiCore::SystemID CPF_STDCALL RenderSystem::GetID() const
{
	return mID;
}

GOM::Result CPF_STDCALL RenderSystem::Configure(MultiCore::iPipeline*)
{
	return GOM::kOK;
}
