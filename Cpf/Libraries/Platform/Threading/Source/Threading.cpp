//////////////////////////////////////////////////////////////////////////
#include "Threading.hpp"
#include "Logging/Logging.hpp"


using namespace Cpf;
using namespace Threading;

namespace
{
	int s_RefCount = 0;
}

CPF_EXPORT_THREADING int ThreadingInitializer::Install()
{
	if (s_RefCount++ == 0)
	{
		CPF_INIT_LOG(Threading);
	}
	return s_RefCount;
}

CPF_EXPORT_THREADING int ThreadingInitializer::Remove()
{
	if (--s_RefCount == 0)
	{
		CPF_DROP_LOG(Threading);
	}
	return s_RefCount;
}
