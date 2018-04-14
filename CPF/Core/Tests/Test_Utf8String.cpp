//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "CPF/Std/Utf8String.hpp"
#include "CPF/CSTD/String.hpp"

using namespace CPF;
using namespace STD;

TEST(Utf8String, Construction)
{
	// This is just a compile check.
	const char* utf8String = "Hello World!";
	String strUtf8(utf8String);
	
	Utf8String t0(utf8String);
	Utf8String t1(strUtf8);
}

TEST(Utf8String, Iteration)
{
	const char* utf8String = "Hello World!";
	Utf8String t0(utf8String);

	auto i = 0;
	for (uint32_t c : t0)
	{
		EXPECT_TRUE(utf8String[i++] == char(c));
	}
}

TEST(Utf8String, Append)
{
	const char* utf8String = "Hello World!";
	const char* d0 = "Hello";
	const char* d1 = "World!";
	
	Utf8String t0(d0);
	Utf8String t1(d1);
	t0 += ' ' + t1;

	auto i = 0;
	for (uint32_t c : t0)
	{
		EXPECT_TRUE(utf8String[i++] == char(c));
	}
}

TEST(Utf8String, ReverseIteration)
{
	const char* utf8String = "Hello World!";
	Utf8String t0(utf8String);

	auto i = CSTD::StrLen(utf8String);
	for (auto it = t0.rbegin(); it!=t0.rend(); ++it)
	{
		char c = char(*it);
		char tc = utf8String[--i];
		EXPECT_TRUE(c == tc);
	}
}

TEST(Utf8String, ToUtf16)
{
	const char* utf8String = "Hello World!";
	const wchar_t* utf8StringL = L"Hello World!";

	Utf8String t0(utf8String);
	WString tws;
	EXPECT_TRUE(ConvertUtf8To16(t0, tws));
	
	auto i = 0;
	for (wchar_t c : tws)
	{
		EXPECT_TRUE(utf8StringL[i++] == c);
	}
}

TEST(Utf8String, At)
{
	const char* utf8String = "Hello World!";
	Utf8String t0(utf8String);
	
	for (int i=0; i<t0.length(); ++i)
	{
		EXPECT_EQ(utf8String[i], t0.at(i));
	}
}

TEST(Utf8String, Erase)
{
	const char* utf8String = "Hello World!";
	Utf8String t0(utf8String);
	Utf8String t1 = t0;
	t1.erase(t1.begin() + 5, t1.end());
	EXPECT_STREQ("Hello", t1.data().c_str());
	Utf8String t2 = t0;
	t2.erase(t2.begin(), t2.begin() + 6);
	EXPECT_STREQ("World!", t2.data().c_str());
}
