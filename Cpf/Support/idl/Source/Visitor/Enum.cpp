//////////////////////////////////////////////////////////////////////////
#include "Visitor/Enum.hpp"
#include "Visitor/Literal.hpp"

using namespace IDL;

IDLTree::EnumItemArray IDL::GetEnumValues(IDLParser::Enum_elementsContext* context)
{
	IDLTree::EnumItemArray result;
	int current = 0;

	for (const auto entry : context->enum_item())
	{
		auto entryName = entry->IDENT()->toString();
		IDLTree::EnumItem item(entryName);
		if (entry->EQUALS())
		{
			// Has a defined value.
			// TODO: Handle the evaluations..
//			item.SetValue(GetIntegerLiteral(entry->integer_lit()));
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
