#include <gtest/gtest.h>
#include "CPF/IO/Path.hpp"
#include "IOTestFixture.hpp"

TEST(Path, Path_Construction)
{
	using namespace CPF;
	using namespace IO;

	Std::Utf8String test = Path::Normalize("Test");
}

TEST_F(IOTestFixture, Normalize)
{
	using namespace CPF;
	using namespace IO;

	int index = 0;
	for (const auto& path : mTestPaths)
	{
		const Std::Utf8String test = Path::Normalize(path);
		EXPECT_TRUE(test == mNormPaths[index]);
		++index;
	}

	Std::Utf8String test0 = Path::Normalize("c:\\wackawacka\\blargo");
	Std::Utf8String expected0("c:/wackawacka/blargo");
	EXPECT_TRUE(test0 == expected0);
}

TEST(Path, EnsureTrailingSeparator)
{
	using namespace CPF;
	using namespace IO;

	Std::Utf8String test0 = Path::Normalize("c:\\wackawacka\\blargo");
	EXPECT_FALSE(test0.back() == '/');
	Std::Utf8String test1 = Path::Normalize("c:\\wackawacka\\blargo\\");
	EXPECT_TRUE(test1.back() == '/');
}

TEST(Path, DetectRooted)
{
	using namespace CPF;
	using namespace IO;

	// Check for windows styled rooted path.
	Std::Utf8String testPath = Path::Normalize("c:\\wackawacka\\blargo");
	EXPECT_TRUE(Path::IsRooted(testPath));

	// Check for *nix styled rooted path.
	Std::Utf8String testPath2 = Path::Normalize("\\wackawacka\\blargo");
	EXPECT_TRUE(Path::IsRooted(testPath2));
}

TEST(Path, GetRoot)
{
	// NOTE: This is primarily for windows, nix roots are always empty.
	using namespace CPF;
	using namespace IO;

	// Check for windows styled rooted path.
	Std::Utf8String testPath = Path::Normalize("c:\\wackawacka\\blargo");
	EXPECT_STREQ("c:", Path::GetRoot(testPath).data().c_str());
}

TEST(Path, HasExtension)
{
	using namespace CPF;
	using namespace IO;

	Std::Utf8String testPath = Path::Normalize("c:\\a\\b.txt");
	EXPECT_TRUE(Path::HasExtension(testPath));
}

TEST(Path, Components)
{
	using namespace CPF;
	using namespace IO;

	const Std::Utf8String testPath(Path::Normalize("c:/this/is/a/test/"));
	Vector<Std::Utf8String> results;
	for (const auto& part : Path::Components(Path::GetDirectory(testPath)))
		results.push_back(part);
	Vector<Std::Utf8String> expected{ "this", "is", "a", "test" };
	EXPECT_EQ(expected, results);
}

TEST(Path, Deconstruct_Reconstruct)
{
	using namespace CPF;
	using namespace IO;

	{
		// NOTE: the final item is a file since this does not terminate with a '/'.
		const Std::Utf8String testPath(Path::Normalize("c:/this/is/a/test/blargo"));
		const Std::Utf8String root = Path::GetRoot(testPath);
		const Std::Utf8String path = Path::GetDirectory(testPath);
		const Std::Utf8String filename = Path::GetFilenameAndExtension(testPath);

		EXPECT_STREQ("c:", root.data().c_str());
		EXPECT_STREQ("/this/is/a/test/", path.data().c_str());
		EXPECT_STREQ("blargo", filename.data().c_str());

		Std::Utf8String reconPath = Path::Combine(path, filename);
		reconPath = Path::Combine(root, reconPath);

		EXPECT_STREQ(testPath.data().c_str(), reconPath.data().c_str());
	}
}
