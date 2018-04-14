//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Threading/Thread.hpp"
#include "CPF/Performance/VTune.hpp"

namespace CPF
{
	namespace Concurrency
	{
		/**
		 * @brief Helper template implements an exponential backoff using pause and eventually OS sleep calls.
		 * @tparam MAX_SPIN Max number of pause calls before switching to sleep.
		 * @tparam SLEEP_MS Length of the OS level sleep to perform at max backoff.
		 */
		class Backoff
		{
		public:
			Backoff(int maxSpin = 32, int sleepMS = 5, int pauseCount = 5);
			~Backoff();

			void operator ()();
			void Reset();

			void SetMaxSpin(int ms);
			int GetMaxSpin() const;
			void SetSleepMS(int ms);
			int GetSleepMS() const;
			void SetPauseCount(int count);
			int GetPauseCount() const;

		private:
			int mBackoff;
			int mMaxSpin;
			int mPauseCount;
			int mSleepMS;
		};

		//////////////////////////////////////////////////////////////////////////
		inline Backoff::Backoff(int maxSpin, int sleepMS, int pauseCount)
			: mBackoff(1)
			, mMaxSpin(maxSpin)
			, mPauseCount(pauseCount)
			, mSleepMS(sleepMS)
		{
			VTUNE_SYNC_CREATE(Backoff, this, VTune::SyncType::eBarrier);
		}

		inline Backoff::~Backoff()
		{
			VTUNE_SYNC_DESTROY(this);
		}

		inline void Backoff::operator ()()
		{
			VTUNE_SYNC_PREPARE(this);
			if (mBackoff >= mMaxSpin)
			{
				VTUNE_SYNC_ACQUIRED(this);
				Threading::Thread::Sleep(Time::Ms(mSleepMS));
				VTUNE_SYNC_RELEASING(this);
			}
			else
			{
				VTUNE_SYNC_ACQUIRED(this);
				for (auto i = 0; i < mBackoff; ++i)
				{
					for (auto j=0; j<mPauseCount; ++j)
						Threading::Thread::Pause();
				}
				mBackoff = (mBackoff >= mMaxSpin) ? mBackoff : mBackoff << 1;
				VTUNE_SYNC_RELEASING(this);
			}
		}

		inline void Backoff:: Reset()
		{
			mBackoff = 1;
		}

		inline void Backoff::SetMaxSpin(int ms)
		{
			mMaxSpin = ms;
		}

		inline int Backoff::GetMaxSpin() const
		{
			return mMaxSpin;
		}

		inline void Backoff::SetSleepMS(int ms)
		{
			mSleepMS = ms;
		}

		inline int Backoff::GetSleepMS() const
		{
			return mSleepMS;
		}
		
		inline void Backoff::SetPauseCount(int count)
		{
			mPauseCount = count;
		}
		
		inline int Backoff::GetPauseCount() const
		{
			return mPauseCount;
		}
	}
}
