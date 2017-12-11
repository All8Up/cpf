#include <gtest/gtest.h>
#include "CPF/IO/Path.hpp"
#include "CPF/IO/Directory.hpp"
#include "CPF/IO/Globbing.hpp"
#include "CPF/IO/File.hpp"

#if 0

TEST(IO, ExistsCreateDeleteDirectory)
{
	using namespace CPF;
	using namespace IO;

	EXPECT_FALSE(Directory::Exists("TestDirectory"));
	EXPECT_TRUE(Directory::Create("TestDirectory"));
	EXPECT_TRUE(Directory::Exists("TestDirectory"));
	EXPECT_TRUE(Directory::Delete("TestDirectory"));
}

TEST(IO, DirectoryRecursive)
{
	using namespace CPF;
	using namespace IO;
	String testBase = "TestDir";
	String testDir = Path::Combine(testBase, "This/Is/A/Test/");

	EXPECT_FALSE(Directory::Exists(testBase));
	EXPECT_FALSE(Directory::Exists(testDir));

	EXPECT_TRUE(Directory::Create(testDir, true));
	EXPECT_TRUE(Directory::Delete("TestDir", true));

	EXPECT_FALSE(Directory::Exists(testBase));
	EXPECT_FALSE(Directory::Exists(testDir));
}

TEST_F(IOTestFixture, DirectoryAndFileRecursive)
{
	using namespace CPF;
	using namespace IO;
	String testBase = "TestDir";
	String testDir = Path::Combine(testBase, "This/Is/A/Test/");

	EXPECT_FALSE(Directory::Exists(testBase));
	EXPECT_FALSE(Directory::Exists(testDir));

	EXPECT_TRUE(Directory::Create(testDir, true));
	{
		// Create some files.
		auto a = File::Create("TestDir/This/a.txt", StreamAccess::eWrite);
		EXPECT_TRUE(a!=nullptr);
		auto b = File::Create("TestDir/This/Is/b", StreamAccess::eWrite);
		EXPECT_TRUE(b != nullptr);
		auto c = File::Create("TestDir/This/Is/A/c", StreamAccess::eWrite);
		EXPECT_TRUE(c != nullptr);
		auto d = File::Create("TestDir/This/Is/A/Test/temp.txt", StreamAccess::eWrite);
		EXPECT_TRUE(d != nullptr);

		a->Close();
		b->Close();
		c->Close();
		d->Close();
	}
	EXPECT_TRUE(Directory::Delete("TestDir", true));

	EXPECT_FALSE(Directory::Exists(testBase));
	EXPECT_FALSE(Directory::Exists(testDir));
}

TEST(IO, Directory_File_Iterator)
{
	using namespace CPF;
	using namespace IO;

	Vector<String> contents;
	Directory::Entries entries(".");
	for (const auto& entry : entries)
	{
		contents.push_back(entry.mName);
	}

	for (auto entry : Directory::Entries(".", [](const Directory::DirEntry& entry) {
		// Only get cmake related files.
		return Glob("*.cmake", entry.mName.c_str());
	}))
	{
		std::cout << "..: " << entry.mName << " " <<
				  (IsSet(entry.mAttributes, Attributes::eFile) ? "<file>" : "<other>") <<
				  std::endl;
	}
}
#endif
