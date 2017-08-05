//////////////////////////////////////////////////////////////////////////
#include "AST/SymbolTable.hpp"
#include <cassert>
#include "AST/Namespace.hpp"

using namespace AST;

const std::string SymbolTable::mGlobalNamespace = "::";

SymbolTable::SymbolTable()
{
	// Add the global namespace.
	mCurrentNamespace = _AddNamespace(ScopeVector(), "");
}

SymbolTable::ScopeVector SymbolTable::GetCurrentScope() const
{
	return mCurrentScope;
}

void SymbolTable::PushScope(const std::string& name)
{
	// Create the current scope string.
	ScopeNameHandle scopeName = _FindScopeName(name);
	if (scopeName == InvalidScopeName)
		scopeName = _AddScopeName(name);

	// Append the new scope.
	ScopeVector scope = _GetCurrentScope();
	scope.push_back(scopeName);
	mCurrentScope = scope;

	// If the namespace already exists, return the symbol.
	std::shared_ptr<Symbol> ns;
	if (_FindNamespace(scope, ns))
	{
		mCurrentNamespace = ns;
		AddSymbol(ns);
		return;
	}
	AddSymbol(_AddNamespace(scope, name));
}

bool SymbolTable::PopScope()
{
	assert(!mCurrentScope.empty());
	if (mCurrentScope.empty())
		return false;

	mCurrentScope.pop_back();
	_FindNamespace(mCurrentScope, mCurrentNamespace);
	return true;
}

void SymbolTable::AddSymbol(SymbolPtr ptr)
{
	mSymbols.push_back(ptr);
}

std::string SymbolTable::GetScopeString(SymbolPtr ptr) const
{
	return _ToString(ptr->GetScope());
}

SymbolTable::ScopeNameHandle SymbolTable::_AddScopeName(const std::string& name)
{
	assert(_FindScopeName(name) == InvalidScopeName);
	ScopeNameHandle result = mScopeArena.size();
	mScopeArena.push_back(name);
	return result;
}

SymbolTable::ScopeNameHandle SymbolTable::_FindScopeName(const std::string& name) const
{
	assert(!name.empty());
	size_t index = 0;
	for (const auto& it : mScopeArena)
	{
		if (it == name)
			return index;
		++index;
	}

	return InvalidScopeName;
}

const std::string& SymbolTable::_GetScopeName(ScopeNameHandle handle) const
{
	if (handle == InvalidScopeName)
		return mGlobalNamespace;
	assert(handle != InvalidScopeName && handle < mScopeArena.size());
	return mScopeArena[handle];
}

const SymbolTable::ScopeVector& SymbolTable::_GetCurrentScope() const
{
	return mCurrentScope;
}

std::string SymbolTable::_ToString(const ScopeVector& path) const
{
	std::string result;
	if (path.empty())
		return mGlobalNamespace;
	for (const auto it : path)
		result += mGlobalNamespace + _GetScopeName(it);
	return result;
}

bool SymbolTable::_FindNamespace(const ScopeVector& scope, std::shared_ptr<Symbol>& ns) const
{
	auto it = mNamespaces.find(scope);
	if (it != mNamespaces.end())
	{
		ns = it->second;
		return true;
	}
	return false;
}

std::shared_ptr<Symbol> SymbolTable::_AddNamespace(const ScopeVector& scope, const std::string& name)
{
	assert(mNamespaces.find(scope) == mNamespaces.end());
	SymbolPtr result(std::make_shared<Namespace>(mCurrentScope, name));
	mNamespaces[scope] = result;
	return result;
}
