#include <gtest/gtest.h>
#include "CPF/IO/Globbing.hpp"
#include "CPF/Std/Utf8String.hpp"


TEST(Globbing, Match)
{
	using namespace CPF;
	using namespace IO;

	const Std::Utf8String simple("test.test");
	EXPECT_TRUE(Glob("*.test", simple));
	EXPECT_TRUE(Glob("test.*", simple));
	EXPECT_FALSE(Glob("*.xx", simple));
	EXPECT_FALSE(Glob("temp.*", simple));
}
