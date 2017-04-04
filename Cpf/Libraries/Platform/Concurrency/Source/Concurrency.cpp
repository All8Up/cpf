//////////////////////////////////////////////////////////////////////////
#include "Concurrency/Concurrency.hpp"
#include "Logging/Logging.hpp"
#include "Time.hpp"

using namespace Cpf;

namespace
{
	int32_t sRefCount = 0;
}

CPF_EXPORT_CONCURRENCY int ConcurrencyInitializer::Install()
{
	if (++sRefCount == 1)
	{
		CPF_INIT_LOG(Concurrency);
		CPF_LOG_LEVEL(Concurrency, Warn);
		TimeInitializer::Install();
	}
	return sRefCount;
}

CPF_EXPORT_CONCURRENCY int ConcurrencyInitializer::Remove()
{
	if (--sRefCount == 0)
	{
		TimeInitializer::Remove();
		CPF_DROP_LOG(Concurrency);
	}
	return sRefCount;
}
