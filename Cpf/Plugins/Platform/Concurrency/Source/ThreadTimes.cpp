//////////////////////////////////////////////////////////////////////////
#include "Concurrency/ThreadTimes.hpp"

using namespace Cpf;
using namespace Concurrency;

GOM::Result CPF_STDCALL ThreadTimes::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;

		case kIID.GetID():
			*outIface = static_cast<iThreadTimes*>(this);
			break;

		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

void CPF_STDCALL ThreadTimes::Wait()
{
	mSemaphore.Acquire();
}

void CPF_STDCALL ThreadTimes::Signal()
{
	mSemaphore.Release();
}
