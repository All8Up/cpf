//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include "IO/TextWriter.hpp"


namespace IDL
{
	namespace CodeGen
	{
		class CodeWriter
		{
		public:
			CodeWriter(Cpf::IO::TextWriter& outWriter, bool useTabs = false, int indentSpaces = 4);

			void Output(const char* const format, ...);
			void OutputLine(const char* const format, ...);

			int Indent();
			int Unindent();
			std::string GetIndentString() const;

		private:
			Cpf::IO::TextWriter mWriter;
			int mIndent;
			bool mUseTabs = true;
			int mIndentSpaces = 0;

			std::string mIndentString;
		};
	}
}
