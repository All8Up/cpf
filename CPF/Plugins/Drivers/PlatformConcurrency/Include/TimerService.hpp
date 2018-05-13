//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Concurrency/iTimerService.hpp"
#include "CPF/Time.hpp"
#include <CPF/GOM/tUnknown.hpp>
#include "CPF/Std/Vector.hpp"
#include "CPF/Std/PackedPool.hpp"
#include "CPF/Threading/ConditionVariable.hpp"

namespace CPF
{
	namespace Platform
	{
		class TimerService : public GOM::tUnknown<iTimerService>
		{
		public:
			TimerService();
			TimerService(const TimerService&) = delete;
			TimerService(TimerService&&) = default;
			~TimerService() = default;

			TimerService& operator = (const TimerService&) = delete;
			TimerService& operator = (TimerService&&) = default;

			GOM::Result CPF_STDCALL WaitForFirst() override;
			GOM::Result CPF_STDCALL Tick(int64_t deltaTimeMs, int64_t* outTriggered) override;
			void CPF_STDCALL Shutdown() override;

			TimerHandle CPF_STDCALL Delay(int64_t lengthMs, TimerFunction callback, void* context) override;
			TimerHandle CPF_STDCALL Interval(int64_t lengthMs, TimerFunction callback, void* context) override;

            GOM::Result CPF_STDCALL Cancel(TimerHandle handle) override;

		private:
			void _InsertTimer(Time::Ms target, TimerHandle handle);
            STD::Vector<TimerHandle>& _GetSlot(size_t level, int64_t index);
            int64_t _GetOffsetSlot(size_t level, int64_t index) const;
			bool _FindNextTimer(size_t& level, int64_t& index) const;

			// Implementation based on hierarchical hashed timers.
			Time::Ms mNow;

			enum class TimerType : int32_t
			{
				eDelay,
				eInterval
			};
			struct TimerData
			{
				TimerType mType;
				Time::Ms mTime;
                Time::Ms mTarget;
                int64_t mLevel;
                int64_t mSlot;
				TimerFunction mpCallback;
				void* mpContext;
			};
			STD::PackedPool<TimerHandle, TimerData> mTimers;

			static constexpr int kLevels = 6;

			// Time wheels.
			STD::Vector<STD::Vector<STD::Vector<TimerHandle>>> mWheels;
			// Indexes.
			STD::Vector<size_t> mIndexes;

			// For the wait implementation.
			Threading::ConditionVariable mWaitCondition;
			Threading::Mutex mWaitMutex;
		};
	}
}
