//////////////////////////////////////////////////////////////////////////
#pragma once
#include <AST/Symbol.hpp>

namespace AST
{
	class Struct : public Symbol
	{
	public:
		Struct(const ScopeVector& scope, const std::string& name);
		virtual ~Struct();

		SymbolType GetType() const override { return SymbolType::eStruct; }
		std::string ToString() const override { return std::string("Struct: ") + GetName(); }

	private:
	};
}