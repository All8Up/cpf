//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/CodeWriter.hpp"
#include <cassert>
#include <cstdarg>
#include "Std/String.hpp"

using namespace IDL;
using namespace CodeGen;

CodeWriter::CodeWriter(CPF::IO::TextWriter& writer, bool useTabs, int indentSpaces)
	: mWriter(writer)
	, mIndent(0)
	, mUseTabs(useTabs)
	, mIndentSpaces(indentSpaces)
	, mLastSectionID(-1)
{
	if (mUseTabs)
		mIndentString = std::string(256, '\n');
	else
		mIndentString = std::string(256, ' ');
}

void CodeWriter::Output(const char* const format, ...)
{
	va_list args;
	va_start(args, format);
	char buffer[2048];
	vsprintf(buffer, format, args);
	va_end(args);
	mWriter.Write(buffer, CPF::Std::StrLen(buffer));
}

void CodeWriter::OutputLine(const char* const format, ...)
{
	CPF::String indention = GetIndentString();
	mWriter.Write(indention.c_str(), indention.length());
	{
		va_list args;
		va_start(args, format);
		char buffer[2048];
		vsprintf(buffer, format, args);
		va_end(args);
		mWriter.Write(buffer, CPF::Std::StrLen(buffer));
	}
	mWriter.Write("\n", 1);
}

void CodeWriter::OutputLineNoIndent(const char* const format, ...)
{
	va_list args;
	va_start(args, format);
	char buffer[2048];
	vsprintf(buffer, format, args);
	va_end(args);
	mWriter.Write(buffer, CPF::Std::StrLen(buffer));
	mWriter.Write("\n", 1);
}

void CodeWriter::LineFeed(int32_t newSection, int32_t noLFSections, int32_t addLFSections)
{
	if ((mLastSectionID & noLFSections) == 0)
	{
		if ((mLastSectionID & addLFSections) != 0)
		{
			mWriter.Write("\n", 1);
		}
	}
	if (newSection != kNoSection)
		mLastSectionID = newSection;
}

int CodeWriter::Indent()
{
	return ++mIndent;
}

int CodeWriter::Unindent()
{
	assert(mIndent > 0);
	return --mIndent;
}

std::string CodeWriter::GetIndentString() const
{
	std::string result;
	if (mUseTabs)
		result.assign(mIndentString.begin(), mIndentString.begin() + mIndent);
	else
		result.assign(mIndentString.begin(), mIndentString.begin() + (mIndent * mIndentSpaces));
	return result;
}
