//////////////////////////////////////////////////////////////////////////
#include "Concurrency/LoadBalancer.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Concurrency;
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

	if (mQueryOutstanding)
	{
		CPF_LOG(Networked, Info) << " Processor usage: " << mCPUUsage.GetValue();

		mQueryOutstanding = false;
		auto distTimes = mDistTimeQuery.GetResult();
		int threadCount;

		// TODO: Currently expects scheduler 0 to be a distributor and 1 to be a thread pool.
		if (distTimes.mDuration.GetTicks() > 0)
		{
			float duration = float(Time::Seconds(distTimes.mDuration));
			float utilization = 0.0f;
			for (int i = 0; i < distTimes.mThreadCount; ++i)
				utilization += float(Time::Seconds(distTimes.mUserTime[i]));

			utilization = utilization / (float(distTimes.mThreadCount) * duration);
			if (utilization < 0.9f)
			{
				threadCount = distTimes.mThreadCount;
				if (threadCount>1)
				{
					threadCount -= 1;
					mSchedulers[0]->SetActiveThreads(threadCount);
				}
			}
			else
			{
				threadCount = distTimes.mThreadCount;
				if (threadCount < mSchedulers[0]->GetAvailableThreads() - 1)
				{
					threadCount += 1;
					mSchedulers[0]->SetActiveThreads(threadCount);
				}
			}

			// Simply set the number of pool threads to the inverse of those used in distribution.
			int targetThreads = mSchedulers[1]->GetAvailableThreads() - threadCount;
			targetThreads = targetThreads > 0 ? targetThreads : 1;
			mSchedulers[1]->SetActiveThreads(targetThreads);
		}
	}
	else
	{
		auto now = Time::Now();
		if (Time::Seconds(now - mLastUpdate) < float(kUpdateRate))
			return;
		mLastUpdate = now;

		// Submits queries to pick up on the next loop.
		// Picking the result up on the next loop prevents blocking.
		mSchedulers[0]->Submit(mDistTimeQuery);
		mQueryOutstanding = true;
	}
}
