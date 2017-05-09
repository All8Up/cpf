//////////////////////////////////////////////////////////////////////////
#include "Concurrency/ThreadTimes.hpp"

using namespace Cpf;
using namespace Concurrency;

COM::Result CPF_STDCALL ThreadTimes::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;

		case kIID.GetID():
			*outIface = static_cast<iThreadTimes*>(this);
			break;

		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

void CPF_STDCALL ThreadTimes::Wait()
{
	mSemaphore.Acquire();
}

void CPF_STDCALL ThreadTimes::Signal()
{
	mSemaphore.Release();
}
