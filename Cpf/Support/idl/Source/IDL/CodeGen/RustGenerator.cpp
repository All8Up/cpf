//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/RustGenerator.hpp"
#include "IDL/CodeGen/CodeWriter.hpp"
#include <inttypes.h>
#include "Hash/Crc.hpp"
#include "GOM/Result.hpp"
#include "Algorithm.hpp"

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
	visitor.On<Visitor::ImportFromStmt>(CPF::Bind(&RustGenerator::OnImportStmt, this, _1, _2));
	visitor.On<Visitor::InterfaceDeclStmt>(CPF::Bind(&RustGenerator::OnInterfaceDeclStmt, this, _1));
	visitor.On<Visitor::EnumDeclStmt>(CPF::Bind(&RustGenerator::OnEnumDeclStmt, this, _1));
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

	mpWriter->LineFeed();

	mpWriter->OutputLine("#[macro_use]");
	mpWriter->OutputLine("mod cpf;");
	mpWriter->OutputLine("use cpf::*;");
	mpWriter->OutputLine("extern crate libc;");
	mpWriter->OutputLine("use libc::*;");

	mpWriter->LineFeed();
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
	mpWriter->LineFeed();
	mpWriter->OutputLine("#[repr(C)]");
	mpWriter->OutputLine("#[derive(Debug)]");
	mpWriter->OutputLine("pub struct %s", decl.mName.c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();
	mpWriter->OutputLine("pub vtable: *const %s", (decl.mName + "VTable").c_str());
	mpWriter->Unindent();
	mpWriter->OutputLine("}");
	mpWriter->LineFeed();

	mpWriter->OutputLine("#[repr(C)]");
	mpWriter->OutputLine("#[derive(Debug)]");
	mpWriter->OutputLine("pub struct %s", (decl.mName + "VTable").c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();
	mpWriter->Output("%spub base: gom::iUnknownVTable", mpWriter->GetIndentString().c_str());
	for (const auto& func : decl.mFunctions)
	{
		mpWriter->Output(",");
		mpWriter->LineFeed();
		mpWriter->Output("%spub %s: extern \"stdcall\" fn(*mut %s",
			mpWriter->GetIndentString().c_str(),
			func.mName.c_str(),
			decl.mName.c_str());
		if (!func.mParams.empty())
		{
			mpWriter->Indent();
			for (const auto& param : func.mParams)
			{
				mpWriter->Output(",\n%s %s: %s",
					mpWriter->GetIndentString().c_str(),
					param.mName.c_str(),
					TypeToString(param.mType).c_str());
			}
			mpWriter->Unindent();
		}
		mpWriter->Output(")");
		if (func.mReturnType.mType != Visitor::Type::Void)
		{
			mpWriter->Output(" -> %s", TypeToString(func.mReturnType).c_str());
		}
	}
	mpWriter->Unindent();
	mpWriter->OutputLine("}");
}

void RustGenerator::OnEnumDeclStmt(const Visitor::EnumDecl& decl)
{
	mpWriter->LineFeed(eStructures, eNamespace, CodeWriter::kAnySection);
	if (decl.mType == Visitor::Type::Void)
		mpWriter->OutputLine("enum class %s;", decl.mName.c_str());
	else
		mpWriter->OutputLine("enum class %s : %s", decl.mName.c_str(), TypeToString(decl.mType).c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();

	for (const auto& item : decl.mEntries)
	{
		if (!item.mValue.empty())
			mpWriter->OutputLine("%s = %s,", item.mName.c_str(), item.mValue.c_str());
		else
			mpWriter->OutputLine("%s,", item.mName.c_str());
	}

	mpWriter->Unindent();
	mpWriter->OutputLine("};");
}

CPF::String RustGenerator::TypeToString(const Visitor::Type& decl)
{
	String result;
	switch (decl)
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
	}
	return result;
}

CPF::String RustGenerator::TypeToString(const Visitor::TypeDecl& decl)
{
	String result;
	for (const auto& ptr : decl.mPointer)
	{
		(void)ptr;
		result += "*mut ";
	}
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
	case Visitor::Type::Ident:
	{
		for (auto it = decl.mIdent.begin(); it != decl.mIdent.end(); ++it)
		{
			bool last = (it + 1) == decl.mIdent.end();
			String p = *it;
			if (!last)
				CPF::Transform(p.begin(), p.end(), p.begin(), [](char c) { return (char)::tolower(c); });
			result += p + (last ? "" : "::");
		}
	}
	break;
	}
	return result;
}
