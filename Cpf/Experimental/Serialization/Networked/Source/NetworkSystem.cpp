//////////////////////////////////////////////////////////////////////////
#include "NetworkSystem.hpp"
#include "MultiCore/iStage.hpp"
#include "Plugin/iClassInstance.hpp"

using namespace Cpf;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
COM::Result NetworkSystem::Install(Plugin::iRegistry* regy)
{
	return regy->Install(kNetworkSystemCID, new Plugin::tSimpleClassInstance<NetworkSystem>());
}

COM::Result NetworkSystem::Remove(Plugin::iRegistry* regy)
{
	return regy->Remove(kNetworkSystemCID);
}

//////////////////////////////////////////////////////////////////////////
NetworkSystem::NetworkSystem()
{
}

void NetworkSystem::_Update(Concurrency::ThreadContext&, void* context)
{
	NetworkSystem* self = reinterpret_cast<NetworkSystem*>(context);
	self->mASIO.poll();
}

//////////////////////////////////////////////////////////////////////////
COM::Result CPF_STDCALL NetworkSystem::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iSystem::kIID.GetID():
			*outIface = static_cast<iSystem*>(this);
			break;
		case NetworkSystem::kIID.GetID():
			*outIface = static_cast<NetworkSystem*>(this);
			break;
		default:
			return COM::kNotImplemented;
		}

		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL NetworkSystem::Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc*)
{
	(void)rgy;
	if (name)
	{
		mID = SystemID(name, strlen(name));
		auto result = rgy->Create(nullptr, kStageListCID, iStageList::kIID, mpStages.AsVoidPP());
		if (COM::Succeeded(result))
		{
			IntrusivePtr<iSingleUpdateStage> updateStage;
			rgy->Create(nullptr, MultiCore::kSingleUpdateStageCID, MultiCore::iSingleUpdateStage::kIID, updateStage.AsVoidPP());
			updateStage->Initialize(this, iStage::kExecute.GetString());
			updateStage->SetUpdate(&NetworkSystem::_Update, this, BlockOpcode::eAll);
			AddStage(updateStage);

			return COM::kOK;
		}
		return result;
	}
	return COM::kInvalidParameter;
}

SystemID CPF_STDCALL NetworkSystem::GetID() const
{
	return mID;
}

COM::Result CPF_STDCALL NetworkSystem::FindStage(StageID id, iStage** outStage) const
{
	return mpStages->FindStage(id, outStage);
}

COM::Result CPF_STDCALL NetworkSystem::GetInstructions(int32_t* count, Instruction* instructions)
{
	return mpStages->GetInstructions(count, instructions);
}

COM::Result CPF_STDCALL NetworkSystem::GetStages(int32_t* count, iStage** outStages) const
{
	return mpStages->GetStages(count, outStages);
}

COM::Result CPF_STDCALL NetworkSystem::AddStage(iStage* stage)
{
	return mpStages->AddStage(stage);
}

COM::Result CPF_STDCALL NetworkSystem::RemoveStage(StageID id)
{
	return mpStages->RemoveStage(id);
}

void CPF_STDCALL NetworkSystem::AddDependency(BlockDependency dep)
{
	mpStages->AddDependency(dep);
}

COM::Result CPF_STDCALL NetworkSystem::GetDependencies(MultiCore::iPipeline* owner, int32_t* count, BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}