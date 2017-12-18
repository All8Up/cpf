#pragma once
#include <gtest/gtest.h>
#include <CPF/Std/Vector.hpp>
#include <CPF/Std/String.hpp>
#include <CPF/Std/Algorithm.hpp>
#include <CPF/IO.hpp>

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
	}

	struct TestRawBinary
	{
		uint32_t one;
		int32_t two;
		int64_t three;
	};
};
