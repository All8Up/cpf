//////////////////////////////////////////////////////////////////////////
#include "Threading/Semaphore.hpp"

using namespace Cpf;
using namespace Platform;
using namespace Threading;

/**
	* Construct a semaphore.
	* @param initCount The initial count the semaphore starts with.
	*/
Semaphore::Semaphore(int initCount)
	: m_Handle(::CreateSemaphore(nullptr, initCount, 0xFFFF, nullptr))
{
}


Semaphore::~Semaphore()
{
	if (m_Handle != InvalidSemaphore)
		::CloseHandle(m_Handle);
}


/**
	* @brief Acquire the semaphore.
	*/
void Semaphore::Acquire()
{
	::WaitForSingleObject(m_Handle, INFINITE);
}


/**
	* @brief Release the semaphore.
	* @param count How many times to release the semaphore.
	*/
void Semaphore::Release(int count)
{
	::ReleaseSemaphore(m_Handle, count, nullptr);
}
