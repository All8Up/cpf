//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Generators/Generator.hpp"

namespace Cpp
{
	class Generator : public IDL::Generator
	{
	public:
		bool Generate(IDL::CodeWriter& context, const IDLTree::SymbolTable& symtab) override;

	private:
		static bool _Prelude(IDL::CodeWriter& context, const IDLTree::SymbolTable& symtab);
	};
}
