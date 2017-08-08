//////////////////////////////////////////////////////////////////////////
#include "Generators/Cpp/Cpp.hpp"
#include "AST/SymbolTable.hpp"
#include "AST/Const.hpp"

using namespace Cpp;

std::string GetStrippedName(const std::string& str)
{
	std::string result(str.begin() + 1, str.end() - 1);
	return result;
}

bool Generator::_Prelude(IDL::Context& context, const AST::SymbolTable& symtab)
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

bool Generator::Generate(IDL::Context& context, const AST::SymbolTable& symtab)
{
	_Prelude(context, symtab);

	for (const auto& symbol : symtab)
	{
		switch (symbol->GetType())
		{
		case AST::SymbolType::eIntegralConst:
		{
			std::shared_ptr<AST::Const> cval = std::static_pointer_cast<AST::Const>(symbol);
			uint64_t value = cval->GetAsInteger();
			context.OutputLine("static const int %s = %llu;", cval->GetName().c_str(), value);
		}
		break;
		case AST::SymbolType::eFloatConst:
		{
			std::shared_ptr<AST::Const> cval = std::static_pointer_cast<AST::Const>(symbol);
			float value = float(cval->GetAsDouble());
			context.OutputLine("static const float %s = %f;", cval->GetName().c_str(), value);
		}
		break;
		case AST::SymbolType::eStringConst:
		{
			std::shared_ptr<AST::Const> cval = std::static_pointer_cast<AST::Const>(symbol);
			std::string value = cval->GetAsString();
			context.OutputLine("static const char %s[] = %s;", cval->GetName().c_str(), value.c_str());
		}
		break;
		case AST::SymbolType::eClassIDConst:
		{
			std::shared_ptr<AST::Const> cval = std::static_pointer_cast<AST::Const>(symbol);
			std::string value = cval->GetAsString();
			// TODO: Decide how to generate the Crc's.  Use the CPF compile time stuff or
			// generate it here.  Probably going with generation here for max compatibility.
			context.OutputLine("static const !!!char %s[] = %s;", cval->GetName().c_str(), value.c_str());
		}
		break;
		case AST::SymbolType::eNamespace:
		{
			// TODO: How to end a namespace with the current structure?
			// TODO: Probably need to make symbols hierarchical.
			context.OutputLine("namespace %s", symbol->GetName().c_str());
			context.OutputLine("{");
			context.Indent();
		}
		break;
		case AST::SymbolType::eEndNamespace:
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
