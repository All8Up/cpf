#include <gtest/gtest.h>
#include "CPF/IO/Directory.hpp"
#include "CPF/Plugin.hpp"
#include "CPF/Plugin/Library.hpp"
#include "TestPlugin/iTestPlugin.hpp"
#include "CPF/Plugin/Registry.hpp"
#include "CPF/IntrusivePtr.hpp"

TEST(Plugin, LoadUnload)
{
	CPF::Plugin::Library testLib;
	EXPECT_TRUE(testLib.Load("./plugins/TestPlugin.cfp"));
	EXPECT_TRUE(testLib.Unload());
}

TEST(Plugin, GetAddress)
{
	CPF::Plugin::Library testLib;
	EXPECT_TRUE(testLib.Load("./plugins/TestPlugin.cfp"));
	void* addr = testLib.GetAddress(kPluginAPIGetDesc);
	EXPECT_TRUE(addr != nullptr);
	EXPECT_TRUE(testLib.Unload());
}

TEST(Plugin, GetAddressTyped)
{
	CPF::Plugin::Library testLib;
	EXPECT_TRUE(testLib.Load("./plugins/TestPlugin.cfp"));
	using RegType = int32_t(*)(CPF::Plugin::iRegistry* registry);
	RegType addr = testLib.GetAddress<RegType>(kPluginAPIGetDesc);
	EXPECT_TRUE(addr != nullptr);
	EXPECT_TRUE(testLib.Unload());
}

TEST(Plugin, Registry)
{
	CPF::IntrusivePtr<CPF::Plugin::iRegistry> registry;
	CPF::PluginHost::CreateRegistry(registry.AsTypePP());
	EXPECT_TRUE(bool(registry));
	registry.Release();
	EXPECT_FALSE(bool(registry));
}

TEST(Plugin, Register)
{
	CPF::IntrusivePtr<CPF::Plugin::iRegistry> registry;
	CPF::PluginHost::CreateRegistry(registry.AsTypePP());
	EXPECT_TRUE(bool(registry));

	EXPECT_TRUE(CPF::GOM::Succeeded(registry->Load("./plugins/TestPlugin.cfp")));
	EXPECT_TRUE(CPF::GOM::Succeeded(registry->Exists(CPF::kTestPluginCID.GetID())));

	registry.Release();
	EXPECT_FALSE(bool(registry));
}

TEST(Plugin, CreateAndCall)
{
	CPF::IntrusivePtr<CPF::Plugin::iRegistry> registry;
	CPF::PluginHost::CreateRegistry(registry.AsTypePP());
	EXPECT_TRUE(bool(registry));

	EXPECT_TRUE(CPF::GOM::Succeeded(registry->Load("./plugins/TestPlugin.cfp")));
	EXPECT_TRUE(CPF::GOM::Succeeded(registry->Exists(CPF::kTestPluginCID.GetID())));

	CPF::IntrusivePtr<CPF::iTestPlugin> testPlugin;
	EXPECT_TRUE(CPF::GOM::Succeeded(registry->Create(nullptr, CPF::kTestPluginCID.GetID(), CPF::iTestPlugin::kIID.GetID(), testPlugin.AsVoidPP())));
	EXPECT_TRUE(bool(testPlugin));

	EXPECT_TRUE(0 == testPlugin->Test());

	testPlugin.Release();
	EXPECT_FALSE(bool(testPlugin));
	registry.Release();
	EXPECT_FALSE(bool(registry));
}
