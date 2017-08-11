//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDL/CodeGen/Generator.hpp"

namespace IDL
{
	namespace CodeGen
	{
		namespace Cpp
		{
			class Generator : public CodeGen::Generator
			{
			public:
				bool Generate(CodeWriter& context, SyntaxTree& src) override;
			};
		}
	}
}
