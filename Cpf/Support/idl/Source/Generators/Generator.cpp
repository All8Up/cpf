//////////////////////////////////////////////////////////////////////////
#include "Generators/Generator.hpp"
#include "Generators/Cpp/Cpp.hpp"

using namespace IDL;

std::shared_ptr<Generator> Generator::Create(Type type)
{
	switch(type)
	{
	case Type::Cpp:
		return std::make_shared<Cpp::Generator>();
	}

	return std::shared_ptr<Generator>();
}
