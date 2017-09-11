//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/Cpp/CodeGen.hpp"
#include "IDL/CodeGen/CodeWriter.hpp"
#include <inttypes.h>
#include "Hash/Crc.hpp"
#include "GOM/Result.hpp"

using namespace IDL;
using namespace CodeGen;
using namespace Cpf::Placeholders;

//////////////////////////////////////////////////////////////////////////
void Cpp::Generator::Begin(Visitor& visitor, CodeWriter& writer)
{
	mpWriter = &writer;

	visitor.On<Visitor::Start>(Cpf::Bind(&Generator::OnStart, this));
	visitor.On<Visitor::ModuleStmt>(Cpf::Bind(&Generator::OnModule, this, _1));
	visitor.On<Visitor::SuccessType>(Cpf::Bind(&Generator::OnSuccessType, this, _1, _2, _3));
	visitor.On<Visitor::FailureType>(Cpf::Bind(&Generator::OnFailureType, this, _1, _2, _3));
	visitor.On<Visitor::ImportStmt>(Cpf::Bind(&Generator::OnImportStmt, this, _1, _2));
	visitor.On<Visitor::InterfaceDeclStmt>(Cpf::Bind(&Generator::OnInterfaceDeclStmt, this, _1));
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
	mpWriter->OutputLine("static constexpr uint32_t k%s = 0x%" PRIx32 "; // %s - %s",
		name.c_str(),
		Cpf::GOM::CreateResult(
			0,
			Cpf::Hash::Crc15(subSystem.c_str(), subSystem.length()),
			Cpf::Hash::Crc16(desc.c_str(), desc.length())),
		subSystem.c_str(),
		desc.c_str());
}

void Cpp::Generator::OnFailureType(const String& name, const String& subSystem, const String& desc)
{
	mpWriter->OutputLine("static constexpr uint32_t k%s = 0x%" PRIx32 "; // %s - %s",
		name.c_str(),
		Cpf::GOM::CreateResult(
			1,
			Cpf::Hash::Crc15(subSystem.c_str(), subSystem.length()),
			Cpf::Hash::Crc16(desc.c_str(), desc.length())),
		subSystem.c_str(),
		desc.c_str());
}

void Cpp::Generator::OnImportStmt(const String& item, const SymbolPath& from)
{
	(void)item;  (void)from;
	mpWriter->OutputLine("#include \"GOM/Result.hpp\"");
	mpWriter->OutputLine("");
}

void Cpp::Generator::OnInterfaceDeclStmt(const Visitor::InterfaceDecl& decl)
{
	mpWriter->OutputLine("");
	if (decl.mSuper.Empty())
		mpWriter->OutputLine("struct %s", decl.mName.c_str());
	else
		mpWriter->OutputLine("struct %s : %s", decl.mName.c_str(), decl.mSuper.ToString("::").c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();

	for (const auto& func : decl.mFunctions)
	{
		mpWriter->Output("%svirtual %s CPF_STDCALL %s (",
			mpWriter->GetIndentString().c_str(),
			TypeToString(func.mReturnType).c_str(),
			func.mName.c_str());

		// Parameters.
		if (!func.mParams.empty())
		{
			mpWriter->Output("%s", TypeToString(func.mParams[0].mType).c_str());
			if (!func.mParams[0].mName.empty())
				mpWriter->Output(" %s", func.mParams[0].mName.c_str());

			for (auto it = func.mParams.begin() + 1; it != func.mParams.end(); ++it)
			{
				mpWriter->Output(", %s", TypeToString(it->mType).c_str());
				if (!it->mName.empty())
					mpWriter->Output(" %s", it->mName.c_str());
			}
		}

		mpWriter->Output(") = 0;\n");
	}

	mpWriter->Unindent();
	mpWriter->OutputLine("};");
}

Cpf::String Cpp::Generator::TypeToString(const Visitor::TypeDecl& decl)
{
	String result;
	if (decl.mConst)
		result += "const ";
	switch (decl.mType)
	{
	case Visitor::Type::U8: result += "uint8_t"; break;
	case Visitor::Type::S8: result += "int8_t"; break;
	case Visitor::Type::U16: result += "uint16_t"; break;
	case Visitor::Type::S16: result += "int16_t"; break;
	case Visitor::Type::U32: result += "uint32_t"; break;
	case Visitor::Type::S32: result += "int32_t"; break;
	case Visitor::Type::U64: result += "uint64_t"; break;
	case Visitor::Type::S64: result += "int64_t"; break;

	case Visitor::Type::F32: result += "float"; break;
	case Visitor::Type::F64: result += "double"; break;

	case Visitor::Type::Void: result += "void"; break;
	case Visitor::Type::Result: result += "Result"; break;
	case Visitor::Type::Ident: result += decl.mIdent; break;
	}
	for (const auto& ptr : decl.mPointer)
	{
		(void)ptr;
		result += "*";
	}
	return result;
}
