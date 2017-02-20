//////////////////////////////////////////////////////////////////////////
#include "GO/Systems/Timer.hpp"
#include "GO/Service.hpp"

using namespace Cpf;
using namespace GO;

//////////////////////////////////////////////////////////////////////////
Timer::Timer(Service* service)
	: System(service)
	, mpUpdate(nullptr)
{
	mpUpdate = new Stage(service, this, "Timer");
	mpUpdate->AddUpdate(this, nullptr, &Timer::_Update);
}

Timer::~Timer()
{
	mpUpdate->Release();
}

void Timer::Activate()
{
	mStart = Platform::Time::Now();
	mTime = mStart;

	Add(mpUpdate);
	mpUpdate->AddRef();
}

void Timer::Deactivate()
{
}

Platform::Time::Value Timer::GetTime() const
{
	return mTime - mStart;
}

float Timer::GetDeltaTime() const
{
	return float(Platform::Time::Seconds(mTime - mStart));
}

void Timer::_Update(System* s, Object*)
{
	reinterpret_cast<Timer*>(s)->mTime = Platform::Time::Now();
}
