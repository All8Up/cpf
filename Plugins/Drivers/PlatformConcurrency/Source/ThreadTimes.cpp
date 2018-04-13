//////////////////////////////////////////////////////////////////////////
#include "ThreadTimes.hpp"
#include "CPF/GOM/ResultCodes.hpp"

using namespace CPF;
using namespace Concurrency;

void CPF_STDCALL ThreadTimes::Wait()
{
	mSemaphore.Acquire();
}

void CPF_STDCALL ThreadTimes::Signal()
{
	mSemaphore.Release();
}
