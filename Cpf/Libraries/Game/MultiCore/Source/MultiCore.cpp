//////////////////////////////////////////////////////////////////////////
#include "MultiCore.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;

namespace
{
	int s_RefCount = 0;
}

CPF_EXPORT_MULTICORE int MultiCoreInitializer::Install()
{
	if (++s_RefCount == 1)
	{
		CPF_INIT_LOG(MultiCore);
		CPF_LOG(MultiCore, Trace) << "Initialized multicore library.";
	}
	return s_RefCount;
}

CPF_EXPORT_MULTICORE int MultiCoreInitializer::Remove()
{
	if (--s_RefCount == 0)
	{
		CPF_LOG(MultiCore, Trace) << "Shutdown multicore library.";
		CPF_DROP_LOG(MultiCore);
	}
	return s_RefCount;
}
