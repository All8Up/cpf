#include <gmock/gmock.h>
#include "IO/Directory.hpp"
#include "Plugin.hpp"
#include "Plugin/Library.hpp"
#include "TestPlugin/iTestPlugin.hpp"
#include "PluginHost/Registry.hpp"

TEST(Plugin, LoadUnload)
{
	Cpf::Plugin::Library testLib;
	EXPECT_TRUE(testLib.Load("./plugins/TestPlugin.cfp"));
	EXPECT_TRUE(testLib.Unload());
}

TEST(Plugin, GetAddress)
{
	Cpf::Plugin::Library testLib;
	EXPECT_TRUE(testLib.Load("./plugins/TestPlugin.cfp"));
	void* addr = testLib.GetAddress(kPluginAPIInstall);
	EXPECT_TRUE(addr != nullptr);
	EXPECT_TRUE(testLib.Unload());
}

TEST(Plugin, GetAddressTyped)
{
	Cpf::Plugin::Library testLib;
	EXPECT_TRUE(testLib.Load("./plugins/TestPlugin.cfp"));
	using RegType = int32_t(*)(Cpf::Plugin::iRegistry* registry);
	RegType addr = testLib.GetAddress<RegType>(kPluginAPIInstall);
	EXPECT_TRUE(addr != nullptr);
	EXPECT_TRUE(testLib.Unload());
}

TEST(Plugin, Registry)
{
	Cpf::IntrusivePtr<Cpf::Plugin::iRegistry> registry;
	Cpf::PluginHost::CreateRegistry(registry.AsTypePP());
	EXPECT_TRUE(bool(registry));
	registry.Release();
	EXPECT_FALSE(bool(registry));
}

TEST(Plugin, Register)
{
	Cpf::IntrusivePtr<Cpf::Plugin::iRegistry> registry;
	Cpf::PluginHost::CreateRegistry(registry.AsTypePP());
	EXPECT_TRUE(bool(registry));

	EXPECT_TRUE(Cpf::GOM::Succeeded(registry->Load("./plugins/TestPlugin.cfp")));
	EXPECT_TRUE(Cpf::GOM::Succeeded(registry->Exists(Cpf::kTestPluginCID.GetID())));

	registry.Release();
	EXPECT_FALSE(bool(registry));
}

TEST(Plugin, CreateAndCall)
{
	Cpf::IntrusivePtr<Cpf::Plugin::iRegistry> registry;
	Cpf::PluginHost::CreateRegistry(registry.AsTypePP());
	EXPECT_TRUE(bool(registry));

	EXPECT_TRUE(Cpf::GOM::Succeeded(registry->Load("./plugins/TestPlugin.cfp")));
	EXPECT_TRUE(Cpf::GOM::Succeeded(registry->Exists(Cpf::kTestPluginCID.GetID())));

	Cpf::IntrusivePtr<Cpf::iTestPlugin> testPlugin;
	EXPECT_TRUE(Cpf::GOM::Succeeded(registry->Create(nullptr, Cpf::kTestPluginCID.GetID(), Cpf::iTestPlugin::kIID.GetID(), testPlugin.AsVoidPP())));
	EXPECT_TRUE(bool(testPlugin));

	EXPECT_TRUE(0 == testPlugin->Test());

	testPlugin.Release();
	EXPECT_FALSE(bool(testPlugin));
	registry.Release();
	EXPECT_FALSE(bool(registry));
}
