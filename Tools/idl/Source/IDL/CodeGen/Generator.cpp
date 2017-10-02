//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/Generator.hpp"
#include "IDL/CodeGen/CppGenerator.hpp"
#include "IDL/CodeGen/RustGenerator.hpp"

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
	}

	return std::shared_ptr<Generator>();
}
