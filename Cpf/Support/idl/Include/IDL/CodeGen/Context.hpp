//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDL/CodeGen/CodeWriter.hpp"

namespace IDL
{
	namespace CodeGen
	{
		class Context
		{
		public:
			Context(CodeWriter& codeWriter)
				: mCodeWriter(codeWriter)
			{}

			CodeWriter& GetWriter() const { return mCodeWriter; }

		private:
			CodeWriter& mCodeWriter;
		};
	}
}
