//////////////////////////////////////////////////////////////////////////
#pragma once
#include "AST/Symbol.hpp"
#include <vector>

namespace AST
{
	class SymbolTable
	{
	public:
		SymbolTable();

		std::string GetCurrentScope() const;
		std::shared_ptr<Symbol> PushScope(const std::string& name);
		bool PopScope();

	private:

		using ScopeNameHandle = size_t;
		static const ScopeNameHandle InvalidScopeName = size_t(~0);
		using ScopeVector = std::vector<ScopeNameHandle>;

		struct ScopeEntry
		{
			ScopeEntry() : mScope(InvalidScopeName) {}

			ScopeNameHandle mScope;
			ScopeVector mChildren;
		};

		ScopeNameHandle _AddScopeName(const std::string& name);
		ScopeNameHandle _FindScopeName(const std::string& name) const;
		const std::string& _GetScopeName(ScopeNameHandle handle) const;

		const ScopeVector& _GetCurrentScope() const;
		std::string _ToString(const ScopeVector& path) const;

		std::vector<std::string> mScopeArena;
		ScopeEntry mGlobal;
		ScopeVector mCurrentScope;

		static const std::string mGlobalScopeName;
	};
}
