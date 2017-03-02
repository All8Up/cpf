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

MultiCore::System* Timer::Creator(MultiCore::Pipeline* owner, const char* name, const Desc*)
{
	return new Timer(owner, name);
}

//////////////////////////////////////////////////////////////////////////
Timer::Timer(MultiCore::Pipeline* owner, const char* name)
	: System(owner, name)
	, mpUpdate(nullptr)
	, mPaused(false)
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
	return float(Platform::Time::Seconds(mDelta));
}

bool Timer::IsPaused() const
{
	return mPaused;
}

void Timer::SetPause(bool flag)
{
	if (!flag && flag)
	{
		mStart = Platform::Time::Now();
		mTime = mStart + mDelta;
	}
	mPaused = flag;
}

void Timer::Pause()
{
	mPaused = true;
}

void Timer::Resume()
{
	SetPause(false);
}

void Timer::_Update(Concurrency::ThreadContext&, void* context)
{
	Timer* self = reinterpret_cast<Timer*>(context);
	if (!self->mPaused)
	{
		Platform::Time::Value now = Platform::Time::Now();
		self->mDelta = now - self->mTime;
		self->mTime = now;
	}
}
