//////////////////////////////////////////////////////////////////////////
#include "Threading/ThreadLocal.hpp"
#include <pthread.h>

using namespace Cpf;
using namespace Threading;

CPF_EXPORT_THREADING ThreadLocal::ThreadLocal()
	: m_ThreadLocal(InvalidThreadLocal)
{
	::pthread_key_create(&m_ThreadLocal, nullptr);
}


CPF_EXPORT_THREADING ThreadLocal::~ThreadLocal()
{
	::pthread_key_delete(m_ThreadLocal);
}


void CPF_EXPORT_THREADING *ThreadLocal::Get()
{
	return ::pthread_getspecific(m_ThreadLocal);
}


void CPF_EXPORT_THREADING ThreadLocal::Set(void* value)
{
	::pthread_setspecific(m_ThreadLocal, value);
}
