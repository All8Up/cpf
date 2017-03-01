//////////////////////////////////////////////////////////////////////////
#include "EntityService/Interfaces/Systems/iTimerSystem.hpp"
#include "../Manager.hpp"
#include "MultiCore/Stage.hpp"

using namespace Cpf;
using namespace EntityService;

//////////////////////////////////////////////////////////////////////////
bool Timer::Install()
{
	return System::Install(kID, &Timer::Creator);
}

bool Timer::Remove()
{
	return System::Remove(kID);
}

MultiCore::System* Timer::Creator(MultiCore::Pipeline* owner, const char* name, const Desc*, const SystemDependencies& deps)
{
	return new Timer(owner, name, deps);
}

//////////////////////////////////////////////////////////////////////////
Timer::Timer(MultiCore::Pipeline* owner, const char* name, const SystemDependencies& deps)
	: System(owner, name, deps)
	, mpUpdate(nullptr)
{
	mStart = Platform::Time::Now();
	mTime = mStart;

	mpUpdate.Adopt(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, kUpdate.GetString()));
	mpUpdate->SetUpdate(&Timer::_Update, this);
	AddStage(mpUpdate);
}

Timer::~Timer()
{
	RemoveStage(mpUpdate->GetID());
}

Platform::Time::Value Timer::GetTime() const
{
	return mTime - mStart;
}

float Timer::GetDeltaTime() const
{
	return float(Platform::Time::Seconds(mTime - mStart));
}

void Timer::_Update(Concurrency::ThreadContext&, void* context)
{
	reinterpret_cast<Timer*>(context)->mTime = Platform::Time::Now();
}
