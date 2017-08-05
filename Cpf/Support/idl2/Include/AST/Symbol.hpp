//////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <memory>

namespace AST
{
	class Symbol
	{
	public:
		enum class Type : int32_t
		{
			eUnknown,
			eNamespace
		};

		Type GetType() const;

		template<int32_t Type> static
		std::shared_ptr<Symbol> Create(const std::string& name);

	private:
		Symbol(Type type, const std::string& name)
			: mType(type)
			, mName(name)
		{
		}

		Type mType;
		std::string mName;
	};

	template<> inline std::shared_ptr<Symbol> Symbol::Create<Symbol::Type::eNamespace>(const std::string& name)
	{
		return std::shared_ptr<Symbol>(new Symbol(Symbol::Type::eNamespace, name));
	}
}
