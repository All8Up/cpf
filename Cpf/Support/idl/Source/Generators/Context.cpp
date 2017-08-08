//////////////////////////////////////////////////////////////////////////
#include "Generators/Context.hpp"
#include <cassert>
#include <cstdarg>

using namespace IDL;

Context::Context(bool useTabs, int indentSpaces)
	: mIndent(0)
	, mUseTabs(useTabs)
	, mIndentSpaces(indentSpaces)
{
	if (mUseTabs)
		mIndentString = std::string(256, '\n');
	else
		mIndentString = std::string(256, ' ');
}

void Context::Output(const char* const format, ...) const
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

void Context::OutputLine(const char* const format, ...) const
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

int Context::Indent()
{
	return ++mIndent;
}

int Context::Unindent()
{
	assert(mIndent > 0);
	return --mIndent;
}

std::string Context::GetIndentString() const
{
	std::string result;
	if (mUseTabs)
		result.assign(mIndentString.begin(), mIndentString.begin() + mIndent);
	else
		result.assign(mIndentString.begin(), mIndentString.begin() + (mIndent * mIndentSpaces));
	return result;
}
