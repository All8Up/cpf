#include <gtest/gtest.h>
#include "CPF/Plugin.hpp"
#include "TestPlugin/iTestPlugin.hpp"
#include "CPF/Plugin/Registry.hpp"
#include "CPF/IntrusivePtr.hpp"

TEST(StaticPlugin, Exists)
{
	CPF::IntrusivePtr<CPF::Plugin::iRegistry> registry;
	CPF::PluginHost::CreateRegistry(registry.AsTypePP());
	CPF_INSTALL_STATIC_PLUGIN(registry, TestPlugin);
	EXPECT_TRUE(CPF::GOM::Succeeded(registry->Exists(CPF::kTestPluginCID.GetID())));
}
