//////////////////////////////////////////////////////////////////////////
#include "NetworkSystem.hpp"
#include "MultiCore/Stage.hpp"

using namespace Cpf;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
bool NetworkSystem::Install()
{
	return MultiCore::System::Install(kID, &NetworkSystem::_Creator);
}

bool NetworkSystem::Remove()
{
	return MultiCore::System::Remove(kID);
}

//////////////////////////////////////////////////////////////////////////
NetworkSystem::NetworkSystem(MultiCore::Pipeline* pipeline, const char* name, const NetworkSystem::Desc* desc)
	: MultiCore::System(pipeline, name)
{
	IntrusivePtr<MultiCore::SingleUpdateStage> updateStage(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, Stage::kExecute.GetString()));
	updateStage->SetUpdate(&NetworkSystem::_Update, this, BlockOpcode::eAll);
	AddStage(updateStage);
}

System* NetworkSystem::_Creator(MultiCore::Pipeline* owner, const char* name, const System::Desc* desc)
{
	return new NetworkSystem(owner, name, static_cast<const NetworkSystem::Desc*>(desc));
}

void NetworkSystem::_Update(Concurrency::ThreadContext&, void* context)
{
	NetworkSystem* self = reinterpret_cast<NetworkSystem*>(context);
	self->mASIO.poll();
}
