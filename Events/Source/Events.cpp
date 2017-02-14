//////////////////////////////////////////////////////////////////////////
#include "Events/Events.hpp"

using namespace Cpf;
using namespace Platform;

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
