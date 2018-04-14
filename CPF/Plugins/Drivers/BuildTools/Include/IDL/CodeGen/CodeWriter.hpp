
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include "CPF/IO/TextWriter.hpp"


namespace IDL
{
	namespace CodeGen
	{
		class CodeWriter
		{
		public:
			CodeWriter(CPF::IO::TextWriter& outWriter, bool useTabs = false, int indentSpaces = 4);

			void SetSection(int32_t v) { mLastSectionID = v; }

			void Output(const char* const format, ...);
			void OutputLine(const char* const format, ...);
			void OutputLineNoIndent(const char* const format, ...);

			static constexpr int32_t kAnySection = 0xffffffff;
			static constexpr int32_t kNoSection = 0;
			void LineFeed(int32_t newSection = 0, int32_t noLFSections = kAnySection, int32_t addLFSections = kAnySection);

			int Indent();
			int Unindent();
			std::string GetIndentString() const;

		private:
			CPF::IO::TextWriter mWriter;
			int mIndent;
			bool mUseTabs = true;
			int mIndentSpaces = 0;

			std::string mIndentString;
			int32_t mLastSectionID;
		};
	}
}
