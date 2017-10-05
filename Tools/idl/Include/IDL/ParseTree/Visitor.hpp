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
			None,
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
		struct MemberInitValue
		{
			enum Type
			{
				None,
				Identifier,
				Integer,
				Float,
				Default,
				Str
			};
			Type mType;
			String mIdent;
			int64_t mInt;
			float mFloat;
			String mString;
			Visitor::Type mAsType;
		};
		struct DataMemberDecl
		{
			String mName;
			TypeDecl mType;
			MemberInitValue mArrayDimensions;
			CPF::Vector<MemberInitValue> mInitializers;
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
			String mValue;
		};
		struct EnumDecl
		{
			String mName;
			Type mType;

			using Entries = CPF::Vector<EnumEntry>;
			Entries mEntries;
		};
		struct ConstIntegral
		{
			String mName;
			Type mType;
			int64_t mValue;
		};

		typedef CPF::Events::Event<0, CPF::Function<void()>> Start;
		typedef CPF::Events::Event<1, CPF::Function<void (const SymbolPath&)>> ModuleStmt;
		typedef CPF::Events::Event<2, CPF::Function<void(const String&, const String&, const String&)>> SuccessType;
		typedef CPF::Events::Event<3, CPF::Function<void(const String&, const String&, const String&)>> FailureType;
		typedef CPF::Events::Event<4, CPF::Function<void(const String&)>> ImportStmt;
		typedef CPF::Events::Event<5, CPF::Function<void(const String&, const SymbolPath&)>> ImportFromStmt;
		typedef CPF::Events::Event<6, CPF::Function<void(const InterfaceDecl&)>> InterfaceDeclStmt;
		typedef CPF::Events::Event<7, CPF::Function<void(const String&)>> InterfaceFwdStmt;
		typedef CPF::Events::Event<8, CPF::Function<void(const String&)>> StructFwdStmt;
		typedef CPF::Events::Event<9, CPF::Function<void(const UnionOrStructDecl&)>> StructDeclStmt;
		typedef CPF::Events::Event<10, CPF::Function<void(const String&, Type)>> EnumForwardStmt;
		typedef CPF::Events::Event<11, CPF::Function<void(const EnumDecl&)>> EnumDeclStmt;
		typedef CPF::Events::Event<12, CPF::Function<void(const String&)>> UnionFwdStmt;
		typedef CPF::Events::Event<13, CPF::Function<void(const UnionOrStructDecl&)>> UnionDeclStmt;
		typedef CPF::Events::Event<14, CPF::Function<void(const ConstIntegral&)>> ConstIntegralStmt;
		typedef CPF::Events::Event<15, CPF::Function<void(const String&, Type)>> FlagsForwardStmt;
		typedef CPF::Events::Event<16, CPF::Function<void(const EnumDecl&)>> FlagsDeclStmt;

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
		antlrcpp::Any visitFlags_fwd(IDLParser::Flags_fwdContext *ctx) override;
		antlrcpp::Any visitFlags_def(IDLParser::Flags_defContext *ctx) override;
		antlrcpp::Any visitConst_integral_def(IDLParser::Const_integral_defContext *ctx) override;

		static Type ParseIntegralType(IDLParser::Integral_typeContext* integralType);
		static TypeDecl ParseTypeDecl(IDLParser::Type_declContext* anyType);
		static String ParseEnumExpr(IDLParser::Enum_exprContext* expr);
		static int64_t ParseIntegerLit(IDLParser::Integer_litContext* lit);
		static MemberInitValue ParseInitValue(IDLParser::Member_init_valueContext* ctx);

		static CPF::String ParseExprValue(IDLParser::Expr_valueContext* expr);
		static CPF::String ParseExprLogical(IDLParser::Expr_logicalContext* expr);
		static CPF::String ParseExprShift(IDLParser::Expr_shiftContext* expr);
		static CPF::String ParseExprMulDiv(IDLParser::Expr_mul_divContext* expr);
		static CPF::String ParseExprAddSub(IDLParser::Expr_add_subContext* expr);
	};
}
