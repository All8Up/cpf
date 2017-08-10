//////////////////////////////////////////////////////////////////////////
#pragma once
#include <IDLTree/Symbol.hpp>

namespace IDLTree
{
	class Interface : public Symbol
	{
	public:
		Interface(const ScopeVector& scope, const std::string& name);

		SymbolType GetType() const override { return SymbolType::eInterface; }
		std::string ToString() const override { return std::string("Interface: ") + GetName(); }

	private:
	};
}
