//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/Rust/CodeGen.hpp"
#include "IDL/CodeGen/CodeWriter.hpp"
#include <inttypes.h>
#include "Hash/Crc.hpp"
#include "GOM/Result.hpp"

using namespace IDL;
using namespace CodeGen;
using namespace CPF::Placeholders;

//////////////////////////////////////////////////////////////////////////
CPF::String ConvertName(const CPF::String& name)
{
	std::locale loc;
	CPF::String result;

	bool first = true;
	bool raising = false;
	for (const auto c : name)
	{
		if (std::isupper(c, loc))
		{
			// Found a leading upper case, start a new word.
			if (first)
			{
				result.push_back(c);
				first = false;
				raising = true;
			}
			else
			{
				if (!raising)
				{
					result.push_back('_');
					raising = true;
				}
				result.push_back(c);
			}
		}
		else
		{
			auto cc = std::toupper(c, loc);
			result.push_back(cc);
			raising = false;
		}
	}

	return result;
}

//////////////////////////////////////////////////////////////////////////
void RustGenerator::Begin(Visitor& visitor, CodeWriter& writer)
{
	mpWriter = &writer;

	visitor.On<Visitor::Start>(CPF::Bind(&RustGenerator::OnStart, this));
	visitor.On<Visitor::ModuleStmt>(CPF::Bind(&RustGenerator::OnModule, this, _1));
	visitor.On<Visitor::SuccessType>(CPF::Bind(&RustGenerator::OnSuccessType, this, _1, _2, _3));
	visitor.On<Visitor::FailureType>(CPF::Bind(&RustGenerator::OnFailureType, this, _1, _2, _3));
	visitor.On<Visitor::ImportStmt>(CPF::Bind(&RustGenerator::OnImportStmt, this, _1, _2));
	visitor.On<Visitor::InterfaceDeclStmt>(CPF::Bind(&RustGenerator::OnInterfaceDeclStmt, this, _1));
}

void RustGenerator::End()
{
	for (const auto& part : mModule.GetPath())
	{
		(void)part;
		mpWriter->Unindent();
		mpWriter->OutputLine("}");
	}
}

//

void RustGenerator::OnStart()
{
	mpWriter->OutputLine("//////////////////////////////////////////////////////////////////////////");
	mpWriter->OutputLine("#![allow(non_snake_case)]");
	mpWriter->OutputLine("#![allow(non_camel_case_types)");
	mpWriter->OutputLine("#![allow(dead_code)]");

	mpWriter->OutputLine("");

	mpWriter->OutputLine("#[macro_use]");
	mpWriter->OutputLine("mod cpf;");
	mpWriter->OutputLine("use cpf::*;");
	mpWriter->OutputLine("extern crate libc;");
	mpWriter->OutputLine("use libc::{c_void};");

	mpWriter->OutputLine("");
}

void RustGenerator::OnModule(const SymbolPath& path)
{
	(void)path;
}

void RustGenerator::OnSuccessType(const String& name, const String& subSystem, const String& desc)
{
	mpWriter->OutputLine("pub const %s : u32 = 0x%" PRIx32 "; // %s - %s",
		ConvertName(name).c_str(),
		CPF::GOM::CreateResult(
			0,
			CPF::Hash::Crc15(subSystem.c_str(), subSystem.length()),
			CPF::Hash::Crc16(desc.c_str(), desc.length())),
		subSystem.c_str(),
		desc.c_str());
}

void RustGenerator::OnFailureType(const String& name, const String& subSystem, const String& desc)
{
	mpWriter->OutputLine("pub const %s : u32 = 0x%" PRIx32 "; // %s - %s",
		ConvertName(name).c_str(),
		CPF::GOM::CreateResult(
			1,
			CPF::Hash::Crc15(subSystem.c_str(), subSystem.length()),
			CPF::Hash::Crc16(desc.c_str(), desc.length())),
		subSystem.c_str(),
		desc.c_str());
}

void RustGenerator::OnImportStmt(const String& item, const SymbolPath& from)
{
	(void)item;  (void)from;
//	mpWriter->OutputLine("#include \"GOM/Result.hpp\"");
//	mpWriter->OutputLine("");
}

void RustGenerator::OnInterfaceDeclStmt(const Visitor::InterfaceDecl& decl)
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

CPF::String RustGenerator::TypeToString(const Visitor::TypeDecl& decl)
{
	String result;
	if (decl.mConst)
		result += "const ";
	switch (decl.mType)
	{
	case Visitor::Type::U8: result += "u8"; break;
	case Visitor::Type::S8: result += "s8"; break;
	case Visitor::Type::U16: result += "u16"; break;
	case Visitor::Type::S16: result += "s16"; break;
	case Visitor::Type::U32: result += "u32"; break;
	case Visitor::Type::S32: result += "s32"; break;
	case Visitor::Type::U64: result += "u64"; break;
	case Visitor::Type::S64: result += "s64"; break;

	case Visitor::Type::F32: result += "float"; break;
	case Visitor::Type::F64: result += "double"; break;

	case Visitor::Type::Void: result += "void"; break;
	case Visitor::Type::Result: result += "u32"; break;
	case Visitor::Type::Ident: result += decl.mIdent; break;
	}
	for (const auto& ptr : decl.mPointer)
	{
		(void)ptr;
		result += "*";
	}
	return result;
}
