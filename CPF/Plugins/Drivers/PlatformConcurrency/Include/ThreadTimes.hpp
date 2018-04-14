//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/iRefCounted.hpp"
#include "CPF/Platform/Concurrency/iThreadTimes.hpp"
#include "CPF/Platform/Concurrency/ThreadTimeInfo.hpp"
#include "CPF/Threading/Semaphore.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Plugin
	{
		struct iRegistry;
	}

	namespace Concurrency
	{
		class ThreadTimes : public GOM::tUnknown<iThreadTimes>
		{
		public:
			ThreadTimes(Plugin::iRegistry*, iUnknown*) {}

			void CPF_STDCALL Wait() override;
			void CPF_STDCALL Signal() override;

			void CPF_STDCALL GetTimes(ThreadTimeInfo* threadTimes) override
			{
				Wait();
				*threadTimes = mTimeResult;
			}

		private:
			friend class Scheduler;

			Threading::Semaphore mSemaphore;
			ThreadTimeInfo mTimeResult;
		};
	}
}
