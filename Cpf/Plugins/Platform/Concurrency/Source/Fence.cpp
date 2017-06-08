//////////////////////////////////////////////////////////////////////////
#include "Concurrency/Fence.hpp"

using namespace Cpf;
using namespace Concurrency;

Fence::Fence(iBase*)
	: mSemaphore(0)
{
}

GOM::Result CPF_STDCALL Fence::Cast(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case iBase::kIID.GetID():
			*outIface = static_cast<iBase*>(this);
			break;

		case kIID.GetID():
			*outIface = static_cast<iFence*>(this);
			break;

		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

void Fence::Wait()
{
	mSemaphore.Acquire();
}

void Fence::Signal()
{
	mSemaphore.Release();
}

