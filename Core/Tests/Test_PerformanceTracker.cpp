//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "CPF/Performance/Tracker.hpp"

TEST(PerformanceTracker, ManualScoped)
{
	CPF_PERF_BEGIN("TestGroup", "TestSection");
	CPF_PERF_END("TestGroup", "TestSection");
}

TEST(PerformanceTracker, ScopedBlock)
{
	CPF_PERF_BLOCK("TestGroup", "TestSection");
}
