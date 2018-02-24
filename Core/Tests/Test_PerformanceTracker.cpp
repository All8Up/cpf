//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "CPF/Performance/Tracker.hpp"

using namespace CPF;
using namespace Performance;

struct TestListener : TrackerListener
{
	void SetInfo(Tick, intmax_t, intmax_t) override
	{
		InfoSet = true;;
	}

	void ThreadNamed(size_t, const char*) override
	{
		++ThreadNames;
	}

	void IDMapped(int32_t, const char*) override
	{
		++IDMappings;
	}

	void BeginBlock(size_t, int32_t, int32_t, Tick) override
	{
		++BeginBlockCount;
	}

	void EndBlock(size_t, int32_t, int32_t, Tick) override
	{
		++EndBlockCount;
	}

	void BeginFrame(Tick) override
	{
		++BeginFrameCount;
	}
	void EndFrame(Tick) override
	{
		++EndFrameCount;
	}

	void Flush() override
	{
		++FlushCount;
	}

	bool InfoSet = false;
	int32_t ThreadNames = 0;
	int32_t IDMappings = 0;
	int32_t BeginBlockCount = 0;
	int32_t EndBlockCount = 0;
	int32_t BeginFrameCount = 0;
	int32_t EndFrameCount = 0;
	int32_t FlushCount = 0;
};

TEST(PerformanceTracker, ManualScoped)
{
	auto* listener = new TestListener();
	InstallListener(listener); // NOTE: Takes ownership and will destroy at shutdown.
	Initialize();
	CPF_PERF_THREAD_NAME("Main");
	{
		CPF_PERF_BEGIN("TestGroup", "TestSection");
		CPF_PERF_END("TestGroup", "TestSection");
	}
	CPF_PERF_FLUSH;

	EXPECT_TRUE(listener->InfoSet);
	EXPECT_EQ(listener->ThreadNames, 1);
	EXPECT_EQ(listener->IDMappings, 2);
	EXPECT_EQ(listener->BeginBlockCount, 1);
	EXPECT_EQ(listener->EndBlockCount, 1);
	EXPECT_EQ(listener->FlushCount, 1);

	Shutdown();
}

TEST(PerformanceTracker, ScopedBlock)
{
	auto* listener = new TestListener();
	InstallListener(listener); // NOTE: Takes ownership and will destroy at shutdown.
	Initialize();
	CPF_PERF_THREAD_NAME("Main");
	{
		CPF_PERF_BLOCK("TestGroup", "TestSection");
	}
	CPF_PERF_FLUSH;

	EXPECT_TRUE(listener->InfoSet);
	// NOTE: Due to the way things work, some of these are zero due to having been initialized above.
	// This is not a problem for the system and is intended, it is only a problem for testing.
	EXPECT_EQ(listener->ThreadNames, 0);
	EXPECT_EQ(listener->IDMappings, 0);
	EXPECT_EQ(listener->BeginBlockCount, 1);
	EXPECT_EQ(listener->EndBlockCount, 1);
	EXPECT_EQ(listener->FlushCount, 1);

	Shutdown();
}

TEST(PerformanceTracker, BeginEndFrame)
{
	auto* listener = new TestListener();
	InstallListener(listener); // NOTE: Takes ownership and will destroy at shutdown.
	InstallListener(new DefaultListener);
	Initialize();
	CPF_PERF_THREAD_NAME("Main");
	{
		CPF_PERF_FRAME_BEGIN();
		CPF_PERF_BEGIN("TestGroup", "TestSection");
		CPF_PERF_END("TestGroup", "TestSection");
		CPF_PERF_FRAME_END();
	}
	CPF_PERF_FLUSH;

	EXPECT_TRUE(listener->InfoSet);
	// NOTE: Due to the way things work, some of these are zero due to having been initialized above.
	// This is not a problem for the system and is intended, it is only a problem for testing.
	EXPECT_EQ(listener->ThreadNames, 0);
	EXPECT_EQ(listener->IDMappings, 1);
	EXPECT_EQ(listener->BeginBlockCount, 1);
	EXPECT_EQ(listener->EndBlockCount, 1);
	EXPECT_EQ(listener->FlushCount, 1);

	Shutdown();
}

TEST(PerformanceTracker, CounterCreate)
{
	Initialize();
	{
		CPF_PERF_COUNTER_CREATE("TestCounter", CounterType::eFrameZeroed);
		EXPECT_EQ(CPF_PERF_COUNTER_GET("TestCounter"), 0);

		CPF_PERF_COUNTER_SET("TestCounter", 5);
		EXPECT_EQ(CPF_PERF_COUNTER_GET("TestCounter"), 5);

		CPF_PERF_COUNTER_INC("TestCounter");

		EXPECT_STREQ(GetFirstCounter()->mpName, "TestCounter");
	}
	Shutdown();
}
