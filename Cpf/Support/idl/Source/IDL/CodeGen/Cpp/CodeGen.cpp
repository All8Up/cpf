//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/Cpp/CodeGen.hpp"
#include "IDL/SyntaxTree.hpp"
#include "IDL/CodeGen/CodeWriter.hpp"

using namespace IDL;
using namespace CodeGen;
using namespace Cpf::Placeholders;
using Visitor = IDL::Visitor;

//////////////////////////////////////////////////////////////////////////
void Cpp::Generator::Begin(Visitor& visitor, IDL::CodeGen::CodeWriter& writer)
{
	mpWriter = &writer;

	visitor.On<Visitor::Start>(Cpf::Bind(&Cpp::Generator::OnStart, this));
	visitor.On<Visitor::ModuleStmt>(Cpf::Bind(&Cpp::Generator::OnModule, this, _1));
	visitor.On<Visitor::SuccessType>(Cpf::Bind(&Cpp::Generator::OnSuccessType, this, _1, _2, _3));
	visitor.On<Visitor::FailureType>(Cpf::Bind(&Cpp::Generator::OnFailureType, this, _1, _2, _3));
	visitor.On<Visitor::ImportAllStmt>(Cpf::Bind(&Cpp::Generator::OnImportAllStmt, this, _1));
}

void Cpp::Generator::End()
{
	for (const auto& part : mModule.GetPath())
	{
		(void)part;
		mpWriter->Unindent();
		mpWriter->OutputLine("}");
	}
}

//

void Cpp::Generator::OnStart()
{
	mpWriter->OutputLine("//////////////////////////////////////////////////////////////////////////");
	mpWriter->OutputLine("#pragma once");
}

void Cpp::Generator::OnModule(const SymbolPath& path)
{
	mModule = path;
	for (const auto& part : path.GetPath())
	{
		mpWriter->OutputLine("namespace %s", part.c_str());
		mpWriter->OutputLine("{");
		mpWriter->Indent();
	}
}

void Cpp::Generator::OnSuccessType(const String& name, const String& subSystem, const String& desc)
{
	mpWriter->OutputLine("static constexpr Result k%s = CreateResult(0, \"%s\"_crc15, \"%s\"_crc16);",
		name.c_str(), subSystem.c_str(), desc.c_str());
}

void Cpp::Generator::OnFailureType(const String& name, const String& subSystem, const String& desc)
{
	mpWriter->OutputLine("static constexpr Result k%s = CreateResult(1, \"%s\"_crc15, \"%s\"_crc16);",
		name.c_str(), subSystem.c_str(), desc.c_str());
}

void Cpp::Generator::OnImportAllStmt(const String& from)
{
	(void)from;
	mpWriter->OutputLine("#include \"GOM/Result.hpp\"");
	mpWriter->OutputLine("");
}
