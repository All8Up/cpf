//////////////////////////////////////////////////////////////////////////
#include "Visitor/Enum.hpp"
#include "Visitor/Literal.hpp"

using namespace IDL;

AST::EnumItemArray IDL::GetEnumValues(IDLParser::Enum_elementsContext* context)
{
	AST::EnumItemArray result;
	int current = 0;

	for (const auto entry : context->enum_item())
	{
		auto entryName = entry->IDENT()->toString();
		AST::EnumItem item(entryName);
		if (entry->EQUALS())
		{
			// Has a defined value.
			item.SetValue(GetIntegerLiteral(entry->integer_lit()));
		}
		else
		{
			// Using auto incrementing value.
			item.SetValue(current++);
		}

		result.emplace_back(item);
	}

	return result;
}
