//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "CPF/Performance/Tracker.hpp"

TEST(PerformanceTracker, ManualScoped)
{
	CPF::Performance::InstallListener(new CPF::Performance::DefaultListener());
	CPF::Performance::Initialize();
	CPF_PERF_BEGIN("TestGroup", "TestSection");
	CPF_PERF_END("TestGroup", "TestSection");
	CPF::Performance::Shutdown();
}

TEST(PerformanceTracker, ScopedBlock)
{
	CPF::Performance::InstallListener(new CPF::Performance::DefaultListener());
	CPF::Performance::Initialize();
	CPF_PERF_BLOCK("TestGroup", "TestSection");
	CPF::Performance::Shutdown();
}
