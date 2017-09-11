//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDL/CodeGen/Generator.hpp"

namespace IDL
{
	namespace CodeGen
	{
		namespace Cpp
		{
			class Generator : public CodeGen::Generator
			{
			public:
				void Begin(IDL::Visitor&, IDL::CodeGen::CodeWriter&) override;
				void End() override;

			private:
				using String = Cpf::String;

				void OnStart();
				void OnModule(const SymbolPath& path);
				void OnSuccessType(const String&, const String&, const String&);
				void OnFailureType(const String&, const String&, const String&);
				void OnImportAllStmt(const String&);

				IDL::CodeGen::CodeWriter* mpWriter;

				SymbolPath mModule;
			};
		}
	}
}
