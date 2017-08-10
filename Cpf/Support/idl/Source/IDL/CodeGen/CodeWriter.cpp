//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/CodeWriter.hpp"
#include <cassert>
#include <cstdarg>

using namespace IDL;
using namespace CodeGen;

CodeWriter::CodeWriter(bool useTabs, int indentSpaces)
	: mIndent(0)
	, mUseTabs(useTabs)
	, mIndentSpaces(indentSpaces)
{
	if (mUseTabs)
		mIndentString = std::string(256, '\n');
	else
		mIndentString = std::string(256, ' ');
}

void CodeWriter::Output(const char* const format, ...) const
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

void CodeWriter::OutputLine(const char* const format, ...) const
{
	printf("%s", GetIndentString().c_str());
	{
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}
	printf("\n");
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
