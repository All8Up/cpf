//////////////////////////////////////////////////////////////////////////
#include "Events/Events.hpp"

using namespace Cpf;

namespace
{
	int s_RefCount = 0;
}


int EventsInitializer::Install()
{
	return ++s_RefCount;
}


int EventsInitializer::Remove()
{
	return --s_RefCount;
}
