//////////////////////////////////////////////////////////////////////////
#pragma once
#include <AST/Symbol.hpp>
#include "Types.hpp"

namespace AST
{
	class DataMember
	{
	public:
		DataMember(const std::string& name);

		const std::string& GetName() const { return mName; }
		void SetName(const std::string& name) { mName = name; }
		TypeDecl GetType() const { return mType; }
		void SetType(TypeDecl type) { mType = type; }

	private:
		std::string mName;
		TypeDecl mType;
	};
	using DataMemberVector = std::vector<DataMember>;

	class Struct : public Symbol
	{
	public:
		Struct(const ScopeVector& scope, const std::string& name);
		virtual ~Struct();

		SymbolType GetType() const override { return SymbolType::eStruct; }
		std::string ToString() const override;

		void SetDataMembers(const DataMemberVector& members) { mDataMembers = members; }
		const DataMemberVector& GetDataMembers() const { return mDataMembers; }

	private:
		DataMemberVector mDataMembers;
	};
}
