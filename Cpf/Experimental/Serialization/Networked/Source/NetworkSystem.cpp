//////////////////////////////////////////////////////////////////////////
#include "NetworkSystem.hpp"
#include "MultiCore/iStage.hpp"
#include "Plugin/iClassInstance.hpp"

using namespace Cpf;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
GOM::Result NetworkSystem::Install(Plugin::iRegistry* regy)
{
	return regy->Install(kNetworkSystemCID, new Plugin::tClassInstance<NetworkSystem>());
}

GOM::Result NetworkSystem::Remove(Plugin::iRegistry* regy)
{
	return regy->Remove(kNetworkSystemCID);
}

//////////////////////////////////////////////////////////////////////////
NetworkSystem::NetworkSystem(GOM::iBase*)
{
}

void NetworkSystem::_Update(const Concurrency::WorkContext*, void* context)
{
	NetworkSystem* self = reinterpret_cast<NetworkSystem*>(context);
	self->mASIO.poll();
}

//////////////////////////////////////////////////////////////////////////
GOM::Result CPF_STDCALL NetworkSystem::Cast(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case GOM::iBase::kIID.GetID():
			*outIface = static_cast<GOM::iBase*>(this);
			break;
		case iSystem::kIID.GetID():
			*outIface = static_cast<iSystem*>(this);
			break;
		case NetworkSystem::kIID.GetID():
			*outIface = static_cast<NetworkSystem*>(this);
			break;
		default:
			return GOM::kNotImplemented;
		}

		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL NetworkSystem::Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc*)
{
	(void)rgy;
	if (name)
	{
		mID = SystemID(name, strlen(name));
		auto result = rgy->Create(this, kStageListCID, iStageList::kIID, mpStages.AsVoidPP());
		if (GOM::Succeeded(result))
		{
			IntrusivePtr<iSingleUpdateStage> updateStage;
			rgy->Create(nullptr, MultiCore::kSingleUpdateStageCID, MultiCore::iSingleUpdateStage::kIID, updateStage.AsVoidPP());
			updateStage->Initialize(this, iStage::kExecute.GetString());
			updateStage->SetUpdate(&NetworkSystem::_Update, this, BlockOpcode::eAll);
			AddStage(updateStage);

			return GOM::kOK;
		}
		return result;
	}
	return GOM::kInvalidParameter;
}

SystemID CPF_STDCALL NetworkSystem::GetID() const
{
	return mID;
}

GOM::Result CPF_STDCALL NetworkSystem::FindStage(StageID id, iStage** outStage) const
{
	return mpStages->FindStage(id, outStage);
}

GOM::Result CPF_STDCALL NetworkSystem::GetInstructions(int32_t* count, Instruction* instructions)
{
	return mpStages->GetInstructions(count, instructions);
}

GOM::Result CPF_STDCALL NetworkSystem::GetStages(int32_t* count, iStage** outStages) const
{
	return mpStages->GetStages(count, outStages);
}

GOM::Result CPF_STDCALL NetworkSystem::AddStage(iStage* stage)
{
	return mpStages->AddStage(stage);
}

GOM::Result CPF_STDCALL NetworkSystem::RemoveStage(StageID id)
{
	return mpStages->RemoveStage(id);
}

void CPF_STDCALL NetworkSystem::AddDependency(BlockDependency dep)
{
	mpStages->AddDependency(dep);
}

GOM::Result CPF_STDCALL NetworkSystem::GetDependencies(MultiCore::iPipeline* owner, int32_t* count, BlockDependency* deps)
{
	return mpStages->GetDependencies(owner, count, deps);
}
