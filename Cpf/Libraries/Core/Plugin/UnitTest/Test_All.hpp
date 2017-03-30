#include <gmock/gmock.h>
#include "IO/Directory.hpp"
#include "Plugin.hpp"

TEST(Plugin, Load)
{
	Cpf::Plugin::Library testLib("./plugins/TestPlugin.cfp");
	EXPECT_TRUE(bool(testLib));
	auto regFunc = testLib.GetAddress("Register");
	EXPECT_TRUE(regFunc != nullptr);
}
