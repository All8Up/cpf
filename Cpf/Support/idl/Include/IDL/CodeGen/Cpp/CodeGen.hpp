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

		private:
			using String = CPF::String;

			void OnStart();
			void OnModule(const SymbolPath& path);
			void OnSuccessType(const String&, const String&, const String&);
			void OnFailureType(const String&, const String&, const String&);
			void OnImportStmt(const String&, const SymbolPath&);
			void OnInterfaceDeclStmt(const Visitor::InterfaceDecl&);
			void OnInterfaceFwdStmt(const String&);
			void OnStructFwdStmt(const String&);
			void OnStructStmt(const Visitor::StructDecl&);

			static String TypeToString(const Visitor::TypeDecl& decl);

			CodeWriter* mpWriter;
			SymbolPath mModule;
		};
	}
}
