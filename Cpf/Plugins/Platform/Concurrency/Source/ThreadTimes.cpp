//////////////////////////////////////////////////////////////////////////
#include "Concurrency/ThreadTimes.hpp"

using namespace Cpf;
using namespace Concurrency;

GOM::Result CPF_STDCALL ThreadTimes::Cast(GOM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case iBase::kIID.GetID():
			*outIface = static_cast<iBase*>(this);
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
