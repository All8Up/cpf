//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/Generator.hpp"
#include "IDL/CodeGen/Cpp/CodeGen.hpp"
#include "IDL/CodeGen/Rust/CodeGen.hpp"
#include "IDL/CodeGen/CSharp/CodeGen.hpp"

using namespace IDL;
using namespace CodeGen;

std::shared_ptr<Generator> CodeGen::Create(Language type)
{
	switch(type)
	{
	case Language::Cpp:
		return std::make_shared<CppGenerator>();
	case Language::Rust:
		return std::make_shared<RustGenerator>();
	case Language::CSharp:
		return std::make_shared<CSharpGenerator>();
	}

	return std::shared_ptr<Generator>();
}
