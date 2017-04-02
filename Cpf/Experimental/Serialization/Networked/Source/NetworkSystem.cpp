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
NetworkSystem::NetworkSystem(MultiCore::iPipeline* pipeline, const char* name, const Desc*)
{
	System::Initialize(pipeline, name);
	IntrusivePtr<SingleUpdateStage> updateStage(reinterpret_cast<MultiCore::SingleUpdateStage*>(MultiCore::Stage::Create(MultiCore::SingleUpdateStage::kID, nullptr, this, Stage::kExecute.GetString())));
	updateStage->SetUpdate(&NetworkSystem::_Update, this, BlockOpcode::eAll);
	AddStage(updateStage);
}

System* NetworkSystem::_Creator(MultiCore::iPipeline* owner, const char* name, const System::Desc* desc)
{
	return new NetworkSystem(owner, name, static_cast<const Desc*>(desc));
}

void NetworkSystem::_Update(Concurrency::ThreadContext&, void* context)
{
	NetworkSystem* self = reinterpret_cast<NetworkSystem*>(context);
	self->mASIO.poll();
}
