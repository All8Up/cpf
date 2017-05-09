//////////////////////////////////////////////////////////////////////////
#pragma once
#include "gmock/gmock.h"
#include "PluginHost/Registry.hpp"

extern "C" void CPF_EXPORT InstallScheduler(Cpf::Plugin::iRegistry*);
extern "C" void CPF_EXPORT RemoveScheduler(Cpf::Plugin::iRegistry*);

class ConcurrencyTest : public::testing::Test
{
public:
	virtual void SetUp()
	{
		Cpf::PluginHost::CreateRegistry(mpRegistry.AsTypePP());
		InstallScheduler(mpRegistry);
	}

	virtual void TearDown()
	{
		RemoveScheduler(mpRegistry);
		mpRegistry.Adopt(nullptr);
	}

	Cpf::Plugin::iRegistry* GetRegistry() { return mpRegistry; }

	Cpf::IntrusivePtr<Cpf::Plugin::iRegistry> mpRegistry;
};
