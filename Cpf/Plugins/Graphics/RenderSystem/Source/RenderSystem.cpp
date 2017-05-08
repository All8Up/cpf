//////////////////////////////////////////////////////////////////////////
#include "RenderSystem.hpp"

using namespace Cpf;

RenderSystem::RenderSystem(COM::iUnknown*)
{
}

COM::Result CPF_STDCALL RenderSystem::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch(id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
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
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL RenderSystem::FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const
{
	return mpStages->FindStage(id, outStage);
}

COM::Result CPF_STDCALL RenderSystem::GetStages(int32_t* count, MultiCore::iStage** outStages) const
{
	return mpStages->GetStages(count, outStages);
}

COM::Result CPF_STDCALL RenderSystem::AddStage(MultiCore::iStage* stage)
{
	return mpStages->AddStage(stage);
}

COM::Result CPF_STDCALL RenderSystem::RemoveStage(MultiCore::StageID id)
{
	return mpStages->RemoveStage(id);
}

COM::Result CPF_STDCALL RenderSystem::GetInstructions(int32_t* count, MultiCore::Instruction* instructions)
{
	return mpStages->GetInstructions(count, instructions);
}

void CPF_STDCALL RenderSystem::AddDependency(MultiCore::BlockDependency dep)
{
	mpStages->AddDependency(dep);
}

COM::Result CPF_STDCALL RenderSystem::GetDependencies(MultiCore::iPipeline* owner, int32_t* count, MultiCore::BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}

COM::Result CPF_STDCALL RenderSystem::Initialize(Plugin::iRegistry* rgy, const char* name, const Desc* desc)
{
	(void)desc;
	mID = MultiCore::SystemID(name, strlen(name));
	rgy->Create(this, MultiCore::kStageListCID, iStageList::kIID, mpStages.AsVoidPP());

	return COM::kOK;
}

MultiCore::SystemID CPF_STDCALL RenderSystem::GetID() const
{
	return mID;
}

COM::Result CPF_STDCALL RenderSystem::Configure(MultiCore::iPipeline*)
{
	return COM::kOK;
}
