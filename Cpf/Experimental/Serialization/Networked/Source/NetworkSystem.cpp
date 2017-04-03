//////////////////////////////////////////////////////////////////////////
#include "NetworkSystem.hpp"
#include "MultiCore/iStage.hpp"

using namespace Cpf;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
bool NetworkSystem::Install()
{
	return System::Install(kID, &NetworkSystem::_Creator);
}

bool NetworkSystem::Remove()
{
	return System::Remove(kID);
}

//////////////////////////////////////////////////////////////////////////
NetworkSystem::NetworkSystem(Plugin::iRegistry* rgy, MultiCore::iPipeline* pipeline, const char* name, const Desc*)
{
	System::Initialize(rgy, pipeline, name);
	IntrusivePtr<iSingleUpdateStage> updateStage;
	rgy->Create(nullptr, MultiCore::kSingleUpdateStageCID, MultiCore::iSingleUpdateStage::kIID, updateStage.AsVoidPP());
	updateStage->Initialize(this, iStage::kExecute.GetString());
	updateStage->SetUpdate(&NetworkSystem::_Update, this, BlockOpcode::eAll);
	AddStage(updateStage);
}

iSystem* NetworkSystem::_Creator(Plugin::iRegistry* rgy, MultiCore::iPipeline* owner, const char* name, const System::Desc* desc)
{
	return new NetworkSystem(rgy, owner, name, static_cast<const Desc*>(desc));
}

void NetworkSystem::_Update(Concurrency::ThreadContext&, void* context)
{
	NetworkSystem* self = reinterpret_cast<NetworkSystem*>(context);
	self->mASIO.poll();
}
