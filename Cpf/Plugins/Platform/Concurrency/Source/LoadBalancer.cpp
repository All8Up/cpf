//////////////////////////////////////////////////////////////////////////
#include "Concurrency/LoadBalancer.hpp"
#include "Concurrency/ThreadTimes.hpp"
#include "Plugin/iRegistry.hpp"
#include "CPF/Logging.hpp"

using namespace CPF;
using namespace Concurrency;
using namespace Threading;

LoadBalancer::LoadBalancer(iUnknown*)
	: mLastUpdate(Time::Now())
{
}

LoadBalancer::~LoadBalancer()
{}

GOM::Result CPF_STDCALL LoadBalancer::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch(id)
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case kIID.GetID():
			*outIface = static_cast<iLoadBalancer*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL LoadBalancer::Initialize(Plugin::iRegistry* regy, int count, iScheduler** schedulers)
{
	if(regy)
	{
		mSchedulers.clear();
		for (int i = 0; i < count; ++i)
			mSchedulers.push_back(schedulers[i]);
		return regy->Create(nullptr, kThreadTimeCID.GetID(), iThreadTimes::kIID.GetID(), mpDistTimeQuery.AsVoidPP());
	}
	return GOM::kInvalidParameter;
}

void CPF_STDCALL LoadBalancer::Balance()
{
	if (mSchedulers.empty())
		return;

	if (mQueryOutstanding)
	{
		CPF_LOG(Concurrency, Info) << " Processor usage: " << mCPUUsage.GetValue();

		mQueryOutstanding = false;
		ThreadTimeInfo info;
		mpDistTimeQuery->GetTimes(&info);
		int threadCount;

		// TODO: Currently expects scheduler 0 to be a distributor and 1 to be a thread pool.
		if (info.mDuration.GetTicks() > 0)
		{
			float duration = float(Time::Seconds(info.mDuration));
			float utilization = 0.0f;
			for (int i = 0; i < info.mThreadCount; ++i)
				utilization += float(Time::Seconds(info.mUserTime[i]));

			utilization = utilization / (float(info.mThreadCount) * duration);
			if (utilization < 0.9f)
			{
				threadCount = info.mThreadCount;
				if (threadCount>1)
				{
					threadCount -= 1;
					mSchedulers[0]->SetActiveThreads(threadCount);
				}
			}
			else
			{
				threadCount = info.mThreadCount;
				if (threadCount < mSchedulers[0]->GetMaxThreads() - 1)
				{
					threadCount += 1;
					mSchedulers[0]->SetActiveThreads(threadCount);
				}
			}

			// Simply set the number of pool threads to the inverse of those used in distribution.
			int targetThreads = mSchedulers[1]->GetMaxThreads() - threadCount;
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
		mSchedulers[0]->Submit(mpDistTimeQuery);
		mQueryOutstanding = true;
	}
}
