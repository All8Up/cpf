//////////////////////////////////////////////////////////////////////////
#include "RefCount.hpp"
#include "RefCounted.hpp"

using namespace Cpf;

iRefCounted::~iRefCounted()
{}

//////////////////////////////////////////////////////////////////////////
namespace
{
	static int s_RefCount = 0;
}

int RefCountInitializer::Install()
{
	if (s_RefCount++ == 0)
	{
	}
	return ++s_RefCount;
}

int RefCountInitializer::Remove()
{
	return --s_RefCount;
}
