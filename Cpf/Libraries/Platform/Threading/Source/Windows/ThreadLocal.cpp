//////////////////////////////////////////////////////////////////////////
#include "Threading/ThreadLocal.hpp"

using namespace Cpf;
using namespace Platform;
using namespace Threading;

CPF_EXPORT_THREADING ThreadLocal::ThreadLocal()
	: m_ThreadLocal(InvalidThreadLocal)
{
	m_ThreadLocal = ::TlsAlloc();
}


CPF_EXPORT_THREADING ThreadLocal::~ThreadLocal()
{
	::TlsFree(m_ThreadLocal);
}


/**
	* @brief Get the value stored in the thread local.
	*/
void CPF_EXPORT_THREADING *ThreadLocal::Get()
{
	return ::TlsGetValue(m_ThreadLocal);
}


/**
	* @brief Set the value of the thread local.
	* @param value The value to set to the thread local.
	*/
void CPF_EXPORT_THREADING ThreadLocal::Set(void* value)
{
	::TlsSetValue(m_ThreadLocal, value);
}
