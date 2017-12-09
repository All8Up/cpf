//////////////////////////////////////////////////////////////////////////
#include "Threading/Mutex.hpp"

using namespace Cpf;
using namespace Threading;

Mutex::Mutex(bool initial)
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_Handle, &attr);
	pthread_mutexattr_destroy(&attr);
}


Mutex::~Mutex()
{
	pthread_mutex_destroy(&m_Handle);
}


void Mutex::Acquire()
{
	pthread_mutex_lock(&m_Handle);
}


bool Mutex::TryAcquire()
{
	return pthread_mutex_trylock(&m_Handle) == 0;
}


void Mutex::Release()
{
	pthread_mutex_unlock(&m_Handle);
}


Mutex_t& Mutex::NativeHandle()
{
	return m_Handle;
}
