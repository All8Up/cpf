//////////////////////////////////////////////////////////////////////////
#pragma once
#include <AST/Symbol.hpp>

namespace AST
{
	class DataMember
	{
	public:
		DataMember(const std::string& name);

	private:
		std::string mName;
	};
	using DataMemberVector = std::vector<DataMember>;

	class Struct : public Symbol
	{
	public:
		Struct(const ScopeVector& scope, const std::string& name);
		virtual ~Struct();

		SymbolType GetType() const override { return SymbolType::eStruct; }
		std::string ToString() const override;

	private:
		DataMemberVector mDataMembers;
	};
}