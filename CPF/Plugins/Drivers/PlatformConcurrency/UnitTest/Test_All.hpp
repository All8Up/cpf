//////////////////////////////////////////////////////////////////////////
#pragma once
#include "gtest/gtest.h"
#include "CPF/Plugin/Registry.hpp"
#include "CPF/IntrusivePtr.hpp"
#include "CPF/Logging.hpp"

class ConcurrencyTest : public::testing::Test
{
public:
	static bool mLoggingInitialized;
	virtual void SetUp()
	{
		if (!mLoggingInitialized)
		{
			char* argv = "";
			CPF_INIT_LOGGING(0, argv);
			mLoggingInitialized = true;
		}
		CPF::PluginHost::CreateRegistry(mpRegistry.AsTypePP());
		EXPECT_TRUE(CPF::GOM::Succeeded(mpRegistry->Load("./plugins/PlatformConcurrency.cfp")));
	}

	virtual void TearDown()
	{
		EXPECT_TRUE(CPF::GOM::Succeeded(mpRegistry->Unload("./plugins/PlatformConcurrency.cfp")));
		mpRegistry.Adopt(nullptr);
	}

	CPF::Plugin::iRegistry* GetRegistry() { return mpRegistry; }

	CPF::IntrusivePtr<CPF::Plugin::iRegistry> mpRegistry;
};
