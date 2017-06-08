//////////////////////////////////////////////////////////////////////////
#include "Resources/Monitors/Manual.hpp"
#include "Resources/Locator.hpp"
#include "Resources/ID.hpp"

using namespace Cpf;
using namespace Resources;
using namespace Monitors;

GOM::Result CPF_STDCALL Manual::Cast(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case iBase::kIID.GetID():
			*outIface = static_cast<iBase*>(this);
			break;
		case kIID.GetID():
			*outIface = static_cast<iMonitor*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}


bool Manual::Touch(ID id)
{
	if (GetLocator())
		return GetLocator()->Touch(id);
	return false;
}

void Manual::TouchAll()
{
	if (GetLocator())
		GetLocator()->TouchAll();
}

Manual::Manual(iBase*)
{}

Manual::~Manual()
{}
