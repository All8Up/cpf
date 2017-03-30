#include <gmock/gmock.h>
#include "IO/Directory.hpp"
#include "Plugin.hpp"

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
	void* addr = testLib.GetAddress("Register");
	EXPECT_TRUE(addr != nullptr);
	EXPECT_TRUE(testLib.Unload());
}

TEST(Plugin, GetAddressTyped)
{
	Cpf::Plugin::Library testLib;
	EXPECT_TRUE(testLib.Load("./plugins/TestPlugin.cfp"));
	using RegType = int32_t(*)(Cpf::Plugin::iRegistry* registry);
	RegType addr = testLib.GetAddress<RegType>("Register");
	EXPECT_TRUE(addr != nullptr);
	EXPECT_TRUE(testLib.Unload());
}

TEST(Plugin, Call)
{
	Cpf::Plugin::Library testLib;
	EXPECT_TRUE(testLib.Load("./plugins/TestPlugin.cfp"));
	using RegType = int32_t(*)(Cpf::Plugin::iRegistry* registry);
	RegType addr = testLib.GetAddress<RegType>("Register");
	EXPECT_TRUE(addr != nullptr);
	EXPECT_TRUE(0 == (*addr)(nullptr));
	EXPECT_TRUE(testLib.Unload());
}
