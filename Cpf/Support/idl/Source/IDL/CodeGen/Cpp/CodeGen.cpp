//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/Cpp/CodeGen.hpp"
#include "IDL/CodeGen/CodeWriter.hpp"
#include <inttypes.h>
#include "Hash/Crc.hpp"
#include "GOM/Result.hpp"
#include "IO/Path.hpp"
#include "GOM/Types.hpp"

using namespace IDL;
using namespace CodeGen;
using namespace CPF::Placeholders;

//////////////////////////////////////////////////////////////////////////
void CppGenerator::Begin(Visitor& visitor, CodeWriter& writer)
{
	mpWriter = &writer;

	visitor.On<Visitor::Start>(CPF::Bind(&CppGenerator::OnStart, this));
	visitor.On<Visitor::ModuleStmt>(CPF::Bind(&CppGenerator::OnModule, this, _1));
	visitor.On<Visitor::SuccessType>(CPF::Bind(&CppGenerator::OnSuccessType, this, _1, _2, _3));
	visitor.On<Visitor::FailureType>(CPF::Bind(&CppGenerator::OnFailureType, this, _1, _2, _3));
	visitor.On<Visitor::ImportStmt>(CPF::Bind(&CppGenerator::OnImportStmt, this, _1, _2));
	visitor.On<Visitor::InterfaceDeclStmt>(CPF::Bind(&CppGenerator::OnInterfaceDeclStmt, this, _1));
	visitor.On<Visitor::InterfaceFwdStmt>(CPF::Bind(&CppGenerator::OnInterfaceFwdStmt, this, _1));
	visitor.On<Visitor::StructFwdStmt>(CPF::Bind(&CppGenerator::OnStructFwdStmt, this, _1));
	visitor.On<Visitor::StructDeclStmt>(CPF::Bind(&CppGenerator::OnStructStmt, this, _1));
	visitor.On<Visitor::EnumForwardStmt>(CPF::Bind(&CppGenerator::OnEnumForwardStmt, this, _1, _2));
	visitor.On<Visitor::EnumDeclStmt>(CPF::Bind(&CppGenerator::OnEnumDeclStmt, this, _1));
	visitor.On<Visitor::UnionFwdStmt>(CPF::Bind(&CppGenerator::OnUnionFwdStmt, this, _1));
	visitor.On<Visitor::UnionDeclStmt>(CPF::Bind(&CppGenerator::OnStructStmt, this, _1));
	visitor.On<Visitor::ConstIntegralStmt>(CPF::Bind(&CppGenerator::OnConstIntegral, this, _1));
}

void CppGenerator::End()
{
	for (const auto& part : mModule.GetPath())
	{
		(void)part;
		mpWriter->Unindent();
		mpWriter->OutputLine("}");
	}
}

//

void CppGenerator::OnStart()
{
	mpWriter->SetSection(eHeader);
	mpWriter->OutputLine("//////////////////////////////////////////////////////////////////////////");
	mpWriter->OutputLine("#pragma once");
}

void CppGenerator::OnModule(const SymbolPath& path)
{
	mpWriter->LineFeed(eNamespace, eNamespace, CodeWriter::kAnySection);
	mModule = path;
	for (const auto& part : path.GetPath())
	{
		mpWriter->OutputLine("namespace %s", part.c_str());
		mpWriter->OutputLine("{");
		mpWriter->Indent();
	}
}

void CppGenerator::OnSuccessType(const String& name, const String& subSystem, const String& desc)
{
	mpWriter->LineFeed(eConstants, eNamespace | eConstants, CodeWriter::kAnySection);
	mpWriter->OutputLine("static constexpr uint32_t k%s = 0x%" PRIx32 "; // %s - %s",
		name.c_str(),
		CPF::GOM::CreateResult(
			0,
			CPF::Hash::Crc15(subSystem.c_str(), subSystem.length()),
			CPF::Hash::Crc16(desc.c_str(), desc.length())),
		subSystem.c_str(),
		desc.c_str());
}

