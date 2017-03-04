//////////////////////////////////////////////////////////////////////////
#include "Threading/Mutex.hpp"

using namespace Cpf;
using namespace Threading;

/**
@brief Constructor.
@param initial The caller can decide to lock the mutex initially if desired.
*/
CPF_EXPORT_THREADING Mutex::Mutex(bool initial)
{
	::InitializeCriticalSection(&m_Handle);
	if (initial)
		::EnterCriticalSection(&m_Handle);
}


CPF_EXPORT_THREADING Mutex::~Mutex()
{
	::DeleteCriticalSection(&m_Handle);
}


/**
@brief Acquire the mutex.
*/
void CPF_EXPORT_THREADING Mutex::Acquire()
{
	::EnterCriticalSection(&m_Handle);
}


/**
@brief Try to acquire the mutex, returns instantly if unavailable.
*/
bool CPF_EXPORT_THREADING Mutex::TryAcquire()
{
	return ::TryEnterCriticalSection(&m_Handle) == TRUE;
}


/**
@brief Release the mutex.
*/
void CPF_EXPORT_THREADING Mutex::Release()
{
	LeaveCriticalSection(&m_Handle);
}


Mutex_t CPF_EXPORT_THREADING &Mutex::NativeHandle()
{
	return m_Handle;
}
