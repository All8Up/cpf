//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDLParserBaseVisitor.h"
#include "IDL/CodeGen/Context.hpp"
#include "Events/Emitter.hpp"
#include "Vector.hpp"
#include "Map.hpp"

namespace IDL
{
	class SymbolPath
	{
	public:
		using Path = CPF::Vector<CPF::String>;

		SymbolPath() {}
		SymbolPath(const CPF::String& path) : mPath{ path } {}
		~SymbolPath() {}

		bool Empty() const { return mPath.empty(); }
		void Push(const CPF::String& part) { mPath.push_back(part); }
		const Path& GetPath() const { return mPath; }
		CPF::String ToString(const CPF::String& separator) const
		{
			CPF::String result;
			if (Empty())
				return result;
			result = mPath[0];
			for (auto it = mPath.begin() + 1; it != mPath.end(); ++it)
			{
				result += separator;
				result += *it;
			}
			return result;
		}
		Path::iterator begin() { return mPath.begin(); }
		Path::iterator end() { return mPath.end(); }
		Path::const_iterator begin() const { return mPath.begin(); }
		Path::const_iterator end() const { return mPath.end(); }

	private:
		Path mPath;
	};

	class Visitor
		: public IDLParserBaseVisitor
		, public CPF::Events::Emitter
	{
	public:
		using String = CPF::String;
		enum class Type : int32_t
		{
			Ident,

			U8, S8,
			U16, S16,
			U32, S32,
			U64, S64,

			F32, F64,

			Void, Result
		};
		struct Pointer
		{
			bool mConst;
		};
		struct TypeDecl
		{
			TypeDecl() : mConst(false) {}

			bool mConst;
			Type mType;
			SymbolPath mIdent;
			CPF::Vector<Pointer> mPointer;
		};
		struct ParamDecl
		{
			String mName;
			TypeDecl mType;
		};
		struct FunctionDecl
		{
			String mName;
			TypeDecl mReturnType;
			bool mConst;
			CPF::Vector<ParamDecl> mParams;
		};
		struct InterfaceDecl
		{
			String mName;
			SymbolPath mSuper;

			using Functions = CPF::Vector<FunctionDecl>;
			Functions mFunctions;
		};
		struct DataMemberDecl
		{
			String mName;
			TypeDecl mType;
			int32_t mArrayDimensions;
		};
		enum class OsType : int32_t
		{
			eNone = 0,
			eDarwin,
			eWindows,
			eCount
		};
		struct UnionOrStructDecl
		{
			bool mUnion;
			String mName;
			using MemberVector = CPF::Vector<DataMemberDecl>;
			MemberVector mDataMembers[int(OsType::eCount)];
		};
		struct EnumEntry
		{
			String mName;
			int64_t mValue;
		};
		struct EnumDecl
		{
			String mName;
			Type mType;

			using Entries = CPF::Vector<EnumEntry>;
			Entries mEntries;
		};

		typedef CPF::Events::Event<0, CPF::Function<void()>> Start;
		typedef CPF::Events::Event<1, CPF::Function<void (const SymbolPath&)>> ModuleStmt;
		typedef CPF::Events::Event<2, CPF::Function<void(const String&, const String&, const String&)>> SuccessType;
		typedef CPF::Events::Event<3, CPF::Function<void(const String&, const String&, const String&)>> FailureType;
		typedef CPF::Events::Event<4, CPF::Function<void(const String&, const SymbolPath&)>> ImportStmt;
		typedef CPF::Events::Event<5, CPF::Function<void(const InterfaceDecl&)>> InterfaceDeclStmt;
		typedef CPF::Events::Event<6, CPF::Function<void(const String&)>> InterfaceFwdStmt;
		typedef CPF::Events::Event<7, CPF::Function<void(const String&)>> StructFwdStmt;
		typedef CPF::Events::Event<8, CPF::Function<void(const UnionOrStructDecl&)>> StructDeclStmt;
		typedef CPF::Events::Event<9, CPF::Function<void(const String&, const TypeDecl&)>> EnumForwardStmt;
		typedef CPF::Events::Event<10, CPF::Function<void(const EnumDecl&)>> EnumDeclStmt;
		typedef CPF::Events::Event<11, CPF::Function<void(const String&)>> UnionFwdStmt;
		typedef CPF::Events::Event<12, CPF::Function<void(const UnionOrStructDecl&)>> UnionDeclStmt;

		Visitor();

	protected:
		antlrcpp::Any visitMain(IDLParser::MainContext *ctx) override;
		antlrcpp::Any visitModule_stmt(IDLParser::Module_stmtContext *context) override;
		antlrcpp::Any visitSuccess_stmt(IDLParser::Success_stmtContext *ctx) override;
		antlrcpp::Any visitFailure_stmt(IDLParser::Failure_stmtContext *ctx) override;
		antlrcpp::Any visitImport_from_stmt(IDLParser::Import_from_stmtContext *ctx) override;
		antlrcpp::Any visitImport_stmt(IDLParser::Import_stmtContext *ctx) override;
		antlrcpp::Any visitInterface_decl(IDLParser::Interface_declContext *ctx) override;
		antlrcpp::Any visitInterface_fwd(IDLParser::Interface_fwdContext *ctx) override;
		antlrcpp::Any visitStruct_fwd(IDLParser::Struct_fwdContext *ctx) override;
		antlrcpp::Any visitStruct_decl(IDLParser::Struct_declContext *ctx) override;
		antlrcpp::Any visitUnion_fwd(IDLParser::Union_fwdContext *ctx) override;
		antlrcpp::Any visitUnion_decl(IDLParser::Union_declContext *ctx) override;
		antlrcpp::Any visitEnum_fwd(IDLParser::Enum_fwdContext *ctx) override;
		antlrcpp::Any visitEnum_def(IDLParser::Enum_defContext *ctx) override;

		static TypeDecl ParseIntegralType(IDLParser::Integral_typeContext* integralType);
		static TypeDecl ParseTypeDecl(IDLParser::Type_declContext* anyType);
		static int64_t ParseEnumExpr(IDLParser::Enum_exprContext* expr);
		static int64_t ParseIntegerLit(IDLParser::Integer_litContext* lit);
	};
}