void CppGenerator::OnFailureType(const String& name, const String& subSystem, const String& desc)
{
	mpWriter->LineFeed(eConstants, eNamespace | eConstants, CodeWriter::kAnySection);
	mpWriter->OutputLine("static constexpr uint32_t k%s = 0x%" PRIx32 "; // %s - %s",
		name.c_str(),
		CPF::GOM::CreateResult(
			1,
			CPF::Hash::Crc15(subSystem.c_str(), subSystem.length()),
			CPF::Hash::Crc16(desc.c_str(), desc.length())),
		subSystem.c_str(),
		desc.c_str());
}

void CppGenerator::OnImportStmt(const String& item, const SymbolPath& from)
{
	mpWriter->LineFeed(eImports, eImports | eHeader, CodeWriter::kAnySection);
	auto path = CPF::IO::Path::Combine(from.ToString("/"), item+".hpp");
	mpWriter->OutputLine("#include \"%s\"", path.c_str());
}

void CppGenerator::OnInterfaceDeclStmt(const Visitor::InterfaceDecl& decl)
{
	mpWriter->LineFeed(eInterfaces, eNamespace, CodeWriter::kAnySection);
	if (decl.mSuper.Empty())
		mpWriter->OutputLine("struct %s", decl.mName.c_str());
	else
		mpWriter->OutputLine("struct %s : %s", decl.mName.c_str(), decl.mSuper.ToString("::").c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();

	//
	CPF::String hashName = (mModule.ToString("::") + "::" + decl.mName).c_str();
	CPF::GOM::InterfaceID iid = CPF::GOM::InterfaceID(CPF::Hash::Crc64(hashName.c_str(), hashName.length()));
	mpWriter->OutputLine("static constexpr GOM::InterfaceID kIID = GOM::InterfaceID(0x%" PRIx64 " /* %s */);",
		iid.GetID(), hashName.c_str());

	if (!decl.mFunctions.empty())
		mpWriter->OutputLine("");

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

		if (func.mConst)
			mpWriter->Output(") const = 0;");
		else
			mpWriter->Output(") = 0;");
		mpWriter->LineFeed(eInterfaces, CodeWriter::kNoSection, CodeWriter::kAnySection);
	}

	mpWriter->Unindent();
	mpWriter->OutputLine("};");
}

void CppGenerator::OnInterfaceFwdStmt(const String& name)
{
	mpWriter->LineFeed(eForwards, eNamespace | eForwards, CodeWriter::kAnySection);
	mpWriter->OutputLine("struct %s;", name.c_str());
}

void CppGenerator::OnStructFwdStmt(const String& name)
{
	mpWriter->LineFeed(eForwards, eNamespace | eForwards, CodeWriter::kAnySection);
	mpWriter->OutputLine("struct %s;", name.c_str());
}

void CppGenerator::OnUnionFwdStmt(const String& name)
{
	mpWriter->LineFeed(eForwards, eNamespace | eForwards, CodeWriter::kAnySection);
	mpWriter->OutputLine("union %s;", name.c_str());
}

