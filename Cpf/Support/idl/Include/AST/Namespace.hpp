//////////////////////////////////////////////////////////////////////////
#pragma once
#include "AST/Symbol.hpp"

namespace AST
{
	class Namespace : public Symbol
	{
	public:
		Namespace(const ScopeVector& scope, const std::string& name);
		virtual ~Namespace();

		SymbolType GetType() const override;

		std::string ToString() const override { return std::string("Namespace: ") + GetName(); }

	protected:
	};

	class EndNamespace : public Symbol
	{
	public:
		EndNamespace(const ScopeVector& scope, const std::string& name);
		virtual ~EndNamespace();

		SymbolType GetType() const override;
		std::string ToString() const override { return std::string("EndNamespace: ") + GetName(); }
	};
}
