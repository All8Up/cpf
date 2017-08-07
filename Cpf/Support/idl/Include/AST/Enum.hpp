//////////////////////////////////////////////////////////////////////////
#pragma once
#include "AST/Types.hpp"
#include "AST/Symbol.hpp"
#include <memory>
#include <vector>

namespace AST
{
	class EnumItem
	{
	public:
		EnumItem(const std::string& name);
		EnumItem(const std::string& name, uint64_t value);

		const std::string& GetName() const { return mName; }
		uint64_t GetValue() const { return mValue; }
		void SetValue(uint64_t v) { mValue = v; }

	private:
		std::string mName;
		uint64_t mValue;
	};
	using EnumItemArray = std::vector<EnumItem>;


	class Enum : public Symbol
	{
	public:
		Enum(const ScopeVector& scope, const std::string& name);
		Enum(const ScopeVector& scope, const std::string& name, IntegralType type);
		virtual ~Enum() {}

		SymbolType GetType() const override { return SymbolType::eEnum; }
		std::string ToString() const override;

		void SetItems(const EnumItemArray& items) { mItems = items; }
		const EnumItemArray& GetItems() const { return mItems; }

	private:
		IntegralType mType;
		EnumItemArray mItems;
	};
}
