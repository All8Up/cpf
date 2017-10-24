//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/IO/File.hpp"

TEST(IO, Basics)
{
	using namespace CPF::IO::File;
	FileSystemHelper::Initialize();
	try
	{
		if (CPF::GOM::Failed(Exists("does_not_exist.txt").Get()))
		{}
	}
	catch (CPF::Exception& exception)
	{
		(void)exception;
	}
}

#if 0
#include "String.hpp"
#include "Vector.hpp"
#include "Algorithm.hpp"
#include "Adapter/FileSystem.hpp"


//////////////////////////////////////////////////////////////////////////
class IOTestFixture : public testing::Test
{
public:
	CPF::Vector<CPF::String> mTestPaths;
	CPF::Vector<CPF::String> mNormPaths;
	CPF::Vector<CPF::WString> mWTestPaths;
	CPF::Vector<CPF::WString> mWNormPaths;

	virtual void SetUp() override
	{
		CPF::IOInitializer::Install();

		CPF::String paths[] =
		{
			"test/path/",						// A standard non-rooted path.
			"c:\\test\\path\\",					// Window's style rooted path.
			"/test/path/",						// A linux style rooted path.
			"c:\\Users\\test.user\\",			// Windows's style path in a user folder with dot naming.
			"/Users/hey.you/",					// A linux style path in the user folder with dot naming.
			"test/path/blargo",					// A path and file without extension.
			"test/path/blargo.txt",				// A path and file with extension.
			"/Users/hey.you/blargo.txt",		// A unix style rooted path with dot named folder and a file with extension.
			"C:\\Users\\hey.you\\blargo.txt",	// A windows style rooted path into a dot named user folder with file and extension.
			"   /Users/hey.you/  "				// Add some leading and trailing spaces to screw things up.
		};
		mNormPaths =
		{
			"test/path/",
			"c:/test/path/",
			"/test/path/",
			"c:/Users/test.user/",
			"/Users/hey.you/",
			"test/path/blargo",
			"test/path/blargo.txt",
			"/Users/hey.you/blargo.txt",
			"C:/Users/hey.you/blargo.txt",
			"/Users/hey.you/"
		};
		for (const auto& path : mNormPaths)
		{
			CPF::WString wpath;
			CPF::ForEach(path.begin(), path.end(), [&](const char c) { wpath.push_back(wchar_t(c)); });
			mWNormPaths.push_back(wpath);
		}

		for (const auto& path : paths)
		{
			mTestPaths.push_back(path);
			CPF::WString wpath;
			CPF::ForEach(path.begin(), path.end(), [&](const char c) { wpath.push_back(wchar_t(c)); });
			mWTestPaths.push_back(wpath);
		}
	}

	virtual void TearDown() override
	{
		CPF::IOInitializer::Remove();
	}

	struct TestRawBinary
	{
		uint32_t one;
		int32_t two;
		int64_t three;
	};
};


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
