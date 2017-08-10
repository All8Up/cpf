//////////////////////////////////////////////////////////////////////////
#include "IDL/CodeGen/Generator.hpp"
#include "IDL/CodeGen/Cpp/CodeGen.hpp"

using namespace IDL;
using namespace CodeGen;

std::shared_ptr<Generator> Generator::Create(Type type)
{
	switch(type)
	{
	case Type::Cpp:
		return std::make_shared<Cpp::Generator>();
	}

	return std::shared_ptr<Generator>();
}
