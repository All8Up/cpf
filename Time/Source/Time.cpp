//////////////////////////////////////////////////////////////////////////
#include "Time/Counter.hpp"

using namespace Cpf;
using namespace Platform;
using namespace Time;

//
namespace
{
	int s_RefCount = 0;
}


/**
@brief Initialize the time library.
@result Outstanding reference counts on the library.
*/
CPF_EXPORT_TIME int TimeInitializer::Install()
{
	if (s_RefCount++ == 0)
	{
		if (InitializeCounter())
		{
			return s_RefCount;
		}
		--s_RefCount;
	}
	return s_RefCount;
}

/**
@brief Shutdown the time library.
@result Remaining reference counts on the library.
*/
CPF_EXPORT_TIME int TimeInitializer::Remove()
{
	CPF_ASSERT(s_RefCount != 0);
	if (--s_RefCount == 0)
	{
		/* Nothing to do here. */
	}
	return s_RefCount;
}
