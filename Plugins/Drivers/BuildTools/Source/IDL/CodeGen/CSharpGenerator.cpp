//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/CSharpGenerator.hpp"
#include "IDL/CodeGen/CodeWriter.hpp"
#include <inttypes.h>
#include "CPF/Hash/Crc.hpp"
#include "CPF/GOM/Result.hpp"
#include "CPF/Std/Algorithm.hpp"

using namespace IDL;
using namespace CodeGen;
using namespace CPF::STD::Placeholders;

//////////////////////////////////////////////////////////////////////////
void CSharpGenerator::Begin(Visitor& visitor, CodeWriter& writer)
{
	mpWriter = &writer;

	visitor.On<Visitor::Start>(CPF::STD::Bind(&CSharpGenerator::OnStart, this));
	visitor.On<Visitor::ModuleStmt>(CPF::STD::Bind(&CSharpGenerator::OnModule, this, _1));
	visitor.On<Visitor::SuccessType>(CPF::STD::Bind(&CSharpGenerator::OnSuccessType, this, _1, _2, _3));
	visitor.On<Visitor::FailureType>(CPF::STD::Bind(&CSharpGenerator::OnFailureType, this, _1, _2, _3));
	visitor.On<Visitor::ImportFromStmt>(CPF::STD::Bind(&CSharpGenerator::OnImportStmt, this, _1, _2));
	visitor.On<Visitor::InterfaceDeclStmt>(CPF::STD::Bind(&CSharpGenerator::OnInterfaceDeclStmt, this, _1));
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
	mpWriter->OutputLine("using System;");
	mpWriter->OutputLine("using System.Runtime.InteropServices;");
}

void CSharpGenerator::OnModule(const SymbolPath& path)
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

void CSharpGenerator::OnSuccessType(const String& name, const String& subSystem, const String& desc)
{
	mpWriter->LineFeed(eConstants, eNamespace | eConstants, CodeWriter::kAnySection);
	mpWriter->OutputLine("//const UInt32 k%s = 0x%" PRIx32 "; // %s - %s",
		name.c_str(),
		CPF::GOM::CreateResult(
			0,
			CPF::Hash::Crc15(subSystem.c_str(), subSystem.length()),
			CPF::Hash::Crc16(desc.c_str(), desc.length())),
		subSystem.c_str(),
		desc.c_str());
}

