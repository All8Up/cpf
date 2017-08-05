//////////////////////////////////////////////////////////////////////////
#pragma once
#include "AST/Symbol.hpp"
#include <vector>
#include <map>


namespace AST
{
	class SymbolTable
	{
	public:
		using ScopeNameHandle = Symbol::ScopeNameHandle;
		static const ScopeNameHandle InvalidScopeName = Symbol::InvalidScopeName;
		using ScopeVector = Symbol::ScopeVector;

		SymbolTable();

		ScopeVector GetCurrentScope() const;
		void PushScope(const std::string& name);
		bool PopScope();

		void AddSymbol(SymbolPtr ptr);
		std::string GetScopeString(SymbolPtr ptr) const;

		using SymbolVector = std::vector<SymbolPtr>;
		using iterator = SymbolVector::iterator;
		using const_iterator = SymbolVector::const_iterator;

		iterator begin() { return mSymbols.begin(); }
		iterator end() { return mSymbols.end(); }
		const_iterator begin() const { return mSymbols.begin(); }
		const_iterator end() const { return mSymbols.end(); }

	private:
		// Scope handling.
		ScopeNameHandle _AddScopeName(const std::string& name);
		ScopeNameHandle _FindScopeName(const std::string& name) const;
		const std::string& _GetScopeName(ScopeNameHandle handle) const;
		const ScopeVector& _GetCurrentScope() const;
		std::string _ToString(const ScopeVector& path) const;

		std::vector<std::string> mScopeArena;
		ScopeVector mCurrentScope;

		// Namespace handling.
		using NamespaceSet = std::map<ScopeVector, std::shared_ptr<Symbol> >;
		bool _FindNamespace(const ScopeVector& scope, std::shared_ptr<Symbol>& ns) const;
		std::shared_ptr<Symbol> _AddNamespace(const ScopeVector& scope, const std::string& name);

		NamespaceSet mNamespaces;
		std::shared_ptr<Symbol> mCurrentNamespace;

		// Vector in order of submission for later in order generation.
		SymbolVector mSymbols;

		// Name of the global namespace.
		static const std::string mGlobalNamespace;
	};
}
