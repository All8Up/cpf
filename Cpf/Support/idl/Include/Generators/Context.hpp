//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

namespace IDL
{
	class Context
	{
	public:
		Context(bool useTabs = false, int indentSpaces = 4);

		void Output(const char* const format, ...) const;
		void OutputLine(const char* const format, ...) const;

		int Indent();
		int Unindent();
		std::string GetIndentString() const;

	private:
		int mIndent;
		bool mUseTabs = true;
		int mIndentSpaces = 0;

		std::string mIndentString;
	};
}
