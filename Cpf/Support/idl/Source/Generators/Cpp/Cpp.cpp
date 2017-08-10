//////////////////////////////////////////////////////////////////////////
#include "Generators/Cpp/Cpp.hpp"
#include "IDLTree/SymbolTable.hpp"
#include "IDLTree/Const.hpp"

using namespace Cpp;

std::string GetStrippedName(const std::string& str)
{
	std::string result(str.begin() + 1, str.end() - 1);
	return result;
}

bool Generator::_Prelude(IDL::CodeWriter& context, const IDLTree::SymbolTable& symtab)
{
	context.OutputLine("//////////////////////////////////////////////////////////////////////////");
	context.OutputLine("#pragma once");

	for (const auto& import : symtab.GetImports())
	{
		auto strippedName = GetStrippedName(import->GetModule());
		context.OutputLine(("#include \"" + strippedName + ".hpp\"").c_str());
	}
	context.OutputLine("");
	return true;
}

bool Generator::Generate(IDL::CodeWriter& context, const IDLTree::SymbolTable& symtab)
{
	_Prelude(context, symtab);

	for (const auto& symbol : symtab)
	{
		switch (symbol->GetType())
		{
		case IDLTree::SymbolType::eIntegralConst:
		{
			auto cval = std::static_pointer_cast<IDLTree::Const>(symbol);
			uint64_t value = cval->GetAsInteger();
			context.OutputLine("static const int %s = %llu;", cval->GetName().c_str(), value);
		}
		break;
		case IDLTree::SymbolType::eFloatConst:
		{
			auto cval = std::static_pointer_cast<IDLTree::Const>(symbol);
			float value = float(cval->GetAsDouble());
			context.OutputLine("static const float %s = %f;", cval->GetName().c_str(), value);
		}
		break;
		case IDLTree::SymbolType::eStringConst:
		{
			auto cval = std::static_pointer_cast<IDLTree::Const>(symbol);
			std::string value = cval->GetAsString();
			context.OutputLine("static const char %s[] = %s;", cval->GetName().c_str(), value.c_str());
		}
		break;
		case IDLTree::SymbolType::eClassIDConst:
		{
			auto cval = std::static_pointer_cast<IDLTree::Const>(symbol);
			std::string value = cval->GetAsString();
			// TODO: Decide how to generate the Crc's.  Use the CPF compile time stuff or
			// generate it here.  Probably going with generation here for max compatibility.
			context.OutputLine("static const !!!char %s[] = %s;", cval->GetName().c_str(), value.c_str());
		}
		break;
		case IDLTree::SymbolType::eNamespace:
		{
			// TODO: How to end a namespace with the current structure?
			// TODO: Probably need to make symbols hierarchical.
			context.OutputLine("namespace %s", symbol->GetName().c_str());
			context.OutputLine("{");
			context.Indent();
		}
		break;
		case IDLTree::SymbolType::eEndNamespace:
		{
			context.Unindent();
			context.OutputLine("}");
		}
		break;

		default:
		{
			auto scope = symtab.GetScopeString(symbol);
			context.OutputLine("%s = %s", scope.c_str(), symbol->ToString().c_str());
		}
		break;
		}
	}

	return false;
}
