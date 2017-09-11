//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDLParserBaseVisitor.h"
#include "IDL/SyntaxTree.hpp"
#include "IDL/CodeGen/Context.hpp"
#include "Events/Emitter.hpp"

namespace IDL
{
	class Visitor
		: public IDLParserBaseVisitor
		, public Cpf::Events::Emitter
	{
	public:
		using String = Cpf::String;
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
			Cpf::Vector<Pointer> mPointer;
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
			Cpf::Vector<ParamDecl> mParams;
		};
		struct InterfaceDecl
		{
			String mName;
			SymbolPath mSuper;

			using Functions = Cpf::Vector<FunctionDecl>;
			Functions mFunctions;
		};

		typedef Cpf::Events::Event<0, Cpf::Function<void()>> Start;
		typedef Cpf::Events::Event<1, Cpf::Function<void (const SymbolPath&)>> ModuleStmt;
		typedef Cpf::Events::Event<2, Cpf::Function<void(const String&, const String&, const String&)>> SuccessType;
		typedef Cpf::Events::Event<3, Cpf::Function<void(const String&, const String&, const String&)>> FailureType;
		typedef Cpf::Events::Event<4, Cpf::Function<void(const String&, const SymbolPath&)>> ImportStmt;
		typedef Cpf::Events::Event<5, Cpf::Function<void(const InterfaceDecl&)>> InterfaceDeclStmt;

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
