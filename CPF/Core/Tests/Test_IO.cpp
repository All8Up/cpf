#include <gtest/gtest.h>
#include "CPF/IO/File.hpp"
#include "CPF/GOM/Result.hpp"
#include "CPF/Plugin/Registry.hpp"
#include "CPF/Plugin/iRegistry.hpp"
#include "CPF/Std/Algorithm.hpp"
//#include "CPF/IO/Default.hpp"

#if 0
TEST(IO, Basics)
{
	using namespace CPF;
	using namespace GOM;
	using namespace IO;
	using namespace File;
	IntrusivePtr<Plugin::iRegistry> registry;

	EXPECT_TRUE(Succeeded(PluginHost::CreateRegistry(registry.AsTypePP())));
	EXPECT_TRUE(Succeeded(DefaultIO::Install(registry)));
	EXPECT_TRUE(FileSystemHelper::Initialize(registry));

	ASSERT_THROW(Failed(Exists("does_not_exist.txt").Get()), std::exception);
}
#endif


#if 0
//////////////////////////////////////////////////////////////////////////
#include "Test_File.hpp"
#include "Test_Directory.hpp"
#include "Test_Path.hpp"
#include "Test_Globbing.hpp"
#include "Test_BinaryReader.hpp"
#include "Test_BinaryWriter.hpp"
// Not sure what is wrong with this at the moment, should work but even in binary mode it is skipping cr/lf.
//#include "Test_TextReader.hpp"
#include "Test_TextWriter.hpp"

//////////////////////////////////////////////////////////////////////////
#include "IO/Result.hpp"

TEST(IO, Result)
{
	using namespace CPF::IO;
	using TestResult = Result<int64_t, std::string>;

	TestResult t0(TestResult::Error("Test"));
	EXPECT_TRUE(t0.IsError());
	EXPECT_FALSE(t0.IsOK());
	EXPECT_STREQ("Test", t0.Error().c_str());

	TestResult t1(TestResult::OK(1));
	EXPECT_TRUE(t1.IsOK());
	EXPECT_FALSE(t1.IsError());
	EXPECT_EQ(1, t1.OK());
}
#endif
