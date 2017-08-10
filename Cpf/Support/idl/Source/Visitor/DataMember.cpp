//////////////////////////////////////////////////////////////////////////
#include "Visitor/DataMember.hpp"
#include "Visitor/Literal.hpp"
#include "IDLTree/Types.hpp"

using namespace IDLTree;

DataMember GetTypeDecl(const std::string& name, IDLParser::Type_declContext* context)
{
	DataMember result(name);
	TypeDecl typeDecl;
	if (context->type_modifier())
	{
		// Has a const modifier.
		typeDecl.mModifiers = TypeModifier::Const;
	}
	assert(context->any_type() != nullptr);
	auto baseType = context->any_type();

	if (baseType->integral_type())
	{
		auto typeContext = baseType->integral_type();
		typeDecl.mType = IDL::GetType(typeContext);
	}
	else if (baseType->float_type())
	{
		auto typeContext = baseType->float_type();
		if (typeContext->F32())
			typeDecl.mType = AllTypes::F32;
		else if (typeContext->F64())
			typeDecl.mType = AllTypes::F64;
	}
	else if (baseType->utility_type())
	{
		auto typeContext = baseType->utility_type();
		if (typeContext->VOID())
			typeDecl.mType = AllTypes::Void;
		else if (typeContext->RESULT())
			typeDecl.mType = AllTypes::Result;
	}
	else if (baseType->IDENT())
	{
		typeDecl.mType = AllTypes::Identifier;
		typeDecl.mIdentifier = baseType->IDENT()->toString();
	}
	result.SetType(typeDecl);

	return result;
}

DataMemberVector IDL::GetDataMembers(IDLParser::Struct_declContext *context)
{
	DataMemberVector members;
	auto blockContext = context->struct_block();
	const auto& items = blockContext->struct_item();
	for (const auto& item : items)
	{
		if (item->member_decl())
		{
			auto mbr = item->member_decl();
			auto typeDecl = mbr->type_decl();
			members.push_back(GetTypeDecl(mbr->IDENT()->toString(), typeDecl));
		}
		else if (item->enum_def())
		{ /* Handled elsewhere. */ }
		else if (item->const_def())
		{ /* Handled elsewhere. */ }
	}

	return members;
}
