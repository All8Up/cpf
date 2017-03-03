//////////////////////////////////////////////////////////////////////////
#include "Concurrency/LoadBalancer.hpp"

using namespace Cpf;
using namespace Concurrency;
using namespace Platform;
using namespace Threading;

LoadBalancer::LoadBalancer()
	: mLastUpdate(Time::Now())
{}

LoadBalancer::~LoadBalancer()
{}

void LoadBalancer::SetSchedulers(Schedulers&& schedulers)
{
	mSchedulers = Move(schedulers);
	Balance();
}

void LoadBalancer::Balance()
{
	if (mSchedulers.empty())
		return;

	auto now = Time::Now();
	if (Time::Seconds(now - mLastUpdate) < float(kUpdateRate))
		return;
	mLastUpdate = now;

	// For the moment, just assign threads first come first serve.
	// TODO: Do something to make this use the scheduler timing information.
	int totalThreads = Thread::GetHardwareThreadCount();
	int first = totalThreads - (int(mSchedulers.size()) - 1);
	first = first > 0 ? first : 1;
	int remains = totalThreads - first;
	remains = remains > 0 ? remains : 1;
	int divy = remains / (int(mSchedulers.size()) - 1);
	divy = divy > 0 ? divy : 1;

	if (first != mSchedulers[0]->GetActiveThreads())
		mSchedulers[0]->SetActiveThreads(first);

	for (int i = 1; i < mSchedulers.size(); ++i)
		if (divy != mSchedulers[i]->GetActiveThreads())
			mSchedulers[i]->SetActiveThreads(divy);
}
