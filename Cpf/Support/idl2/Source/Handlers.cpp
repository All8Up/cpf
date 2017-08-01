//////////////////////////////////////////////////////////////////////////
#include "Handlers.hpp"

/**
 * @brief Gets qualified identifier.
 * @param [in,out] ctx If non-null, the context.
 * @return The qualified identifier.
 */
std::string idl::GetQualifiedIdent(IDLParser::Qualified_identContext* ctx)
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
