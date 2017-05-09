//////////////////////////////////////////////////////////////////////////
#include "Concurrency/Fence.hpp"

using namespace Cpf;
using namespace Concurrency;

Fence::Fence(iUnknown*)
	: mSemaphore(0)
{
}

COM::Result CPF_STDCALL Fence::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;

		case kIID.GetID():
			*outIface = static_cast<iFence*>(this);
			break;

		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

void Fence::Wait()
{
	mSemaphore.Acquire();
}

void Fence::Signal()
{
	mSemaphore.Release();
}

