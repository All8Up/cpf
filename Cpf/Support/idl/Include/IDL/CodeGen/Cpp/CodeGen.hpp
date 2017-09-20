//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDL/CodeGen/Generator.hpp"

namespace IDL
{
	namespace CodeGen
	{
		class CppGenerator : public Generator
		{
		public:
			void Begin(Visitor&, CodeWriter&) override;
			void End() override;

			enum Sections : int32_t
			{
				eHeader = 1<<0,
				eImports = 1<<1,
				eNamespace = 1<<2,
				eInterfaces = 1<<3,
				eConstants = 1<<4,
				eStructures = 1<<5,
				eForwards = 1<<6
			};

		private:
			using String = CPF::String;

			void OnStart();
			void OnModule(const SymbolPath& path);
			void OnSuccessType(const String&, const String&, const String&);
			void OnFailureType(const String&, const String&, const String&);
			void OnImportStmt(const String&);
			void OnImportFromStmt(const String&, const SymbolPath&);
			void OnInterfaceDeclStmt(const Visitor::InterfaceDecl&);
			void OnInterfaceFwdStmt(const String&);
			void OnStructFwdStmt(const String&);
			void OnUnionFwdStmt(const String&);
			void OnStructStmt(const Visitor::UnionOrStructDecl&);
			void OnEnumForwardStmt(const String&, Visitor::Type);
			void OnEnumDeclStmt(const Visitor::EnumDecl&);
			void OnFlagsForwardStmt(const String&, Visitor::Type);
			void OnFlagsDeclStmt(const Visitor::EnumDecl&);
			void OnConstIntegral(const Visitor::ConstIntegral&);
			void OnDefaultsDeclStmt(const Visitor::Defaults&);

			static String TypeToString(const Visitor::Type type);
			static String TypeToString(const Visitor::TypeDecl& decl);

			CodeWriter* mpWriter;
			SymbolPath mModule;
		};
	}
}
