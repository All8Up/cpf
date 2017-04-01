//////////////////////////////////////////////////////////////////////////
#include "NetworkSystem.hpp"
#include "MultiCore/Stage.hpp"

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
	: System(pipeline, name)
{
	IntrusivePtr<SingleUpdateStage> updateStage(Stage::Create<SingleUpdateStage>(this, Stage::kExecute.GetString()));
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
