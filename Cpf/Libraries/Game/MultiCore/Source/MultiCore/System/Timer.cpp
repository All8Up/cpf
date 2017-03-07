//////////////////////////////////////////////////////////////////////////
#include "MultiCore/System/Timer.hpp"

using namespace Cpf;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
bool Timer::Install()
{
	return System::Install(kID, &Timer::Creator);
}

bool Timer::Remove()
{
	return System::Remove(kID);
}

System* Timer::Creator(MultiCore::Pipeline* owner, const char* name, const Desc*)
{
	return new Timer(owner, name);
}

//////////////////////////////////////////////////////////////////////////
Timer::Timer(Pipeline* owner, const char* name)
	: System(owner, name)
	, mPaused(false)
	, mpUpdate(nullptr)
{
	mStart = Time::Now();
	mTime = mStart;

	mpUpdate.Adopt(Stage::Create<SingleUpdateStage>(this, Stage::kExecute.GetString()));
	mpUpdate->SetUpdate(&Timer::_Update, this);
	AddStage(mpUpdate);
}

Timer::~Timer()
{
	RemoveStage(mpUpdate->GetID());
}

Time::Value Timer::GetTime() const
{
	return mTime - mStart;
}

float Timer::GetDeltaTime() const
{
	return float(Time::Seconds(mDelta));
}

bool Timer::IsPaused() const
{
	return mPaused;
}

void Timer::SetPause(bool flag)
{
	if (!flag && flag)
	{
		mStart = Time::Now();
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
		Time::Value now = Time::Now();
		self->mDelta = now - self->mTime;
		self->mTime = now;
	}
}
