//////////////////////////////////////////////////////////////////////////
#include "CPF/Plugin.hpp"
#include "CPF/Application.hpp"
#include "CPF/GOM/tUnknown.hpp"
#include "CPF/Platform/Concurrency/iThreadPool.hpp"
#include "CPF/Platform/Concurrency/iTimerService.hpp"
#include "CPF/Threading/Thread.hpp"
#include <CPF/Threading/Future.hpp>

using namespace CPF;
using namespace Platform;

/*
Simple testbed for timers which is going to be transitioned to futures.
*/
struct TimerTest
{
	TimerTest(iTimerService* timerService)
		: mHandle(timerService->Interval(
			Time::Ms(Time::Seconds(2)),
			&TimerTest::Callback,
			this))
		, mCount(0)
		, mpTimerService(timerService)
	{
	}

	static void Callback(TimerHandle handle, GOM::Result result, void* context)
	{
		if (result == kCanceled)
		{
			printf("Canceled: %s\n", std::to_string(int64_t(Time::Ms(Time::Now()))).c_str());
			return;
		}

		printf("Tick: %s\n", std::to_string(int64_t(Time::Ms(Time::Now()))).c_str());
		auto& self = *reinterpret_cast<TimerTest*>(context);

        // Run 10 times and then cancel.
		if (++self.mCount > 10)
			self.mpTimerService->Cancel(handle);
		CPF_ASSERT(self.mHandle == handle);
	}

	TimerHandle mHandle;
	int mCount;
	iTimerService* mpTimerService;
};

// Aggregates a timer service to return futures.
#if 0
class AsyncTimerService
{
public:
    AsyncTimerService(iTimerService* service) : mpTimerService(service) {}

    Future<AsyncResult<TimerHandle, GOM::Result>>&& Delay(int64_t ms, Executor* executure = nullptr);
    Future<AsyncResult<TimerHandle, GOM::Result>>&& Interval(int64_t ms, Executor* executure = nullptr);

private:
    iTimerService* mpTimerService;
};
#endif

struct iEventStream : GOM::iUnknown
{
    static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("EventStream"_crc64);

};

struct iRuntime : GOM::iUnknown
{
    static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Runtime"_crc64);

    virtual void CPF_STDCALL InstallThreadPool(iThreadPool* threadPool) = 0;
    virtual void CPF_STDCALL InstallTimerService(iTimerService* timerService) = 0;

    virtual iEventStream* CPF_STDCALL Interval(int64_t ms) = 0;
};

// Standard event driven runtime.  Generally speaking, everything runs in the installed
// thread pool.
class Runtime : public GOM::tUnknown<iRuntime>
{
public:
    Runtime(Plugin::iRegistry* registry) : mpRegistry(registry) {}

    void CPF_STDCALL InstallThreadPool(iThreadPool* threadPool) override { mpThreadPool = IntrusivePtr<iThreadPool>(threadPool); }
    void CPF_STDCALL InstallTimerService(iTimerService* timerService) override { mpTimerService = IntrusivePtr<iTimerService>(timerService); }
    iEventStream* CPF_STDCALL Interval(int64_t ms) override { return nullptr; }

private:
    IntrusivePtr<Plugin::iRegistry> mpRegistry;
    IntrusivePtr<iThreadPool> mpThreadPool;
    IntrusivePtr<iTimerService> mpTimerService;
};



CPF_BEGIN_PLUGINS(ExampleCoreEventDriven)
CPF_INSTALL_PLUGIN(ExampleCoreEventDriven, PlatformConcurrency);

/** @brief A basic event driven console application.
 */
class ExampleCoreEventDriven : public GOM::tUnknown<iApplication>
{
    IntrusivePtr<iThreadPool> mpPool;
	IntrusivePtr<iTimerService> mpTimerService;

public:
	ExampleCoreEventDriven(Plugin::iRegistry* registry)
		: mpRegistry(registry)
	{}

	int32_t Run() override
	{
        int32_t result = -1;

		if (GOM::Succeeded(CPF_INSTALL_PLUGINS(mpRegistry, ExampleCoreEventDriven)))
		{
			if (GOM::Succeeded(mpRegistry->Create(nullptr, iThreadPool::kCID, iThreadPool::kIID, mpPool.AsVoidPP())) &&
	            GOM::Succeeded(mpPool->Initialize(4)) &&
				GOM::Succeeded(mpRegistry->Create(nullptr, iTimerService::kCID, iTimerService::kIID, mpTimerService.AsVoidPP())))
		    {
                /*
                First things first, start a simple test for the timer service.
                */

                TimerTest timerTest(mpTimerService);

                for (; mpTimerService->WaitForFirst() != kNoTimers;)
                    ;

                // Start of the real thing.
                // Manually build up the runtime object.
                IntrusivePtr<iRuntime> runtime(new Runtime(mpRegistry));
                runtime->InstallThreadPool(mpPool);
                runtime->InstallTimerService(mpTimerService);

                //
                auto interval = TakeIntrusivePtr(runtime->Interval(Time::Ms(Time::Seconds(5.0f))));

                /*
                test = runtime->Interval(Time::Seconds(5))
                    .Take(10)
                    .ForEach([](AsyncHandle handle) {
                        printf("Interval.\n");
                    })
                    .MapError([](AsyncHandle handle, GOM::Result error) {
                        printf("Error in interval timer.\n");
                    });
                runtime->Run(test);
                */
            }
			if (!GOM::Failed(CPF_REMOVE_PLUGINS(mpRegistry, ExampleCoreEventDriven)))
				result = -2;
			else
				result = 0;
		}
		return result;
	}

private:
	Plugin::iRegistry* mpRegistry;
};

/* Utility macro registers the application as a plugin.
 */
CPF_APPLICATION(ExampleCoreEventDriven);
