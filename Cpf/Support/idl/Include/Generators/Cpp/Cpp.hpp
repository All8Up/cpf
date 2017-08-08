//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Generators/Generator.hpp"
#include <string>

namespace Cpp
{
	class Generator : public IDL::Generator
	{
	public:
		bool Generate(IDL::Context& context, const AST::SymbolTable& symtab) override;

	private:
		static bool _Prelude(IDL::Context& context, const AST::SymbolTable& symtab);
	};
}
