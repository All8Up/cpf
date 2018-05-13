//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "Test_All.hpp"
#include "CPF/Platform/Concurrency/iTimerService.hpp"
#include "CPF/GOM/ResultCodes.hpp"

TEST_F(ConcurrencyTest, iTimerService_Delay)
{
    using namespace CPF;
    using namespace Platform;

    struct Tester
    {
        static void TimerCallback(TimerHandle handle, GOM::Result result, void* context)
        {
            auto& tester = *reinterpret_cast<Tester*>(context);
            ++tester.mCallbackCount;
            tester.mLastHandle = handle;
            tester.mLastResult = result;
        }
        int32_t mCallbackCount = 0;
        TimerHandle mLastHandle;
        GOM::Result mLastResult;
    };
    Tester tester;

    IntrusivePtr<iTimerService> timerService;
    EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iTimerService::kCID, iTimerService::kIID, timerService.AsVoidPP())));

    const TimerHandle handle1 = timerService->Delay(10, &Tester::TimerCallback, &tester);
    EXPECT_TRUE(handle1 != TimerHandle::eInvalid);

    const TimerHandle handle2 = timerService->Delay(100, &Tester::TimerCallback, &tester);
    EXPECT_TRUE(handle2 != TimerHandle::eInvalid);

    // Tick 5 times at 1 ms each.
    for (int i = 0; i < 5; ++i) timerService->Tick(1, nullptr);

    // Create another timer pair.
    const TimerHandle handle3 = timerService->Delay(10, &Tester::TimerCallback, &tester);
    EXPECT_TRUE(handle1 != TimerHandle::eInvalid);

    const TimerHandle handle4 = timerService->Delay(100, &Tester::TimerCallback, &tester);
    EXPECT_TRUE(handle4 != TimerHandle::eInvalid);

    // Tick 4 times.
    for (int i = 0; i < 4; ++i) timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 0);
    // Tick should trigger the first callback.
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 1);
    EXPECT_EQ(tester.mLastHandle, handle1);
    EXPECT_EQ(tester.mLastResult, GOM::kOK);

    // Tick 4 times.
    for (int i = 0; i < 4; ++i) timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 1);

    // Tick should trigger the third callback.
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 2);
    EXPECT_EQ(tester.mLastHandle, handle3);
    EXPECT_EQ(tester.mLastResult, GOM::kOK);

    // We should be at tick 15, so we need 100-15 ticks to trigger handle2.
    timerService->Tick(100 - 15 - 1, nullptr); // Do one less than needed.
    EXPECT_EQ(tester.mCallbackCount, 2);

    // Tick should trigger the second callback.
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 3);
    EXPECT_EQ(tester.mLastHandle, handle2);
    EXPECT_EQ(tester.mLastResult, GOM::kOK);

    // And 5 ticks later should be the final timer.
    timerService->Tick(4, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 3);

    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 4);
    EXPECT_EQ(tester.mLastHandle, handle4);
    EXPECT_EQ(tester.mLastResult, GOM::kOK);

    // Let's test a 3 wheel timer.
    const TimerHandle handle5 = timerService->Delay(4096, &Tester::TimerCallback, &tester);
    EXPECT_TRUE(handle5 != TimerHandle::eInvalid);

    timerService->Tick(4095, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 4);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 5);

    // Let's test a 4 wheel timer.
    const TimerHandle handle6 = timerService->Delay(4096*64, &Tester::TimerCallback, &tester);
    EXPECT_TRUE(handle6 != TimerHandle::eInvalid);

    timerService->Tick((4096 * 64) - 1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 5);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 6);
}

TEST_F(ConcurrencyTest, iTimerService_Interval)
{
    using namespace CPF;
    using namespace Platform;

    struct Tester
    {
        static void TimerCallback(TimerHandle handle, GOM::Result result, void* context)
        {
            if (GOM::Succeeded(result))
            {
                auto& tester = *reinterpret_cast<Tester*>(context);
                ++tester.mCallbackCount;
                tester.mLastHandle = handle;
                tester.mLastResult = result;
            }
        }
        int32_t mCallbackCount = 0;
        TimerHandle mLastHandle;
        GOM::Result mLastResult;
    };
    Tester tester;

    IntrusivePtr<iTimerService> timerService;
    EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, iTimerService::kCID, iTimerService::kIID, timerService.AsVoidPP())));

    const TimerHandle handle1 = timerService->Interval(5, &Tester::TimerCallback, &tester);
    timerService->Tick(1, nullptr);
    const TimerHandle handle2 = timerService->Interval(5, &Tester::TimerCallback, &tester);
    timerService->Tick(1, nullptr);
    const TimerHandle handle3 = timerService->Interval(5, &Tester::TimerCallback, &tester);
    timerService->Tick(1, nullptr);
    const TimerHandle handle4 = timerService->Interval(5, &Tester::TimerCallback, &tester);
    timerService->Tick(1, nullptr);
    const TimerHandle handle5 = timerService->Interval(5, &Tester::TimerCallback, &tester);

    EXPECT_EQ(tester.mCallbackCount, 0);

    // First tick for each timer.
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 1);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 2);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 3);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 4);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 5);

    // Second tick for each timer.
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 6);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 7);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 8);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 9);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 10);

    // And cancel a couple, then
    EXPECT_TRUE(GOM::Succeeded(timerService->Cancel(handle3)));
    EXPECT_TRUE(GOM::Succeeded(timerService->Cancel(handle4)));

    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 11);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 12);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 12);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 12);
    timerService->Tick(1, nullptr);
    EXPECT_EQ(tester.mCallbackCount, 13);
}
