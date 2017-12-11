#include <gtest/gtest.h>
#include "CPF/IO/TextReader.hpp"
#include "CPF/IO/File.hpp"

#if 0
TEST(IO, TextReader)
{
	using namespace CPF;
	using namespace IO;

	String line0("This is a test file.");
	String line1("It has two lines of text.");

	// Create the test file.
	{
		auto f = ::fopen("TestTextFile.txt", "wt");
		::fprintf(f, (line0+"\n").c_str());
		::fprintf(f, (line1+"\n").c_str());
		::fclose(f);
	}

	{
		IntrusivePtr<Stream> readStream(
			File::Create("TestTextFile.txt", Access::eRead));
		TextReader reader(readStream);

		String firstLine, secondLine;
		EXPECT_EQ(line0.length(), reader.ReadLine(firstLine));
		EXPECT_EQ(line0, firstLine);
		EXPECT_EQ(line1.length(), reader.ReadLine(secondLine));
		EXPECT_EQ(line1, secondLine);
	}

	{
		::unlink("TestTextFile.txt");
	}
}
#endif
