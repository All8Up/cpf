//////////////////////////////////////////////////////////////////////////
#pragma once
#include "gmock/gmock.h"
#include "PluginHost/Registry.hpp"

extern "C" void CPF_EXPORT InstallScheduler(CPF::Plugin::iRegistry*);
extern "C" void CPF_EXPORT RemoveScheduler(CPF::Plugin::iRegistry*);

class ConcurrencyTest : public::testing::Test
{
public:
	virtual void SetUp()
	{
		CPF::PluginHost::CreateRegistry(mpRegistry.AsTypePP());
		InstallScheduler(mpRegistry);
	}

	virtual void TearDown()
	{
		RemoveScheduler(mpRegistry);
		mpRegistry.Adopt(nullptr);
	}

	CPF::Plugin::iRegistry* GetRegistry() { return mpRegistry; }

	CPF::IntrusivePtr<CPF::Plugin::iRegistry> mpRegistry;
};
