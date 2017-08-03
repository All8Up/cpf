//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IO/Path.hpp"


TEST(Path, Path_Construction)
{
	using namespace Cpf;
	using namespace IO;

	String test = Path::Normalize("Test");
	WString wtest = Path::Normalize(L"Test");
}

TEST_F(IOTestFixture, Normalize)
{
	using namespace Cpf;
	using namespace IO;

	int index = 0;
	for (const auto& path : mTestPaths)
	{
		const String test = Path::Normalize(path);
		EXPECT_TRUE(test == mNormPaths[index]);
		++index;
	}

	String test0 = Path::Normalize("c:\\wackawacka\\blargo");
	String expected0("c:/wackawacka/blargo");
	EXPECT_TRUE(test0 == expected0);

	WString test1 = Path::Normalize(L"c:\\wackawacka\\blargo");
	WString expected1(L"c:/wackawacka/blargo");
	EXPECT_TRUE(test1 == expected1);
}

TEST(Path, EnsureTrailingSeparator)
{
	using namespace Cpf;
	using namespace IO;

	{
		String test0 = Path::Normalize("c:\\wackawacka\\blargo");
		EXPECT_FALSE(test0.back() == '/');
		String test1 = Path::Normalize("c:\\wackawacka\\blargo\\");
		EXPECT_TRUE(test1.back() == '/');
	}
	{
		WString test0 = Path::Normalize(L"c:\\wackawacka\\blargo");
		EXPECT_FALSE(test0.back() == L'/');
		WString test1 = Path::Normalize(L"c:\\wackawacka\\blargo\\");
		EXPECT_TRUE(test1.back() == L'/');
	}
}

TEST(Path, DetectRooted)
{
	using namespace Cpf;
	using namespace IO;

	{
		// Check for windows styled rooted path.
		String testPath = Path::Normalize("c:\\wackawacka\\blargo");
		EXPECT_TRUE(Path::IsRooted(testPath));

		// Check for *nix styled rooted path.
		String testPath2 = Path::Normalize("\\wackawacka\\blargo");
		EXPECT_TRUE(Path::IsRooted(testPath2));
	}

	{
		// Check for windows styled rooted path.
		WString testPath = Path::Normalize(L"c:\\wackawacka\\blargo");
		EXPECT_TRUE(Path::IsRooted(testPath));

		// Check for *nix styled rooted path.
		WString testPath2 = Path::Normalize(L"\\wackawacka\\blargo");
		EXPECT_TRUE(Path::IsRooted(testPath2));
	}
}

TEST(Path, GetRoot)
{
	// NOTE: This is primarily for windows, nix roots are always empty.
	using namespace Cpf;
	using namespace IO;

	{
		// Check for windows styled rooted path.
		String testPath = Path::Normalize("c:\\wackawacka\\blargo");
		EXPECT_STREQ("c:", Path::GetRoot(testPath).c_str());
	}
}

TEST(Path, HasExtension)
{
	using namespace Cpf;
	using namespace IO;

	{
		String testPath = Path::Normalize("c:\\a\\b.txt");
		EXPECT_TRUE(Path::HasExtension(testPath));
	}
}

TEST(Path, Components)
{
	using namespace Cpf;
	using namespace IO;

	const String testPath(Path::Normalize("c:/this/is/a/test/"));
	Vector<String> results;
	for (const auto& part : Path::Components(Path::GetDirectory(testPath)))
		results.push_back(part);
	Vector<String> expected{ "this", "is", "a", "test" };
	EXPECT_EQ(expected, results);
}

TEST(Path, Deconstruct_Reconstruct)
{
	using namespace Cpf;
	using namespace IO;

	{
		// NOTE: the final item is a file since this does not terminate with a '/'.
		const String testPath(Path::Normalize("c:/this/is/a/test/blargo"));
		const String root = Path::GetRoot(testPath);
		const String path = Path::GetDirectory(testPath);
		const String filename = Path::GetFilename(testPath);

		EXPECT_STREQ("c:", root.c_str());
		EXPECT_STREQ("/this/is/a/test/", path.c_str());
		EXPECT_STREQ("blargo", filename.c_str());

		String reconPath = Path::Combine(path, filename);
		reconPath = Path::Combine(root, reconPath);

		EXPECT_STREQ(testPath.c_str(), reconPath.c_str());
	}
}
