//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/CSharpGenerator.hpp"
#include "IDL/CodeGen/CodeWriter.hpp"
#include <inttypes.h>
#include "Hash/Crc.hpp"
#include "GOM/Result.hpp"
#include "Algorithm.hpp"

using namespace IDL;
using namespace CodeGen;
using namespace CPF::Placeholders;

//////////////////////////////////////////////////////////////////////////
void CSharpGenerator::Begin(Visitor& visitor, CodeWriter& writer)
{
	mpWriter = &writer;

	visitor.On<Visitor::Start>(CPF::Bind(&CSharpGenerator::OnStart, this));
	visitor.On<Visitor::ModuleStmt>(CPF::Bind(&CSharpGenerator::OnModule, this, _1));
	visitor.On<Visitor::SuccessType>(CPF::Bind(&CSharpGenerator::OnSuccessType, this, _1, _2, _3));
	visitor.On<Visitor::FailureType>(CPF::Bind(&CSharpGenerator::OnFailureType, this, _1, _2, _3));
	visitor.On<Visitor::ImportFromStmt>(CPF::Bind(&CSharpGenerator::OnImportStmt, this, _1, _2));
	visitor.On<Visitor::InterfaceDeclStmt>(CPF::Bind(&CSharpGenerator::OnInterfaceDeclStmt, this, _1));
}

void CSharpGenerator::End()
{
	for (const auto& part : mModule.GetPath())
	{
		(void)part;
		mpWriter->Unindent();
		mpWriter->OutputLine("}");
	}
}

//

void CSharpGenerator::OnStart()
{

}

void CSharpGenerator::OnModule(const SymbolPath& path)
{
	(void)path;
}

void CSharpGenerator::OnSuccessType(const String& name, const String& subSystem, const String& desc)
{
	mpWriter->OutputLine("pub const %s : u32 = 0x%" PRIx32 "; // %s - %s",
		(name).c_str(),
		CPF::GOM::CreateResult(
			0,
			CPF::Hash::Crc15(subSystem.c_str(), subSystem.length()),
			CPF::Hash::Crc16(desc.c_str(), desc.length())),
		subSystem.c_str(),
		desc.c_str());
}

void CSharpGenerator::OnFailureType(const String& name, const String& subSystem, const String& desc)
{
	mpWriter->OutputLine("pub const %s : u32 = 0x%" PRIx32 "; // %s - %s",
		(name).c_str(),
		CPF::GOM::CreateResult(
			1,
			CPF::Hash::Crc15(subSystem.c_str(), subSystem.length()),
			CPF::Hash::Crc16(desc.c_str(), desc.length())),
		subSystem.c_str(),
		desc.c_str());
}

void CSharpGenerator::OnImportStmt(const String& item, const SymbolPath& from)
{
	(void)item;  (void)from;
	//	mpWriter->OutputLine("#include \"GOM/Result.hpp\"");
	//	mpWriter->OutputLine("");
}

void CSharpGenerator::OnInterfaceDeclStmt(const Visitor::InterfaceDecl& decl)
{
	/*mpWriter->LineFeed();
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
	mpWriter->Output("%spub base: gom::iUnknownVTable", mpWriter->GetIndentString().c_str());*/

	mpWriter->LineFeed();
	mpWriter->OutputLine("[StructLayout(LayoutKind.Sequential)]");
	mpWriter->OutputLine("public class %sVTable", decl.mName.c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();

	for (const auto& func : decl.mFunctions)
	{
		mpWriter->OutputLine("[UnmanagedFunctionPointer(CallingConvention.StdCall)]");
		mpWriter->Output("%spublic delegate %s %sFunc(IntPtr self", 
			mpWriter->GetIndentString().c_str(),
			TypeToString(func.mReturnType).c_str(),
			func.mName.c_str());

		/*mpWriter->OutputLine("[MarshalAs(UnmanagedType.FunctionPtr)]");
		mpWriter->Output("%spublic Func<", mpWriter->GetIndentString().c_str());*/

		for (const auto paramDecl : func.mParams)
		{
			mpWriter->Output(", %s %s", TypeToString(paramDecl.mType).c_str(), paramDecl.mName.c_str());
		}

		/*mpWriter->Output(", %s> %s;", 
			TypeToString(func.mReturnType).c_str(),
			func.mName.c_str());*/

		mpWriter->OutputLine(");");
		mpWriter->OutputLine("");
		mpWriter->OutputLine("[MarshalAs(UnmanagedType.FunctionPtr)]");
		mpWriter->OutputLine("public %sFunc %s;", func.mName.c_str(), func.mName.c_str());


		mpWriter->LineFeed(eInterfaces, CodeWriter::kNoSection, CodeWriter::kAnySection);
		mpWriter->LineFeed(eInterfaces, CodeWriter::kNoSection, CodeWriter::kAnySection);
	}

	mpWriter->Unindent();
	mpWriter->OutputLine("}");

	mpWriter->LineFeed();
	mpWriter->OutputLine("[StructLayout(LayoutKind.Sequential)]");
	mpWriter->OutputLine("public class %s", decl.mName.c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();
	mpWriter->OutputLine("public IntPtr vTable;");
	mpWriter->Unindent();
	mpWriter->OutputLine("}");
}

CPF::String CSharpGenerator::TypeToString(const Visitor::TypeDecl& decl)
{
	String result;
	if (decl.mType != Visitor::Type::Ident)
	{
		for (const auto& ptr : decl.mPointer)
		{
			(void)ptr;
			result += "ref ";
		}
	}

	switch (decl.mType)
	{
	case Visitor::Type::U8: result += "Byte"; break;
	case Visitor::Type::S8: result += "SByte"; break;
	case Visitor::Type::U16: result += "UInt16"; break;
	case Visitor::Type::S16: result += "Int16"; break;
	case Visitor::Type::U32: result += "UInt32"; break;
	case Visitor::Type::S32: result += "Int32"; break;
	case Visitor::Type::U64: result += "UInt64"; break;
	case Visitor::Type::S64: result += "Int64"; break;

	case Visitor::Type::F32: result += "float"; break;
	case Visitor::Type::F64: result += "double"; break;

	case Visitor::Type::Void: result += "void"; break;
	case Visitor::Type::Result: result += "UInt32"; break;
	case Visitor::Type::Ident:
	{
		result += decl.mIdent.ToString("");
		/*for (auto it = decl.mIdent.begin(); it != decl.mIdent.end(); ++it)
		{
			bool last = (it + 1) == decl.mIdent.end();
			String p = *it;
			if (!last)
				CPF::Transform(p.begin(), p.end(), p.begin(), [](char c) { return (char)::tolower(c); });
			result += p + (last ? "" : "::");
		}*/
	}
	break;
	}
	return result;
}
