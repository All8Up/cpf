//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDL/CodeGen/Generator.hpp"

namespace IDL
{
	namespace CodeGen
	{
		class RustGenerator : public Generator
		{
		public:
			void Begin(Visitor&, CodeWriter&) override;
			void End() override;

		private:
			using String = CPF::STD::String;

			enum Sections : int32_t
			{
				eHeader = 1 << 0,
				eImports = 1 << 1,
				eNamespace = 1 << 2,
				eInterfaces = 1 << 3,
				eConstants = 1 << 4,
				eStructures = 1 << 5,
				eForwards = 1 << 6
			};

			void OnStart();
			void OnModule(const SymbolPath& path);
			void OnSuccessType(const String&, const String&, const String&);
			void OnFailureType(const String&, const String&, const String&);
			void OnImportStmt(const String&, const SymbolPath&);
			void OnInterfaceDeclStmt(const Visitor::InterfaceDecl&);
			void OnEnumDeclStmt(const Visitor::EnumDecl& decl);

			static String TypeToString(const Visitor::Type& decl);
			static String TypeToString(const Visitor::TypeDecl& decl);

			CodeWriter* mpWriter;
			SymbolPath mModule;
		};
	}
}