void CppGenerator::OnStructStmt(const Visitor::UnionOrStructDecl& decl)
{
	mpWriter->LineFeed(eStructures, eNamespace, CodeWriter::kAnySection);
	if (decl.mUnion)
		mpWriter->OutputLine("union %s", decl.mName.c_str());
	else
		mpWriter->OutputLine("struct %s", decl.mName.c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();
	for (const auto& member : decl.mDataMembers[int(Visitor::OsType::eNone)])
	{
		mpWriter->OutputLine("%s %s%s;",
			TypeToString(member.mType).c_str(),
			member.mName.c_str(),
			member.mArrayDimensions>0 ? (String("[") + std::to_string(member.mArrayDimensions) + String("]")).c_str() : "");
	}
	if (!decl.mDataMembers[int(Visitor::OsType::eWindows)].empty())
	{
		mpWriter->OutputLineNoIndent("#if CPF_TARGET_WINDOWS");
		for (const auto& member : decl.mDataMembers[int(Visitor::OsType::eWindows)])
		{
			mpWriter->OutputLine("%s %s%s;",
				TypeToString(member.mType).c_str(),
				member.mName.c_str(),
				member.mArrayDimensions > 0 ? (String("[") + std::to_string(member.mArrayDimensions) + String("]")).c_str() : "");
		}
		mpWriter->OutputLineNoIndent("#endif");
	}
	if (!decl.mDataMembers[int(Visitor::OsType::eDarwin)].empty())
	{
		mpWriter->OutputLineNoIndent("#if CPF_TARGET_DARWIN");
		for (const auto& member : decl.mDataMembers[int(Visitor::OsType::eDarwin)])
		{
			mpWriter->OutputLine("%s %s%s;",
				TypeToString(member.mType).c_str(),
				member.mName.c_str(),
				member.mArrayDimensions > 0 ? (String("[") + std::to_string(member.mArrayDimensions) + String("]")).c_str() : "");
		}
		mpWriter->OutputLineNoIndent("#endif");
	}
	mpWriter->Unindent();
	mpWriter->OutputLine("};");
}

void CppGenerator::OnEnumForwardStmt(const String& name, Visitor::Type type)
{
	mpWriter->LineFeed(eForwards, eNamespace | eForwards, CodeWriter::kAnySection);
	if (type == Visitor::Type::Void)
		mpWriter->OutputLine("enum class %s;", name.c_str());
	else
		mpWriter->OutputLine("enum class %s : %s;", name.c_str(), TypeToString(type).c_str());
}

void CppGenerator::OnEnumDeclStmt(const Visitor::EnumDecl& decl)
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
		if (item.mValue != 0x7fffffffffffffff)
			mpWriter->OutputLine("%s = %d,", item.mName.c_str(), int32_t(item.mValue));
		else
			mpWriter->OutputLine("%s,", item.mName.c_str());
	}

	mpWriter->Unindent();
	mpWriter->OutputLine("};");
}

void CppGenerator::OnConstIntegral(const Visitor::ConstIntegral& constIntegral)
{
	mpWriter->LineFeed(eConstants, eNamespace | eConstants, CodeWriter::kAnySection);
	mpWriter->OutputLine("static constexpr %s k%s = %d;",
		TypeToString(constIntegral.mType).c_str(),
		constIntegral.mName.c_str(),
		constIntegral.mValue);
}


CPF::String CppGenerator::TypeToString(const Visitor::Type type)
{
	switch (type)
	{
	case Visitor::Type::U8: return "uint8_t";
	case Visitor::Type::S8: return "int8_t";
	case Visitor::Type::U16: return "uint16_t";
	case Visitor::Type::S16: return "int16_t";
	case Visitor::Type::U32: return "uint32_t";
	case Visitor::Type::S32: return "int32_t";
	case Visitor::Type::U64: return "uint64_t";
	case Visitor::Type::S64: return "int64_t";

	case Visitor::Type::F32: return "float";
	case Visitor::Type::F64: return "double";

	case Visitor::Type::Void: return "void";
	case Visitor::Type::Result: return "GOM::Result";
	}
	return "";
}

CPF::String CppGenerator::TypeToString(const Visitor::TypeDecl& decl)
{
	String result;
	if (decl.mConst)
		result += "const ";
	switch (decl.mType)
	{
	case Visitor::Type::Ident:
		result += decl.mIdent.ToString("::");
		break;
	default:
		result += TypeToString(decl.mType);
		break;
	}
	for (const auto& ptr : decl.mPointer)
	{
		if (ptr.mConst)
			result += " const *";
		else
			result += "*";
	}
	return result;
}
