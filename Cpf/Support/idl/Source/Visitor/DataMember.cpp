//////////////////////////////////////////////////////////////////////////
#include "Visitor/DataMember.hpp"
#include "Visitor/Literal.hpp"
#include "AST/Types.hpp"

using namespace IDL;

AST::DataMember GetTypeDecl(const std::string& name, IDLParser::Type_declContext* context)
{
	AST::DataMember result(name);
	AST::TypeDecl typeDecl;
	if (context->type_modifier())
	{
		// Has a const modifier.
		typeDecl.mModifiers = AST::TypeModifier::Const;
	}
	assert(context->any_type() != nullptr);
	auto baseType = context->any_type();

	if (baseType->integral_type())
	{
		auto typeContext = baseType->integral_type();
		typeDecl.mType = GetType(typeContext);
	}
	else if (baseType->float_type())
	{
		auto typeContext = baseType->float_type();
		if (typeContext->F32())
			typeDecl.mType = AST::AllTypes::F32;
		else if (typeContext->F64())
			typeDecl.mType = AST::AllTypes::F64;
	}
	else if (baseType->utility_type())
	{
		auto typeContext = baseType->utility_type();
		if (typeContext->VOID())
			typeDecl.mType = AST::AllTypes::Void;
		else if (typeContext->RESULT())
			typeDecl.mType = AST::AllTypes::Result;
	}
	else if (baseType->IDENT())
	{
		typeDecl.mType = AST::AllTypes::Identifier;
		typeDecl.mIdentifier = baseType->IDENT()->toString();
	}
	result.SetType(typeDecl);

	return result;
}

AST::DataMemberVector IDL::GetDataMembers(IDLParser::Struct_declContext *context)
{
	AST::DataMemberVector members;
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
