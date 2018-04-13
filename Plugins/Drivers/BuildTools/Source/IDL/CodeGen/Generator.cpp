//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/Generator.hpp"
#include "IDL/CodeGen/CppGenerator.hpp"
#include "IDL/CodeGen/RustGenerator.hpp"
#include "IDL/CodeGen/CSharpGenerator.hpp"

using namespace IDL;
using namespace CodeGen;

std::shared_ptr<Generator> CodeGen::Create(CPF::OutputLanguage type)
{
	switch(type)
	{
	case CPF::OutputLanguage::eCPP:
		return std::make_shared<CppGenerator>();
	case CPF::OutputLanguage::eRust:
		return std::make_shared<RustGenerator>();
	case CPF::OutputLanguage::eCSharp:
		return std::make_shared<CSharpGenerator>();
	}

	return std::shared_ptr<Generator>();
}
