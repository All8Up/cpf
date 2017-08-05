//////////////////////////////////////////////////////////////////////////
#pragma once
#include "AST/Types.hpp"
#include <string>
#include <memory>
#include <vector>


namespace AST
{
	class EnumItem
	{
	public:
		EnumItem(const std::string& name, uint64_t value);

		const std::string& GetName() const { return mName; }
		uint64_t GetValue() const { return mValue; }

	private:
		std::string mName;
		uint64_t mValue;
	};
	using EnumItemArray = std::vector<EnumItem>;


	class Enum
	{
	public:
		static std::shared_ptr<Enum> Create(const std::string& name);
		static std::shared_ptr<Enum> Create(const std::string& name, IntegralType type);

		const std::string& GetName() const { return mName; }
		IntegralType GetType() const { return mType; }

		void SetItems(const EnumItemArray& items) { mItems = items; }
		const EnumItemArray& GetItems() const { return mItems; }

	private:
		Enum(const std::string& name);
		Enum(const std::string& name, IntegralType type);

		std::string mName;
		IntegralType mType;
		EnumItemArray mItems;
	};
}
