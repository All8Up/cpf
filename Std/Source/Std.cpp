//////////////////////////////////////////////////////////////////////////
#include <Std/Std.hpp>


namespace
{
	int s_RefCount = 0;
}


int Cpf::StdInitializer::Install()
{
	return ++s_RefCount;
}


int Cpf::StdInitializer::Remove()
{
	return --s_RefCount;
}
