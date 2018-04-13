//////////////////////////////////////////////////////////////////////////
#include "Fence.hpp"
#include "CPF/GOM/ResultCodes.hpp"

using namespace CPF;
using namespace Concurrency;

Fence::Fence(Plugin::iRegistry*, iUnknown*)
	: mSemaphore(0)
{
}

GOM::Result CPF_STDCALL Fence::QueryInterface(GOM::IID id, void** outIface)
{
	if (outIface)
	{
		switch (uint64_t(id))
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
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

