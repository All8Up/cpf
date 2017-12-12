#include <gtest/gtest.h>
#include "CPF/IO/Directory.hpp"
#include "CPF/IO/File.hpp"
#include "IOTestFixture.hpp"

// NOTE: These unit tests feed each other in order, this is generally bad but
// without assuming delete works it was the first solution which came to mind.

TEST_F(IOTestFixture, File_CreateForRead_Fail)
{
	using namespace CPF::IO;
	EXPECT_FALSE(File::Exists("TestFile.test"));
	auto file = File::Create("TestFile.test", Access::eRead);
	EXPECT_FALSE(file);
}

TEST_F(IOTestFixture, File_CreateForWrite_TestData)
{
	using namespace CPF::IO;
	EXPECT_FALSE(File::Exists("TestFile.test"));
	auto file = File::Create("TestFile.test", Access::eWrite);
	EXPECT_TRUE(file!=nullptr);

	TestRawBinary testData =
	{
		1, 2, 3
	};

	file->Write(&testData, sizeof(testData));
	file->Flush();
	file->Close();
}

TEST_F(IOTestFixture, File_CreateForRead_TestData)
{
	using namespace CPF::IO;
	EXPECT_TRUE(File::Exists("TestFile.test"));
	auto file = File::Create("TestFile.test", Access::eRead);
	EXPECT_TRUE(file!=nullptr);

	TestRawBinary testData;
	EXPECT_EQ(sizeof(TestRawBinary), file->Read(&testData, sizeof(testData)));
	EXPECT_EQ(1, testData.one);
	EXPECT_EQ(2, testData.two);
	EXPECT_EQ(3, testData.three);
	file->Close();
}

TEST_F(IOTestFixture, File_Delete)
{
	using namespace CPF::IO;
	EXPECT_TRUE(File::Exists("TestFile.test"));
	EXPECT_TRUE(File::Delete("TestFile.test"));
}
