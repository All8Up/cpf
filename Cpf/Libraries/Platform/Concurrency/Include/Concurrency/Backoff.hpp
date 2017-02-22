//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/Concurrency.hpp"
#include "Threading/Thread.hpp"
#include "VTune/VTune.hpp"


namespace Cpf
{
	namespace Concurrency
	{
		/**
		 * @brief Helper template implements an exponential backoff using pause and eventually OS sleep calls.
		 * @tparam MAX_SPIN Max number of pause calls before switching to sleep.
		 * @tparam SLEEP_MS Length of the OS level sleep to perform at max backoff.
		 */
		template<const int MAX_SPIN = 1024, const int SLEEP_MS = 1>
		class Backoff
		{
		public:
			Backoff();
			~Backoff();

			void operator ()();
			void Reset();

		private:
			int mBackoff;
		};


		template<const int MAX_SPIN, const int SLEEP_MS>
		Backoff<MAX_SPIN, SLEEP_MS>::Backoff()
			: mBackoff(1)
		{
			VTUNE_SYNC_CREATE(Backoff, this, VTune::SyncType::eBarrier);
		}

		template<const int MAX_SPIN, const int SLEEP_MS>
		Backoff<MAX_SPIN, SLEEP_MS>::~Backoff()
		{
			VTUNE_SYNC_DESTROY(this);
		}

		template<const int MAX_SPIN, const int SLEEP_MS>
		void Backoff<MAX_SPIN, SLEEP_MS>::operator ()()
		{
			VTUNE_SYNC_PREPARE(this);
			if (mBackoff >= MAX_SPIN)
			{
				VTUNE_SYNC_ACQUIRED(this);
				Platform::Threading::Thread::Sleep(Platform::Time::Ms(SLEEP_MS));
				VTUNE_SYNC_RELEASING(this);
			}
			else
			{
				VTUNE_SYNC_ACQUIRED(this);
				for (auto i = 0; i < mBackoff; ++i)
					Platform::Threading::Thread::Pause();
				mBackoff <<= 1;
				VTUNE_SYNC_RELEASING(this);
			}
		}


		template<const int MAX_SPIN, const int SLEEP_MS>
		void Backoff<MAX_SPIN, SLEEP_MS>:: Reset()
		{
			mBackoff = 1;
		}
	}
}
