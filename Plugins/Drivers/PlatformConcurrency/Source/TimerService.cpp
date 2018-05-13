//////////////////////////////////////////////////////////////////////////
#include "TimerService.hpp"
#include "CPF/Math/Algorithm.hpp"
#include "CPF/Threading/ScopedLock.hpp"

using namespace CPF;
using namespace Platform;

TimerService::TimerService()
    : mNow(Time::Now())
{
	// Resize all the wheels to the target hash resolution.
	mWheels.resize(kLevels);
	for (auto& wheel : mWheels)
		wheel.resize(64);

	// Initialize indexes.
	mIndexes.resize(kLevels, 0);
}

GOM::Result CPF_STDCALL TimerService::WaitForFirst()
{
	size_t level;
	int64_t index;

	for (;;)
	{
		if (_FindNextTimer(level, index))
		{
			const auto startTime = Time::Now();
			Time::Ms next;

			if (level != 0)
				next = Time::Ms(int64_t(std::powl(64, double(level))));
			else
				next = Time::Ms(index);

			mWaitCondition.TimedAcquire(mWaitMutex, Time::Value(next));

			const auto delta = Time::Ms(Time::Now() - startTime);
			int64_t triggered;
			Tick(int64_t(delta), &triggered);
			if (triggered > 0)
				return kComplete;
		}
		else
			break;
	}

	return kNoTimers;
}

GOM::Result CPF_STDCALL TimerService::Tick(int64_t deltaTimeMs, int64_t* outTriggered)
{
    const auto tickCount = deltaTimeMs;

	if (outTriggered)
		*outTriggered = 0;

    for (int64_t i = 0; i < tickCount; ++i)
    {
        // Increment by one ms to keep in step with the lowest level wheel.
        mNow = mNow + Time::Ms(1);

        // Increment the index for level 0.
        {
            Threading::ScopedLock<Threading::Mutex> lock(mWaitMutex);
            mIndexes[0] = (mIndexes[0] + 1) % 64;

            // Check for rollover.
            size_t level = 0;
            for (const auto index : mIndexes)
            {
                if (index != 0)
                    break;

                const auto oldIndex = mIndexes[level + 1];
                mIndexes[level + 1] = (mIndexes[level + 1] + 1) % 64;
                const auto timers = STD::Move(mWheels[level + 1][oldIndex]);
                for (const auto timerHandle : timers)
                {
                    const auto timer = mTimers.Get(timerHandle);
                    if (timer)
                        _InsertTimer(timer->mTarget, timerHandle);
                }

                ++level;
            }
        }

        STD::Vector<TimerHandle> slot;
        {
            Threading::ScopedLock<Threading::Mutex> lock(mWaitMutex);
            slot = STD::Move(_GetSlot(0, 0));
        }
        if (!slot.empty())
        {
            // We have timers to trigger.
			if (outTriggered)
				*outTriggered += int64_t(slot.size());
            for (const auto timerHandle : slot)
            {
                TimerData* timer;
                {
                    Threading::ScopedLock<Threading::Mutex> lock(mWaitMutex);
                    timer = mTimers.Get(timerHandle);
                }
                if (timer)
                {
                    (timer->mpCallback)(timerHandle, GOM::kOK, timer->mpContext);

                    if (timer->mType == TimerType::eInterval)
                    {
                        // Reinsert the timer.
                        _InsertTimer(mNow + timer->mTime, timerHandle);
                    }
                    else
                    {
                        Threading::ScopedLock<Threading::Mutex> lock(mWaitMutex);
                        mTimers.Erase(timerHandle);
                    }
                }
            }
        }
    }

	mWaitCondition.ReleaseAll();
	return GOM::kOK;
}

void CPF_STDCALL TimerService::Shutdown()
{
    for (const auto& timer : mTimers)
    {
        (timer.second.mpCallback)(timer.first, kCanceled, timer.second.mpContext);
        Cancel(timer.first);
    }
	mWaitCondition.ReleaseAll();
}

