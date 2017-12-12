#include <gtest/gtest.h>
#include "CPF/IO/Globbing.hpp"
#include "CPF/Std/String.hpp"


TEST(Globbing, Match)
{
	using namespace CPF;
	using namespace IO;

	const String simple("test.test");
	EXPECT_TRUE(Glob("*.test", simple.c_str()));
	EXPECT_TRUE(Glob("test.*", simple.c_str()));
	EXPECT_FALSE(Glob("*.xx", simple.c_str()));
	EXPECT_FALSE(Glob("temp.*", simple.c_str()));
}
