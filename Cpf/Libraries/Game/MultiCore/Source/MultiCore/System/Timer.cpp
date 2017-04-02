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

System* Timer::Creator(MultiCore::iPipeline* owner, const char* name, const Desc*)
{
	auto result =  new Timer();
	result->Initialize(owner, name);
	return result;
}

//////////////////////////////////////////////////////////////////////////
Timer::Timer()
	: mPaused(false)
	, mpUpdate(nullptr)
{
}

Timer::~Timer()
{
	RemoveStage(mpUpdate->GetID());
}

COM::Result CPF_STDCALL Timer::Initialize(iPipeline* owner, const char* name)
{
	COM::Result result = System::Initialize(owner, name);
	if (COM::Succeeded(result))
	{
		mStart = Time::Now();
		mTime = mStart;

		mpUpdate.Adopt(reinterpret_cast<SingleUpdateStage*>(Stage::Create(SingleUpdateStage::kID, this, Stage::kExecute.GetString())));
		mpUpdate->SetUpdate(&Timer::_Update, this);
		AddStage(mpUpdate);
		return COM::kOK;
	}
	return result;
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
