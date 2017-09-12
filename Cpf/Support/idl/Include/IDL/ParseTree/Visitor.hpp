//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDLParserBaseVisitor.h"
#include "IDL/CodeGen/Context.hpp"
#include "Events/Emitter.hpp"
#include "Vector.hpp"

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
			String mIdent;
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
			CPF::Vector<ParamDecl> mParams;
		};
		struct InterfaceDecl
		{
			String mName;
			SymbolPath mSuper;

			using Functions = CPF::Vector<FunctionDecl>;
			Functions mFunctions;
		};

		typedef CPF::Events::Event<0, CPF::Function<void()>> Start;
		typedef CPF::Events::Event<1, CPF::Function<void (const SymbolPath&)>> ModuleStmt;
		typedef CPF::Events::Event<2, CPF::Function<void(const String&, const String&, const String&)>> SuccessType;
		typedef CPF::Events::Event<3, CPF::Function<void(const String&, const String&, const String&)>> FailureType;
		typedef CPF::Events::Event<4, CPF::Function<void(const String&, const SymbolPath&)>> ImportStmt;
		typedef CPF::Events::Event<5, CPF::Function<void(const InterfaceDecl&)>> InterfaceDeclStmt;

		Visitor();

	protected:
		antlrcpp::Any visitMain(IDLParser::MainContext *ctx) override;
		antlrcpp::Any visitGlobal_statements(IDLParser::Global_statementsContext *ctx) override;
		antlrcpp::Any visitGlobal_statement(IDLParser::Global_statementContext *ctx) override;
		antlrcpp::Any visitModule_stmt(IDLParser::Module_stmtContext *context) override;
		antlrcpp::Any visitError_code_stmt(IDLParser::Error_code_stmtContext *ctx) override;
		antlrcpp::Any visitSuccess_stmt(IDLParser::Success_stmtContext *ctx) override;
		antlrcpp::Any visitFailure_stmt(IDLParser::Failure_stmtContext *ctx) override;
		antlrcpp::Any visitImport_from_stmt(IDLParser::Import_from_stmtContext *ctx) override;
		antlrcpp::Any visitImport_stmt(IDLParser::Import_stmtContext *ctx) override;
		antlrcpp::Any visitInterface_stmt(IDLParser::Interface_stmtContext *ctx) override;
		antlrcpp::Any visitInterface_decl(IDLParser::Interface_declContext *ctx) override;

		static TypeDecl ParseTypeDecl(IDLParser::Type_declContext* anyType);
	};
}
