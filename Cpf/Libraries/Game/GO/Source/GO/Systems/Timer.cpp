//////////////////////////////////////////////////////////////////////////
#include "GO/Systems/Timer.hpp"
#include "GO/Manager.hpp"
#include "GO/ObjectStage.hpp"
#include "MultiCore/Stage.hpp"

using namespace Cpf;
using namespace GO;

//////////////////////////////////////////////////////////////////////////
bool Timer::Install()
{
	return System::Install(kID, &Timer::Creator);
}

bool Timer::Remove()
{
	return System::Remove(kID);
}

MultiCore::System* Timer::Creator(MultiCore::Pipeline* owner, const String& name)
{
	return new Timer(owner, name);
}

//////////////////////////////////////////////////////////////////////////
Timer::Timer(MultiCore::Pipeline* owner, const String& name)
	: System(owner, name)
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
	RemoveStage(mpUpdate);
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