void CSharpGenerator::OnFailureType(const String& name, const String& subSystem, const String& desc)
{
	mpWriter->LineFeed(eConstants, eNamespace | eConstants, CodeWriter::kAnySection);
	mpWriter->OutputLine("//const UInt32 k%s = 0x%" PRIx32 "; // %s - %s",
		name.c_str(),
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
	mpWriter->LineFeed(eImports, eImports | eHeader, CodeWriter::kAnySection);
	//auto path = CPF::IO::Path::Combine(from.ToString("/"), item + ".hpp");
	mpWriter->OutputLine("using %s;", from.ToString(".").c_str());
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

	//////////////////////////// VTABLE ////////////////////////////
	mpWriter->LineFeed();
	mpWriter->OutputLine("[StructLayout(LayoutKind.Sequential)]");
	mpWriter->OutputLine("public class %sVTable : iUnknownVTable", decl.mName.c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();

	for (const auto& func : decl.mFunctions)
	{
		mpWriter->OutputLine("[UnmanagedFunctionPointer(CallingConvention.StdCall)]");
		mpWriter->Output("%spublic delegate %s %sFunc(IntPtr self", 
			mpWriter->GetIndentString().c_str(),
			TypeToString(func.mReturnType, {}).c_str(),
			func.mName.c_str());

		/*mpWriter->OutputLine("[MarshalAs(UnmanagedType.FunctionPtr)]");
		mpWriter->Output("%spublic Func<", mpWriter->GetIndentString().c_str());*/

		for (const auto paramDecl : func.mParams)
		{
			mpWriter->Output(", %s %s", TypeToString(paramDecl.mType, paramDecl.mDir).c_str(), paramDecl.mName.c_str());
		}

		/*mpWriter->Output(", %s> %s;", 
			TypeToString(func.mReturnType).c_str(),
			func.mName.c_str());*/

		mpWriter->Output(");");
		mpWriter->OutputLine("");
		mpWriter->OutputLine("");
		mpWriter->OutputLine("[MarshalAs(UnmanagedType.FunctionPtr)]");
		mpWriter->OutputLine("public %sFunc %s;", func.mName.c_str(), func.mName.c_str());

		mpWriter->LineFeed(eInterfaces, CodeWriter::kNoSection, CodeWriter::kAnySection);
	}

	mpWriter->Unindent();
	mpWriter->OutputLine("}");

	//////////////////////////// INTERFACE ////////////////////////////

	mpWriter->LineFeed();
	mpWriter->OutputLine("public interface %s", decl.mName.c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();

	for (const auto& func : decl.mFunctions)
	{
		mpWriter->Output("%s%s %s(IntPtr self",
			mpWriter->GetIndentString().c_str(),
			TypeToString(func.mReturnType, {}).c_str(),
			func.mName.c_str());

		for (const auto paramDecl : func.mParams)
		{
			mpWriter->Output(", %s %s", TypeToString(paramDecl.mType, paramDecl.mDir).c_str(), paramDecl.mName.c_str());
		}

		mpWriter->Output(");");
		mpWriter->OutputLine("");
	}

	mpWriter->Unindent();
	mpWriter->OutputLine("}");

	//////////////////////////// WRAPPER CLASS ////////////////////////////

	mpWriter->LineFeed();
	mpWriter->OutputLine("public class %sWrapper : IWrapper", decl.mName.c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();

	// Class variables
	mpWriter->OutputLine("private IntPtr unmanagedInstance;");
	mpWriter->OutputLine("private %s instance;", decl.mName.c_str());
	mpWriter->OutputLine("private %sVTable vTable = new %sVTable();", decl.mName.c_str(), decl.mName.c_str());
	mpWriter->OutputLine("private GenericObject genericObject = new GenericObject();");
	mpWriter->LineFeed(eInterfaces, CodeWriter::kNoSection, CodeWriter::kAnySection);

	mpWriter->OutputLine("public IntPtr NativePointer => unmanagedInstance;");
	mpWriter->OutputLine("public UInt64 CID => 0x%" PRIX64 ";",  CPF::Hash::ComputeCrc64(decl.mName.c_str(), decl.mName.length(), uint64_t(-1)));
	mpWriter->LineFeed(eInterfaces, CodeWriter::kNoSection, CodeWriter::kAnySection);

	// C++ -> C# constructor
	mpWriter->OutputLine("public %sWrapper(IntPtr unmanagedInst)", decl.mName.c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();
	mpWriter->OutputLine("unmanagedInstance = unmanagedInst;");
	mpWriter->OutputLine("Marshal.PtrToStructure(unmanagedInst, genericObject);");
	mpWriter->OutputLine("Marshal.PtrToStructure(genericObject.VTablePtr, vTable);");
	mpWriter->Unindent();
	mpWriter->OutputLine("}");
	mpWriter->LineFeed(eInterfaces, CodeWriter::kNoSection, CodeWriter::kAnySection);

	// C# -> C++ constructor
	mpWriter->OutputLine("public %sWrapper(%s inst)", decl.mName.c_str(), decl.mName.c_str());
	mpWriter->OutputLine("{");
	mpWriter->Indent();
	mpWriter->OutputLine("instance = inst;");
	mpWriter->OutputLine("var unknown = (IUnknown)inst;");
	mpWriter->OutputLine("");
	mpWriter->OutputLine("vTable.AddRef = unknown.AddRef;");
	mpWriter->OutputLine("vTable.Release = unknown.Release;");
	mpWriter->OutputLine("vTable.QueryInterface = unknown.QueryInterface;");

	// Bind C# object to VTable
	for (const auto& func : decl.mFunctions)
	{
		mpWriter->OutputLine("vTable.%s = inst.%s;", func.mName.c_str(), func.mName.c_str());
	}

	mpWriter->LineFeed();
	mpWriter->OutputLine("genericObject.VTablePtr = Marshal.AllocHGlobal(Marshal.SizeOf(vTable));");
	mpWriter->OutputLine("unmanagedInstance = Marshal.AllocHGlobal(Marshal.SizeOf(genericObject));");

	mpWriter->LineFeed();

	mpWriter->OutputLine("Marshal.StructureToPtr(vTable, genericObject.VTablePtr, false);");
	mpWriter->OutputLine("Marshal.StructureToPtr(genericObject, unmanagedInstance, false);");

	mpWriter->Unindent();
	mpWriter->OutputLine("}");

	// Wrapper functions for calling unmanaged from C#
	for (const auto& func : decl.mFunctions)
	{
		mpWriter->LineFeed(eInterfaces, CodeWriter::kNoSection, CodeWriter::kAnySection);

		// Function signature
		mpWriter->Output("%spublic %s %s(",
			mpWriter->GetIndentString().c_str(),
			TypeToString(func.mReturnType, {}).c_str(),
			func.mName.c_str());

		bool firstParam = true;

		for (const auto paramDecl : func.mParams)
		{
			mpWriter->Output("%s%s %s", !firstParam ? ", " : "", TypeToString(paramDecl.mType, paramDecl.mDir).c_str(), paramDecl.mName.c_str());

			firstParam = false;
		}

		mpWriter->Output(")");
		mpWriter->LineFeed(eInterfaces, CodeWriter::kNoSection, CodeWriter::kAnySection);
		// Function body
		mpWriter->OutputLine("{");
		mpWriter->Indent();
		mpWriter->Output("%s %svTable.%s(unmanagedInstance",
			mpWriter->GetIndentString().c_str(),
			func.mReturnType.mType == Visitor::Type::Void ? "" : "return ",
			func.mName.c_str());

		for (const auto paramDecl : func.mParams)
		{
			mpWriter->Output(", %s%s", TypeModifier(paramDecl.mType, paramDecl.mDir).c_str(), paramDecl.mName.c_str());
		}

		mpWriter->Output(");");
		mpWriter->Unindent();
		mpWriter->LineFeed(eInterfaces, CodeWriter::kNoSection, CodeWriter::kAnySection);
		mpWriter->OutputLine("}");
	}

	mpWriter->Unindent();
	mpWriter->OutputLine("}");
}

CSharpGenerator::String CSharpGenerator::TypeModifier(const Visitor::TypeDecl& decl, const Visitor::ParamDir& paramDir)
{
	String result;

	if (decl.mIdent.ToString("") == "char")
	{
		return "";
	}

	if (paramDir.mOut && paramDir.mIn)
	{
		return "ref ";
	}

	if (paramDir.mOut)
	{
		return "out ";
	}

	if (decl.mType != Visitor::Type::Ident)
	{
		if (decl.mPointer.size() == 1)
		{
			return "ref ";
		}
	}

	return "";
}


CPF::STD::String CSharpGenerator::TypeToString(const Visitor::TypeDecl& decl, const Visitor::ParamDir& paramDir)
{
	String result = TypeModifier(decl, paramDir);

	if (decl.mType != Visitor::Type::Ident)
	{
		if (decl.mPointer.size() > 1)
		{
			return result + "IntPtr";
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
		if(decl.mIdent.ToString("") == "char")
		{
			return "string";
		}

		if(decl.mIdent.ToString("") == "IID_CID")
		{
			return "IID_CID";
		}

		return result + "IntPtr";
		//result += decl.mIdent.ToString("");
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