TimerHandle CPF_STDCALL TimerService::Delay(int64_t lengthMs, TimerFunction callback, void* context)
{
	// Store the timer data.
    TimerData data
    {
        TimerType::eDelay,
        Time::Ms(lengthMs),
        Time::Ms(),
        0, 0,
		callback,
		context
	};

    TimerHandle result;
    {
        Threading::ScopedLock<Threading::Mutex> lock(mWaitMutex);
        result = mTimers.Insert(data);
    }

	// Insert the handle in the appropriate wheel and slot.
    // If the length is 0, make it one so it will trigger the next time we are ticked.
    const auto target = mNow + Time::Ms(Math::Max(lengthMs, int64_t(1)));

    // Insert the timer into the wheels.
    _InsertTimer(target, result);
	mWaitCondition.ReleaseAll();

	return result;
}

TimerHandle CPF_STDCALL TimerService::Interval(int64_t lengthMs, TimerFunction callback, void* context)
{
    if (lengthMs > 0)
    {
        // Store the timer data.
        TimerData data
        {
            TimerType::eInterval,
            Time::Ms(lengthMs),
            Time::Ms(),
            0, 0,
            callback,
            context
        };
        TimerHandle result;
        {
            Threading::ScopedLock<Threading::Mutex> lock(mWaitMutex);
            result = mTimers.Insert(data);
        }

        // Insert the handle in the appropriate wheel and slot.
        const auto target = mNow + Time::Ms(lengthMs);

        // Insert the timer into the wheels.
        _InsertTimer(target, result);
		mWaitCondition.ReleaseAll();

        return result;
    }
    return TimerHandle::eInvalid;
}

GOM::Result CPF_STDCALL TimerService::Cancel(TimerHandle handle)
{
    TimerData* timer;
    {
        Threading::ScopedLock<Threading::Mutex> lock(mWaitMutex);
        timer = mTimers.Get(handle);
    }
    if (timer)
    {
        {
            Threading::ScopedLock<Threading::Mutex> lock(mWaitMutex);
            auto& slot = mWheels[timer->mLevel][timer->mSlot];
            for (auto it = slot.begin(); it != slot.end(); ++it)
            {
                if (*it == handle)
                {
                    slot.erase(it);
                    break;
                }
            }
        }
		(timer->mpCallback)(handle, kCanceled, timer->mpContext);
        {
            Threading::ScopedLock<Threading::Mutex> lock(mWaitMutex);
            mTimers.Erase(handle);
        }
		mWaitCondition.ReleaseAll();
		return GOM::kOK;
    }
    return GOM::kNotFound;
}

void TimerService::_InsertTimer(Time::Ms target, TimerHandle handle)
{
	const auto ms = int64_t(target - mNow);
	for (auto i=kLevels-1; i>=0; --i)
	{
        if (i == 0)
        {
            Threading::ScopedLock<Threading::Mutex> lock(mWaitMutex);
            auto timer = mTimers.Get(handle);
            if (timer)
            {
                timer->mTarget = target;
                timer->mLevel = 0;
                timer->mSlot = _GetOffsetSlot(0, ms);
                _GetSlot(0, ms).push_back(handle);
            }
            return;
        }
        const auto divisor = int64_t(std::powl(64, i));
        const int64_t slot = ms / divisor;
        if (slot != 0)
        {
            Threading::ScopedLock<Threading::Mutex> lock(mWaitMutex);
            auto timer = mTimers.Get(handle);
            if (timer)
            {
                timer->mTarget = target;
                timer->mLevel = i;
                timer->mSlot = _GetOffsetSlot(i, slot - 1);
                _GetSlot(i, slot - 1).push_back(handle);
            }
            return;
        }
    }
}

STD::Vector<TimerHandle>& TimerService::_GetSlot(size_t level, int64_t index)
{
    return mWheels[level][_GetOffsetSlot(level, index)];
}

int64_t TimerService::_GetOffsetSlot(size_t level, int64_t index) const
{
    CPF_ASSERT(level >= 0 && level < kLevels);
    CPF_ASSERT(index >= 0 && index < 64);
    return (mIndexes[level] + index) % 64;
}

bool TimerService::_FindNextTimer(size_t& level, int64_t& index) const
{
	if (mTimers.GetSize() == 0)
		return false;

	for (int i=0; i<kLevels; ++i)
	{
		for (int j=0; j<64; ++j)
		{
			if (!mWheels[i][_GetOffsetSlot(i, j)].empty())
			{
				level = i;
				index = j; // The index is 'not' adjusted by the ring indexing.
				return true;
			}
		}
	}
	CPF_ASSERT_ALWAYS; // We're leaking timers if this happens!
	return false;
}
