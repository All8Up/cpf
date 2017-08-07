//////////////////////////////////////////////////////////////////////////
#include "Visitor/QualifiedIdentifier.hpp"

using namespace IDL;

/**
* @brief Gets qualified identifier.
* @param [in,out] ctx If non-null, the context.
* @return The qualified identifier.
*/
std::string IDL::GetQualifiedIdentifier(IDLParser::Qualified_identContext* ctx)
{
	std::string result;

	result = ctx->IDENT()->toString();
	const auto& parts = ctx->qualified_part();
	for (auto* part : parts)
	{
		result += "::" + part->IDENT()->toString();
	}

	return result;
}
