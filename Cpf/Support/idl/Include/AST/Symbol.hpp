//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <memory>
#include <vector>

namespace AST
{
	class Symbol;
	using SymbolPtr = std::shared_ptr<Symbol>;

	enum class SymbolType : int32_t
	{
		eUnknown,
		eNamespace,
		eIntegralConst,
		eFloatConst,
		eStringConst,
		eClassIDConst,
		eEnum,
		eStruct,
		eInterface
	};

	class Symbol
	{
	public:
		using ScopeNameHandle = size_t;
		static const ScopeNameHandle InvalidScopeName = size_t(~0);
		using ScopeVector = std::vector<ScopeNameHandle>;

		virtual ~Symbol() {}

		virtual SymbolType GetType() const = 0;
		virtual std::string ToString() const { return std::string(); }

		const std::string& GetName() const { return mName; }
		const ScopeVector& GetScope() const { return mScope; }

	protected:
		Symbol(const ScopeVector& scope, const std::string& name)
			: mName(name)
			, mScope(scope)
		{
		}

	private:
		std::string mName;
		ScopeVector mScope;
	};
}
