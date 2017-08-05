//////////////////////////////////////////////////////////////////////////
#include "AST/SymbolTable.hpp"
#include <cassert>

using namespace AST;

const std::string SymbolTable::mGlobalScopeName = "::";

SymbolTable::SymbolTable()
{
}

std::string SymbolTable::GetCurrentScope() const
{
	return "";
}

std::shared_ptr<Symbol> SymbolTable::PushScope(const std::string& name)
{
	// Create the current scope string.
	ScopeNameHandle scopeName = _FindScopeName(name);
	if (scopeName == InvalidScopeName)
		scopeName = _AddScopeName(name);

	// Append the new scope.


	// If the scope already exists, return the symbol.
	// If the scope does not exist, make it and return it.

	std::string currentScope = "::" + name;
	return std::shared_ptr<Symbol>(Symbol::Create<Symbol::Type::eNamespace>(currentScope));
}

bool SymbolTable::PopScope()
{
	return false;
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
		return mGlobalScopeName;
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
		return mGlobalScopeName;
	for (const auto it : path)
		result += mGlobalScopeName + _GetScopeName(it);
	return result;
}
