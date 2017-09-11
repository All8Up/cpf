//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/CodeWriter.hpp"
#include <cassert>
#include <cstdarg>
#include "Std/String.hpp"

using namespace IDL;
using namespace CodeGen;

CodeWriter::CodeWriter(Cpf::IO::TextWriter& writer, bool useTabs, int indentSpaces)
	: mWriter(writer)
	, mIndent(0)
	, mUseTabs(useTabs)
	, mIndentSpaces(indentSpaces)
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
	mWriter.Write(buffer, Cpf::Std::StrLen(buffer));
}

void CodeWriter::OutputLine(const char* const format, ...)
{
	Cpf::String indention = GetIndentString();
	mWriter.Write(indention.c_str(), indention.length());
	{
		va_list args;
		va_start(args, format);
		char buffer[2048];
		vsprintf(buffer, format, args);
		va_end(args);
		mWriter.Write(buffer, Cpf::Std::StrLen(buffer));
	}
	mWriter.Write("\n", 1);
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
