//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Time/Value.hpp"
#include "Concurrency/Concurrency.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		struct ThreadTimeInfo
		{
			int mThreadCount;
			Time::Value mDuration;
			Time::Value mUserTime[kMaxThreads];
			Time::Value mKernelTime[kMaxThreads];
		};
	}
}
