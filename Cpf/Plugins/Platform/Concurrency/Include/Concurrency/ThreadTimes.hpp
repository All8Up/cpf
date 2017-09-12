//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"
#include "Concurrency/iThreadTimes.hpp"
#include "Concurrency/ThreadTimeInfo.hpp"
#include "Threading/Semaphore.hpp"

namespace CPF
{
	namespace Concurrency
	{
		class ThreadTimes : public tRefCounted<iThreadTimes>
		{
		public:
			ThreadTimes(iUnknown*) {}

			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

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
