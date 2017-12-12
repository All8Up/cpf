//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDL/CodeGen/Generator.hpp"

namespace IDL
{
	namespace CodeGen
	{
		class CSharpGenerator : public Generator
		{
		public:
			void Begin(Visitor&, CodeWriter&) override;
			void End() override;

			enum Sections : int32_t
			{
				eHeader = 1 << 0,
				eImports = 1 << 1,
				eNamespace = 1 << 2,
				eInterfaces = 1 << 3,
				eConstants = 1 << 4,
				eStructures = 1 << 5,
			};

		private:
			using String = CPF::String;

			void OnStart();
			void OnModule(const SymbolPath& path);
			void OnSuccessType(const String&, const String&, const String&);
			void OnFailureType(const String&, const String&, const String&);
			void OnImportStmt(const String&, const SymbolPath&);
			void OnInterfaceDeclStmt(const Visitor::InterfaceDecl&);

			static String TypeModifier(const Visitor::TypeDecl& decl, const Visitor::ParamDir& paramDir);
			static String TypeToString(const Visitor::TypeDecl& decl, const Visitor::ParamDir& paramDir);

			CodeWriter* mpWriter;
			SymbolPath mModule;
		};
	}
}
//
//namespace CPF
//{
//	namespace Plugin
//	{
//		struct IID_CID
//		{
//			UInt64 mIID;
//			UInt64 mCID;
//		}
//
//		struct iRegistry; // ????
//
//		interface iClassInstance
//		{
//			GOM::Result CreateInstance(iRegistry registry, GOM::iUnknown outer, out GOM::iUnknown outInstance);
//		}
//	}
//}