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

MultiCore::System* Timer::Creator(const String& name, const Desc*, const Dependencies& deps)
{
	return new Timer(name, deps);
}

//////////////////////////////////////////////////////////////////////////
Timer::Timer(const String& name, const Dependencies& deps)
	: System(name, deps)
	, mpUpdate(nullptr)
{
	mStart = Platform::Time::Now();
	mTime = mStart;

	mpUpdate.Adopt(MultiCore::Stage::Create<MultiCore::SingleUpdateStage>(this, String("Timer Update")));
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
